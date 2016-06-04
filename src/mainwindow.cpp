#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "settingsserialdialog.h"
#include "echo.h"
#include "sensor.h"

#include <QPushButton>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <math.h>
#include <string>
#include <QFileDialog>
#include <QDateTime>

#define MAX_DATA        800
#define SILENCE_SIGNAL  160
#define PI              3.14159265

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threshold_value = ui->signalThresholdValueBox->value();
    loadOperation = false;

    drawMap(ui->sonarMap);
    drawSignalPlot(ui->sonarSignal);

    mbSonar.tryb_pracy      = Sensor::pojedynczy;
    mbSonar.wybrany_czujnik = Sensor::lewy;
    mbSonar.algorithm       = Sensor::alg0;
    mbSonar.angle           = -45.0;
    mbSonar.angleStep       = 1.0;
    mbSonar.maxAngle        = 45.0;
    mbSonar.interpolation   = false;

    ui->sonarMap->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->sonarMap, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

    /* Create SIGNAL-SLOT connections */
    QObject::connect(ui->signalThresholdValueBox, SIGNAL(valueChanged(int)), this, SLOT(threshold_changed()));
}

MainWindow::~MainWindow()
{
    if (stm32_serial->isOpen())
        stm32_serial->close();

    delete ui;
}

void MainWindow::sendAngleToSTM()
{
    stm32_serial->write("+");
}

void MainWindow::readSerialData()
{
    static Echo         echo; 
    static quint16      x = 0;
    static quint16      adc_val;

    static QString saveFileName = "/home/marekf/Dokumenty/pwr/mgr/build/build-sonar_app-Desktop_Qt_5_6_0_GCC_64bit-Debug/data/data.txt";
    static QFile file(saveFileName);

    while (stm32_serial->canReadLine())
    {
        serialBuffer = stm32_serial->readLine();
        bufferSplit = serialBuffer.split("\n");

        if (serialBuffer != "\n")
        {
            adc_val = serialBuffer.toUInt();

            echo.processSignal(mbSonar, adc_val, x, threshold_value);

            x++;

            /* Save data to the file */
            static QTextStream stream(&file);
            if (x == 1) {
                file.open(QIODevice::ReadWrite | QIODevice::Text);

                switch (currentMeasurementType) {
                    case 1:
                        stream << "SIN" << endl;
                        break;
                    case 2:
                        stream << "SCA" << endl;
                        break;
                }

                switch (mbSonar.tryb_pracy) {
                    case 0:
                        stream << "POJ" << endl;
                        break;
                    case 1:
                        stream << "POD" << endl;
                        break;
                }

                switch (mbSonar.wybrany_czujnik) {
                    case 0:
                        stream << "L" << endl
                               << "A:" << mbSonar.angle << endl;

                        break;
                    case 1:
                        stream << "R" << endl
                               << "A:" << mbSonar.angle << endl;
                        break;
                }
            }

            stream << x << "\t" << adc_val << endl;

            if (x == MAX_DATA) {
                stream << "ANALOG_ENVELOPE_END" << endl;
                //file.close();
            }
            /* ~~~~~~~~~~~~~~~~~~~~~ */

            if (currentMeasurementType == single)
            {
                if (mbSonar.wybrany_czujnik == Sensor::lewy)
                {
                    ui->sonarSignal->graph(0)->addData(x, adc_val);
                    ui->sonarSignal->graph(0)->rescaleValueAxis(true);
                    ui->sonarSignal->graph(0)->rescaleKeyAxis(true);
                    ui->sonarSignal->replot();
                }
                else
                {
                    ui->sonarSignal->graph(2)->addData(x, adc_val);
                    ui->sonarSignal->graph(2)->rescaleValueAxis(true);
                    ui->sonarSignal->graph(2)->rescaleKeyAxis(true);
                    ui->sonarSignal->replot();
                }
            }
        }
    }

    if (x >= MAX_DATA)
    {
        dataHandler(&echo, &x);
    }
}

void MainWindow::dataHandler(Echo *echo_ptr, quint16 *x)
{
    //////////////////////////////////////////////////////////////////////////////////
    //                              Jeden pomiar                                    //
    //////////////////////////////////////////////////////////////////////////////////
    if (currentMeasurementType == single)
    {
        if(mbSonar.wybrany_czujnik == Sensor::lewy)
        {
            ui->sonarMap->graph(0)->clearData();
            ui->sonarMap->graph(1)->clearData();
            ui->sonarMap->graph(2)->clearData();
            ui->sonarMap->graph(3)->clearData();

            float angle_tmp = mbSonar.angle;
            mbSonar.angle = 0;
            drawDataOnMap(echo_ptr);
            echo_ptr->restoreToDefaultEcho();
            ui->sonarMap->yAxis->setRange(0, dystans_y_max * 1.1);
            ui->sonarMap->xAxis->setRange(-1, 1);
            ui->sonarMap->replot();
            mbSonar.angle = angle_tmp;
            *x = 0;

            if (mbSonar.tryb_pracy == Sensor::podwojny && loadOperation != true)
            {
                stm32_serial->write("sr");
                mbSonar.wybrany_czujnik = Sensor::prawy;
            }
        }
        else if (mbSonar.wybrany_czujnik == Sensor::prawy)
        {
            if (mbSonar.tryb_pracy == Sensor::pojedynczy)
            {
                ui->sonarMap->graph(0)->clearData();
                ui->sonarMap->graph(1)->clearData();
                ui->sonarMap->graph(2)->clearData();
                ui->sonarMap->graph(3)->clearData();
            }

            float angle_tmp = mbSonar.angle;
            mbSonar.angle = 0;
            drawDataOnMap(echo_ptr);
            echo_ptr->restoreToDefaultEcho();
            ui->sonarMap->yAxis->setRange(0, dystans_y_max * 1.1);
            ui->sonarMap->xAxis->setRange(-1, 1);
            ui->sonarMap->replot();
            mbSonar.angle = angle_tmp;
            *x = 0;

            if (mbSonar.tryb_pracy == Sensor::podwojny)
                mbSonar.wybrany_czujnik = Sensor::lewy;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    //                           Skanowanie otoczenia                               //
    //////////////////////////////////////////////////////////////////////////////////
    else if (currentMeasurementType == scan)
    {
        /* Skanowanie jednym czujnikiem */
        if (mbSonar.tryb_pracy == Sensor::pojedynczy)
        {
            drawDataOnMap(echo_ptr);
            echo_ptr->restoreToDefaultEcho();
            ui->sonarMap->xAxis->setRange(dystans_x_min * 1.1, dystans_x_max * 1.1);
            ui->sonarMap->yAxis->setRange(0, dystans_y_max * 1.1);
            *x = 0;

            if ((mbSonar.angle + mbSonar.angleStep) <= mbSonar.maxAngle && loadOperation != true)
            {
                if(mbSonar.wybrany_czujnik == Sensor::lewy)
                {
                    if (!loadOperation)
                        stm32_serial->write("c+");
                    QThread::msleep(50);
                    mbSonar.angle += mbSonar.angleStep;
                    if (!loadOperation)
                        stm32_serial->write("cl");
                }
                else if(mbSonar.wybrany_czujnik == Sensor::prawy)
                {
                    if (!loadOperation)
                        stm32_serial->write("c+");
                    QThread::msleep(50);
                    mbSonar.angle += mbSonar.angleStep;
                    if (!loadOperation)
                        stm32_serial->write("cr");
                }
            }
            else if (loadOperation != true)
            {
                QThread::msleep(50);
                stm32_serial->write("c+");
                mbSonar.angle = ui->spinBox->value();
                currentMeasurementType = none;
                dystans_y_max = 0;
                dystans_x_min = 0;
                dystans_x_max = 0;
            }
        }

        /* Skanowanie dwoma czujnikami */
        if (mbSonar.tryb_pracy == Sensor::podwojny)
        {
            drawDataOnMap(echo_ptr);
            echo_ptr->restoreToDefaultEcho();
            ui->sonarMap->xAxis->setRange(dystans_x_min * 1.1, dystans_x_max * 1.1);
            ui->sonarMap->yAxis->setRange(0, dystans_y_max * 1.1);
            *x = 0;

            if(mbSonar.wybrany_czujnik == Sensor::lewy && loadOperation != true)
            {
                mbSonar.wybrany_czujnik = Sensor::prawy;
                stm32_serial->write("cr");
                QThread::msleep(50);
            }
            else if(mbSonar.wybrany_czujnik == Sensor::prawy && loadOperation != true)
            {
                mbSonar.wybrany_czujnik = Sensor::lewy;

                if ((mbSonar.angle + mbSonar.angleStep) <= mbSonar.maxAngle)
                {
                    if (!loadOperation)
                        stm32_serial->write("c+");
                    QThread::msleep(50);
                    mbSonar.angle += mbSonar.angleStep;
                    stm32_serial->write("cl");
                }
                else
                {
                    QThread::msleep(50);
                    stm32_serial->write("c+");
                    mbSonar.angle = ui->spinBox->value();
                    currentMeasurementType = none;
                    dystans_y_max = 0;
                    dystans_x_min = 0;
                    dystans_x_max = 0;
                }
            }
        }
    }
    echo_ptr->deleteResults();
}

void MainWindow::on_loadBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open file"),
                "/home/marekf/Dokumenty/pwr/mgr/build/build-sonar_app-Desktop_Qt_5_6_0_GCC_64bit-Debug/data",
                "Text file (*txt)");
    QFile fileToLoad(fileName);

    Echo echo2;
    QString x_str, adc_str, angle_str;
    quint16 x_tmp, adc_tmp;
    float angle_tmp;
    QStringList list_tmp;
    measurementType mTmp = currentMeasurementType;
    float mAngle = mbSonar.angle;
    Sensor::czujnik mCzuj = mbSonar.wybrany_czujnik;
    Sensor::_tryb_pracy mTryb = mbSonar.tryb_pracy;

    loadOperation = true;

    if (fileToLoad.open(QIODevice::ReadOnly))
    {
        QTextStream in(&fileToLoad);
        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (line == "SIN")
                currentMeasurementType = single;
            else if (line == "SCA")
                currentMeasurementType = scan;
            else if (line == "POJ")
                mbSonar.tryb_pracy = Sensor::pojedynczy;
            else if (line == "POD")
                mbSonar.tryb_pracy = Sensor::podwojny;
            else if (line == "L")
                mbSonar.wybrany_czujnik = Sensor::lewy;
            else if (line == "R")
                mbSonar.wybrany_czujnik = Sensor::prawy;
            else if (line.count(":")) {
                list_tmp = line.split(":");
                angle_str = list_tmp[1];
                angle_tmp = angle_str.toFloat();
                mbSonar.angle = angle_tmp;
            }
            else if (line != "ANALOG_ENVELOPE_END"){
                list_tmp = line.split("\t");
                x_str   = list_tmp[0];
                adc_str = list_tmp[1];
                x_tmp   = x_str.toUInt();
                adc_tmp = adc_str.toUInt();
                echo2.processSignal(mbSonar, adc_tmp, x_tmp, threshold_value);
                if (x_tmp == MAX_DATA) {
                    dataHandler(&echo2, &x_tmp);
                }
            }
        }
        fileToLoad.close();
        loadOperation = false;
        currentMeasurementType = mTmp;
        mbSonar.wybrany_czujnik = mCzuj;
        mbSonar.tryb_pracy = mTryb;
        mbSonar.angle = mAngle;
    }

}

void MainWindow::drawDataOnMap(Echo *echo)
{
    ui->sonarMap->graph(0)->setPen(QPen(Qt::blue));
    ui->sonarMap->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->sonarMap->graph(0)->setLineStyle(QCPGraph::lsNone);

    ui->sonarMap->graph(1)->setPen(QPen(Qt::red));
    ui->sonarMap->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->sonarMap->graph(1)->setLineStyle(QCPGraph::lsNone);

    ui->sonarMap->graph(2)->setPen(QPen(Qt::darkGreen));
    ui->sonarMap->graph(2)->setScatterStyle(QCPScatterStyle::ssStar);
    ui->sonarMap->graph(2)->setLineStyle(QCPGraph::lsNone);

    ui->sonarMap->graph(3)->setPen(QPen(Qt::darkMagenta));
    ui->sonarMap->graph(3)->setScatterStyle(QCPScatterStyle::ssTriangle);
    ui->sonarMap->graph(3)->setLineStyle(QCPGraph::lsNone);

    short detObjNum = echo->getNumberOfObjects();
    double *detectionPoints = echo->calculateDetectionPoints(mbSonar, ui->doubleSpinBox_calibLeft->value(), ui->doubleSpinBox_calibRight->value());

    if (dystans_y_max < echo->getYmax())
        dystans_y_max = echo->getYmax();

    if (dystans_x_min > echo->getXmin())
        dystans_x_min = echo->getXmin();

    if (dystans_x_max < echo->getXmax())
        dystans_x_max = echo->getXmax();

    short index = 0;

    for (short echoNum = 0; echoNum < (detObjNum * 2); echoNum += 2)
    {
        if (ui->rBtn_TOF_scan->isChecked())
        {
            if (mbSonar.wybrany_czujnik == Sensor::lewy) {
                ui->sonarMap->graph(0)->addData(detectionPoints[echoNum], detectionPoints[echoNum + 1]);
                /*double ustawione = ui->doubleSpinBox_calibLeft->value();
                double calib = (0.5*ustawione)/detectionPoints[echoNum + 1];
                QMessageBox::information(this, "calibraiton", QString::number(detectionPoints[echoNum + 1]));*/
            }
            else {
                ui->sonarMap->graph(1)->addData(detectionPoints[echoNum], detectionPoints[echoNum + 1]);
                /*double ustawione = ui->doubleSpinBox_calibRight->value();
                double calib = (0.5*ustawione)/detectionPoints[echoNum + 1];
                QMessageBox::information(this, "calibraiton", QString::number(detectionPoints[echoNum + 1]));*/
            }
        }
        else if (ui->rBtn_PAS_scan->isChecked())
        {
            float offset = 0.02;
            double dystans_y_cpy, dystans_x_cpy;
            dystans_x_cpy = detectionPoints[echoNum];
            dystans_y_cpy = detectionPoints[echoNum + 1];

            for (short i = 0; i < echo->getEchoStrengthValue(index); i++)
            {
                if (mbSonar.wybrany_czujnik == Sensor::lewy)
                    ui->sonarMap->graph(0)->addData(dystans_x_cpy, dystans_y_cpy);
                else
                    ui->sonarMap->graph(1)->addData(dystans_x_cpy, dystans_y_cpy);

                dystans_y_cpy += cos(mbSonar.angle*PI/180) * offset;
                if (abs(mbSonar.angle) > 0.001)
                    dystans_x_cpy += sin(mbSonar.angle*PI/180) * offset;
            }
        }
        index++;
    }

    /* Algorithm 1
     * The computations are performed here, not in the 'echo' object
     */
    if ((mbSonar.algorithm == Sensor::alg1 || mbSonar.algorithm == Sensor::alg1_and_trian)
            && mbSonar.wybrany_czujnik == Sensor::prawy && ui->rBtn_TOF_scan->isChecked()) {
        short alg1_index = 0;
        double alg1_dystans_xy[2];
        while (echo->detDistanceAlg1[alg1_index] > 0.01) {
            alg1_dystans_xy[1] = cos(mbSonar.angle*PI/180) * echo->detDistanceAlg1[alg1_index];
            alg1_dystans_xy[0] = sin(mbSonar.angle*PI/180) * echo->detDistanceAlg1[alg1_index];
            ui->sonarMap->graph(2)->addData(alg1_dystans_xy[0], alg1_dystans_xy[1]);
            alg1_index++;
        }
    }
    else if ((mbSonar.algorithm == Sensor::alg1 || mbSonar.algorithm == Sensor::alg1_and_trian)
             && mbSonar.wybrany_czujnik == Sensor::prawy && ui->rBtn_PAS_scan->isChecked()) {
        short alg1_index = 0;
        double alg1_dystans_xy[2];
        float offset = 0.02;

        while (echo->detDistanceAlg1[alg1_index] > 0.01) {

            alg1_dystans_xy[0] = sin(mbSonar.angle*PI/180) * echo->detDistanceAlg1[alg1_index];
            alg1_dystans_xy[1] = cos(mbSonar.angle*PI/180) * echo->detDistanceAlg1[alg1_index];

            for (short i = 0; i < echo->detDistanceAlg1_Strength[alg1_index]; i++) {
                ui->sonarMap->graph(2)->addData(alg1_dystans_xy[0], alg1_dystans_xy[1]);
                alg1_dystans_xy[1] += cos(mbSonar.angle*PI/180) * offset;
                if (abs(mbSonar.angle) > 0.001)
                    alg1_dystans_xy[0] += sin(mbSonar.angle*PI/180) * offset;
            }

            alg1_index++;
        }
    }
    if ((mbSonar.algorithm == Sensor::triangulation || mbSonar.algorithm == Sensor::alg1_and_trian)
            //&& mbSonar.wybrany_czujnik == Sensor::prawy && ui->rBtn_TOF_scan->isChecked()) {
            && mbSonar.wybrany_czujnik == Sensor::prawy) {
        short trIndex = 0;
        while (echo->getTrianX(trIndex) > 0.01 || echo->getTrianY(trIndex) > 0.01) {
            ui->sonarMap->graph(3)->addData(echo->getTrianX(trIndex), echo->getTrianY(trIndex));
            ui->lineEditX->setText(QString::number(echo->getTrianX(trIndex)));
            ui->lineEditY->setText(QString::number(echo->getTrianY(trIndex)));
            trIndex++;
        }
    }

    ui->sonarMap->graph(0)->rescaleAxes(true);
    ui->sonarMap->graph(3)->rescaleAxes(true);
    ui->sonarMap->replot();
}

void MainWindow::drawMap(QCustomPlot *customPlot)
{
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red));

    customPlot->addGraph();
    customPlot->graph(2)->setPen(QPen(Qt::darkGreen));

    customPlot->addGraph();
    customPlot->graph(3)->setPen(QPen(Qt::darkYellow));

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 0.5);

    /* Enable the 'drag' option */
    customPlot->setInteractions(customPlot->interactions() | QCP::iRangeDrag);

    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(zoomWithScroll(QWheelEvent*)));
    connect(customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(showPointCoordinates(QMouseEvent*)));

    customPlot->replot();
}

void MainWindow::drawSignalPlot(QCustomPlot *customPlot)
{
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red));

    customPlot->addGraph();
    customPlot->graph(2)->setPen(QPen(Qt::black));

    for (int i = 0; i < MAX_DATA; i++)
    {
        customPlot->graph(1)->addData(i, threshold_value);
    }

    customPlot->xAxis->setRange(0, 400);
    customPlot->yAxis->setRange(0, 2000);
    customPlot->replot();
}

void MainWindow::threshold_changed()
{
    threshold_value = ui->signalThresholdValueBox->value();

    ui->sonarSignal->graph(1)->clearData();

    for (int i = 0; i < MAX_DATA; i++)
    {
        ui->sonarSignal->graph(1)->addData(i, threshold_value);
    }

    ui->sonarSignal->replot();
}

void MainWindow::on_actionConnect_triggered()
{

}

void MainWindow::on_singleMeasurementBtn_clicked()
{
    if ( !(ui->cBox_left_sensor->isChecked()) && !(ui->cBox_right_sensor->isChecked()) )
        QMessageBox::critical(this, "Error", "No sensor has been chosen!");
    else
    {
        currentMeasurementType = single;
        mbSonar.currentFilter = 0;
        ui->sonarSignal->graph(0)->clearData();
        ui->sonarSignal->graph(2)->clearData();
        if (mbSonar.wybrany_czujnik == Sensor::lewy)
            stm32_serial->write("sl");
        else if (mbSonar.wybrany_czujnik == Sensor::prawy)
            stm32_serial->write("sr");
    }
}

void MainWindow::on_scanBtn_clicked()
{
    if ( !(ui->cBox_left_sensor->isChecked()) && !(ui->cBox_right_sensor->isChecked()) )
        QMessageBox::critical(this, "Error", "No sensor has been chosen!");
    else
    {
        currentMeasurementType = scan;
        mbSonar.currentFilter = 0;
        ui->sonarMap->graph(0)->clearData();
        ui->sonarMap->graph(1)->clearData();
        ui->sonarMap->graph(2)->clearData();
        ui->sonarMap->graph(3)->clearData();
        ui->sonarSignal->graph(0)->clearData();
        if (mbSonar.wybrany_czujnik == Sensor::prawy)
            stm32_serial->write("cr");
        else
            stm32_serial->write("cl");
    }
}

void MainWindow::on_updateAngleBtn_clicked()
{
    mbSonar.angle = ui->spinBox->value();
    mbSonar.angleStep = ui->doubleSpinBox->value();
    mbSonar.maxAngle = ui->spinBox_2->value();

    QString myInitAngle = "a" + QString::number(ui->spinBox->value()) + "\n";
    QByteArray myInitAngleArray (myInitAngle.toStdString().c_str());
    stm32_serial->write(myInitAngleArray);

    QString myFinalAngle = QString::number(ui->spinBox_2->value()) + "\n";
    QByteArray myFinalAngleArray (myFinalAngle.toStdString().c_str());
    stm32_serial->write(myFinalAngleArray);

    QString myStepAngle = QString::number((quint16)(10*(ui->doubleSpinBox->value()))) + "\n";
    QByteArray myStepArray (myStepAngle.toStdString().c_str());
    stm32_serial->write(myStepArray);
}

void MainWindow::on_actionSerial_port_triggered()
{
    settingsSerDialog = new SettingsSerialDialog(this);
    settingsSerDialog->show();
}

void MainWindow::on_connectBtn_clicked()
{
    stm32_serial = new QSerialPort(this);

    /*  Checks, whether the STM32 serial port is on or not  */
    stm32_available = false;

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if ( serialPortInfo.manufacturer() == "STMicroelectronics" &&
             serialPortInfo.description()  == "STM32 STLink")
        {
            stm32_available = true;
            stm32_port_name = serialPortInfo.portName();
        }
    }

    /*  If the port is available  */
    if (stm32_available)
    {
        stm32_serial->setPortName(stm32_port_name);
        stm32_serial->open(QSerialPort::ReadWrite);
        stm32_serial->setBaudRate(QSerialPort::Baud115200);
        stm32_serial->setDataBits(QSerialPort::Data8);
        stm32_serial->setFlowControl(QSerialPort::NoFlowControl);
        stm32_serial->setParity(QSerialPort::NoParity);
        stm32_serial->setStopBits(QSerialPort::OneStop);

        QMessageBox::information(this, "Serial port connection", "The connection has been successfully established!");

        ui->tabWidget->setEnabled(true);
        ui->singleMeasurementBtn->setEnabled(true);
        ui->scanBtn->setEnabled(true);

        QObject::connect(stm32_serial, SIGNAL(readyRead()), this, SLOT(readSerialData()));
    } else {
        QMessageBox::critical(this, "Error (serial port connection)", "The specified serial port has not been found.");
    }
}

void MainWindow::on_cBox_left_sensor_stateChanged(int arg1)
{
    if ( (ui->cBox_left_sensor->isChecked()) && !(ui->cBox_right_sensor->isChecked()) )
    {
        mbSonar.tryb_pracy      = Sensor::pojedynczy;
        mbSonar.wybrany_czujnik = Sensor::lewy;
    }
    else if ( !(ui->cBox_left_sensor->isChecked()) && (ui->cBox_right_sensor->isChecked()) )
    {
        mbSonar.tryb_pracy      = Sensor::pojedynczy;
        mbSonar.wybrany_czujnik = Sensor::prawy;
    }
    else
    {
        mbSonar.tryb_pracy      = Sensor::podwojny;
        mbSonar.wybrany_czujnik = Sensor::lewy;         // zarowno dla zaznaczonych dwoch pol, jak i dwoch odznaczonych wykona sie pomiar przy
                                                // uzyciu dwoch czujnikow; rozpoczyna LEWY
    }
}

void MainWindow::on_cBox_right_sensor_stateChanged(int arg1)
{
    if ( (ui->cBox_left_sensor->isChecked()) && !(ui->cBox_right_sensor->isChecked()) )
    {
        mbSonar.tryb_pracy      = Sensor::pojedynczy;
        mbSonar.wybrany_czujnik = Sensor::lewy;
    }
    else if ( !(ui->cBox_left_sensor->isChecked()) && (ui->cBox_right_sensor->isChecked()) )
    {
        mbSonar.tryb_pracy      = Sensor::pojedynczy;
        mbSonar.wybrany_czujnik = Sensor::prawy;
    }
    else
    {
        mbSonar.tryb_pracy      = Sensor::podwojny;
        mbSonar.wybrany_czujnik = Sensor::lewy;         // zarowno dla zaznaczonych dwoch pol, jak i dwoch odznaczonych wykona sie pomiar przy
                                                // uzyciu dwoch czujnikow; rozpoczyna LEWY
    }
}

//////////////////////////////////////////////////////////////////
/// Mouse - context menu
void MainWindow::contexMenu_setBothSonarsInvisible()
{
    ui->sonarMap->graph(0)->setVisible(false);
    ui->sonarMap->graph(1)->setVisible(false);
    ui->sonarMap->replot();
}

void MainWindow::contexMenu_setBothSonarsVisible()
{
    ui->sonarMap->graph(0)->setVisible(true);
    ui->sonarMap->graph(1)->setVisible(true);
    ui->sonarMap->replot();
}

void MainWindow::contexMenu_setLeftSonarInvisible()
{
    ui->sonarMap->graph(0)->setVisible(false);
    ui->sonarMap->replot();
}

void MainWindow::contexMenu_setLeftSonarVisible()
{
    ui->sonarMap->graph(0)->setVisible(true);
    ui->sonarMap->replot();
}

void MainWindow::contexMenu_setRightSonarInvisible()
{
    ui->sonarMap->graph(1)->setVisible(false);
    ui->sonarMap->replot();
}

void MainWindow::contexMenu_setRightSonarVisible()
{
    ui->sonarMap->graph(1)->setVisible(true);
    ui->sonarMap->replot();
}
/// Mouse - context menu
//////////////////////////////////////////////////////////////////

void MainWindow::contextMenuRequest(QPoint pos)
{
    QMenu *contextMenu = new QMenu(this);
    contextMenu->setAttribute(Qt::WA_DeleteOnClose);

    contextMenu->addAction("Hide data from both sensors", this, SLOT(contexMenu_setBothSonarsInvisible()));
    contextMenu->addAction("Show data from both sensors", this, SLOT(contexMenu_setBothSonarsVisible()));
    contextMenu->addAction("Hide data from left sensor", this, SLOT(contexMenu_setLeftSonarInvisible()));
    contextMenu->addAction("Show data from left sensor", this, SLOT(contexMenu_setLeftSonarVisible()));
    contextMenu->addAction("Hide data from right sensor", this, SLOT(contexMenu_setLeftSonarInvisible()));
    contextMenu->addAction("Show data from right sensor", this, SLOT(contexMenu_setLeftSonarVisible()));

    contextMenu->popup(ui->sonarMap->mapToGlobal(pos));
}

void MainWindow::on_spinBox_alg1_valueChanged(double arg1)
{
    mbSonar.alg1_radius = arg1;
}


void MainWindow::on_lSon_visible_stateChanged(int arg1)
{
    if (ui->lSon_visible->isChecked())
        ui->sonarMap->graph(0)->setVisible(true);
    else
        ui->sonarMap->graph(0)->setVisible(false);

    ui->sonarMap->replot();
}

void MainWindow::on_rSon_visible_stateChanged(int arg1)
{
    if (ui->rSon_visible->isChecked())
        ui->sonarMap->graph(1)->setVisible(true);
    else
        ui->sonarMap->graph(1)->setVisible(false);

    ui->sonarMap->replot();
}

void MainWindow::on_alg1_visible_stateChanged(int arg1)
{
    if (ui->alg1_visible->isChecked())
        ui->sonarMap->graph(2)->setVisible(true);
    else
        ui->sonarMap->graph(2)->setVisible(false);

    ui->sonarMap->replot();
}

void MainWindow::on_cBox_Tr_visible_clicked()
{
    if (ui->cBox_Tr_visible->isChecked())
        ui->sonarMap->graph(3)->setVisible(true);
    else
        ui->sonarMap->graph(3)->setVisible(false);

    ui->sonarMap->replot();
}





void MainWindow::showPointCoordinates(QMouseEvent *event)
{
    float x = roundf(ui->sonarMap->xAxis->pixelToCoord(event->pos().x()) * 10000)/10000;
    float y = roundf(ui->sonarMap->yAxis->pixelToCoord(event->pos().y()) * 10000)/10000;
    float dystans_context = roundf(sqrt(x*x+y*y) * 10000)/10000;
    setToolTip(QString("x: %1\ny: %2\nd: %3").arg(x).arg(y).arg(dystans_context));
}

void MainWindow::on_rBtn_Trian_clicked()
{
    if (ui->rBtn_Trian->isChecked()) {
        if (ui->cBox_alg1->isChecked())
            mbSonar.algorithm = Sensor::alg1_and_trian;
        else
            mbSonar.algorithm = Sensor::triangulation;

        ui->cBox_left_sensor->setChecked(true);
        ui->cBox_right_sensor->setChecked(true);
        ui->cBox_left_sensor->setDisabled(true);
        ui->cBox_right_sensor->setDisabled(true);

        mbSonar.tryb_pracy      = Sensor::podwojny;
        mbSonar.wybrany_czujnik = Sensor::lewy;
    }
    else if (!(ui->cBox_alg1->isChecked())) {
        ui->cBox_left_sensor->setEnabled(true);
        ui->cBox_right_sensor->setEnabled(true);
        mbSonar.algorithm = Sensor::alg0;
    }
    else {
        mbSonar.algorithm = Sensor::alg1;
    }
}

void MainWindow::on_cBox_alg1_clicked()
{
    if (ui->cBox_alg1->isChecked()) {
        if (ui->rBtn_Trian->isChecked())
            mbSonar.algorithm = Sensor::alg1_and_trian;
        else
            mbSonar.algorithm = Sensor::alg1;

        ui->cBox_left_sensor->setChecked(true);
        ui->cBox_right_sensor->setChecked(true);
        ui->cBox_left_sensor->setDisabled(true);
        ui->cBox_right_sensor->setDisabled(true);

        mbSonar.tryb_pracy      = Sensor::podwojny;
        mbSonar.wybrany_czujnik = Sensor::lewy;
    }
    else if (!(ui->rBtn_Trian->isChecked())) {
        ui->cBox_left_sensor->setEnabled(true);
        ui->cBox_right_sensor->setEnabled(true);
        mbSonar.algorithm = Sensor::alg0;
    }
    else {
        mbSonar.algorithm = Sensor::triangulation;
    }
}

/*---------------------------------------------------------------*/
/*--------------------------- ZOOM ------------------------------*/
/*---------------------------------------------------------------*/

void MainWindow::zoomWithScroll(QWheelEvent *event)
{
    QPoint scrollNum = event->angleDelta();

    if (!scrollNum.isNull()) {
        if (scrollNum.ry() < 0) {
            ui->sonarMap->xAxis->scaleRange(1.2,0);
            ui->sonarMap->yAxis->scaleRange(1.2,0);
        } else {
            ui->sonarMap->xAxis->scaleRange(0.8,0);
            ui->sonarMap->yAxis->scaleRange(0.8,0);
        }
        ui->sonarMap->replot();
    }
}

void MainWindow::on_btn_save_clicked()
{
    QString fileName = ui->saveNameEdit->text();
    if (fileName != NULL) {
        ui->sonarMap->saveJpg(fileName);
    } else {
        QMessageBox::critical(this, "Save failed!", "Specify the file name.");
    }
}



void MainWindow::on_interpolation_cBox_toggled(bool checked)
{
    if (checked)
        mbSonar.interpolation = true;
    else
        mbSonar.interpolation = false;
}
