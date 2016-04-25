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

#define MAX_DATA        600
#define SILENCE_SIGNAL  160

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threshold_value = ui->signalThresholdValueBox->value();

    drawMap(ui->sonarMap);
    drawSignalPlot(ui->sonarSignal);

    mbSonar.tryb_pracy      = Sensor::pojedynczy;
    mbSonar.wybrany_czujnik = Sensor::lewy;
    mbSonar.algorithm       = Sensor::alg0;
    mbSonar.angle           = -45.0;
    mbSonar.angleStep       = 1.0;
    mbSonar.maxAngle        = 45.0;

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

    while (stm32_serial->canReadLine())
    {
        serialBuffer = stm32_serial->readLine();
        bufferSplit = serialBuffer.split("\n");

        if (serialBuffer != "\n")
        {
            adc_val = serialBuffer.toUInt();

            echo.processSignal(adc_val, x, threshold_value);

            x++;

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

                float angle_tmp = mbSonar.angle;
                mbSonar.angle = 0;
                drawDataOnMap(&echo);
                echo.restoreToDefaultEcho();
                ui->sonarMap->yAxis->setRange(0, dystans_y_max * 1.1);
                ui->sonarMap->xAxis->setRange(-1, 1);
                ui->sonarMap->replot();
                mbSonar.angle = angle_tmp;
                x = 0;

                if (mbSonar.tryb_pracy == Sensor::podwojny)
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
                }

                float angle_tmp = mbSonar.angle;
                mbSonar.angle = 0;
                drawDataOnMap(&echo);
                echo.restoreToDefaultEcho();
                ui->sonarMap->yAxis->setRange(0, dystans_y_max * 1.1);
                ui->sonarMap->xAxis->setRange(-1, 1);
                ui->sonarMap->replot();
                mbSonar.angle = angle_tmp;
                x = 0;

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
                drawDataOnMap(&echo);
                echo.restoreToDefaultEcho();
                ui->sonarMap->xAxis->setRange(dystans_x_min * 1.1, dystans_x_max * 1.1);
                ui->sonarMap->yAxis->setRange(0, dystans_y_max * 1.1);
                x = 0;

                if ((mbSonar.angle + mbSonar.angleStep) <= mbSonar.maxAngle)
                {
                    if(mbSonar.wybrany_czujnik == Sensor::lewy)
                    {
                        stm32_serial->write("c+");
                        QThread::msleep(50);
                        mbSonar.angle += mbSonar.angleStep;
                        stm32_serial->write("cl");
                    }
                    else if(mbSonar.wybrany_czujnik == Sensor::prawy)
                    {
                        stm32_serial->write("c+");
                        QThread::msleep(50);
                        mbSonar.angle += mbSonar.angleStep;
                        stm32_serial->write("cr");
                    }
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

            /* Skanowanie dwoma czujnikami */
            if (mbSonar.tryb_pracy == Sensor::podwojny)
            {
                drawDataOnMap(&echo);
                echo.restoreToDefaultEcho();
                ui->sonarMap->xAxis->setRange(dystans_x_min * 1.1, dystans_x_max * 1.1);
                ui->sonarMap->yAxis->setRange(0, dystans_y_max * 1.1);
                x = 0;

                if(mbSonar.wybrany_czujnik == Sensor::lewy)
                {
                    mbSonar.wybrany_czujnik = Sensor::prawy;
                    stm32_serial->write("cr");
                    QThread::msleep(50);
                }
                else if(mbSonar.wybrany_czujnik == Sensor::prawy)
                {
                    mbSonar.wybrany_czujnik = Sensor::lewy;

                    if ((mbSonar.angle + mbSonar.angleStep) <= mbSonar.maxAngle)
                    {
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
        echo.deleteResults();
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

    short detObjNum = echo->getNumberOfObjects();
    double *detectionPoints = echo->calculateDetectionPoints(mbSonar);

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
            if (mbSonar.wybrany_czujnik == Sensor::lewy)
                ui->sonarMap->graph(0)->addData(detectionPoints[echoNum], detectionPoints[echoNum + 1]);
            else
                ui->sonarMap->graph(1)->addData(detectionPoints[echoNum], detectionPoints[echoNum + 1]);
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

                dystans_y_cpy += cos(mbSonar.angle*3.1415/180) * offset;
                if (abs(mbSonar.angle) > 0.001)
                    dystans_x_cpy += sin(mbSonar.angle*3.1415/180) * offset;
            }
        }
        index++;
    }

    /* Algorithm 1
     * The computations are performed here, not in the 'echo' object
     */
    if (mbSonar.algorithm == Sensor::alg1 && mbSonar.wybrany_czujnik == Sensor::prawy && ui->rBtn_TOF_scan->isChecked()) {
        short alg1_index = 0;
        double alg1_dystans_xy[2];
        while (echo->detDistanceAlg1[alg1_index] > 0.01) {
            alg1_dystans_xy[1] = cos(mbSonar.angle*3.1415/180) * echo->detDistanceAlg1[alg1_index];
            alg1_dystans_xy[0] = sin(mbSonar.angle*3.1415/180) * echo->detDistanceAlg1[alg1_index];
            ui->sonarMap->graph(2)->addData(alg1_dystans_xy[0], alg1_dystans_xy[1]);
            alg1_index++;
        }
    }
    else if (mbSonar.algorithm == Sensor::alg1 && mbSonar.wybrany_czujnik == Sensor::prawy && ui->rBtn_PAS_scan->isChecked()) {
        short alg1_index = 0;
        double alg1_dystans_xy[2];
        float offset = 0.02;

        while (echo->detDistanceAlg1[alg1_index] > 0.01) {

            alg1_dystans_xy[0] = sin(mbSonar.angle*3.1415/180) * echo->detDistanceAlg1[alg1_index];
            alg1_dystans_xy[1] = cos(mbSonar.angle*3.1415/180) * echo->detDistanceAlg1[alg1_index];

            for (short i = 0; i < echo->detDistanceAlg1_Strength[alg1_index]; i++) {
                ui->sonarMap->graph(2)->addData(alg1_dystans_xy[0], alg1_dystans_xy[1]);
                alg1_dystans_xy[1] += cos(mbSonar.angle*3.1415/180) * offset;
                if (abs(mbSonar.angle) > 0.001)
                    alg1_dystans_xy[0] += sin(mbSonar.angle*3.1415/180) * offset;
            }

            alg1_index++;
        }
    }

    ui->sonarMap->graph(0)->rescaleAxes(true);
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

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 0.5);

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
        ui->sonarMap->graph(0)->clearData();
        ui->sonarMap->graph(1)->clearData();
        ui->sonarMap->graph(2)->clearData();
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

void MainWindow::showPointCoordinates(QMouseEvent *event)
{
    float x = ui->sonarMap->xAxis->pixelToCoord(event->pos().x());
    float y = ui->sonarMap->yAxis->pixelToCoord(event->pos().y());
    float dystans_context = sqrt(x*x+y*y);
    setToolTip(QString("%1 , %2, %3").arg(x).arg(y).arg(dystans_context));
}

void MainWindow::on_rBtn_Trian_clicked()
{
    mbSonar.algorithm = Sensor::triangulation;

    ui->cBox_left_sensor->setChecked(true);
    ui->cBox_right_sensor->setChecked(true);
    ui->cBox_left_sensor->setDisabled(true);
    ui->cBox_right_sensor->setDisabled(true);

    mbSonar.tryb_pracy      = Sensor::podwojny;
    mbSonar.wybrany_czujnik = Sensor::lewy;
}

void MainWindow::on_cBox_alg1_clicked()
{
    mbSonar.algorithm = Sensor::alg1;

    ui->cBox_left_sensor->setChecked(true);
    ui->cBox_right_sensor->setChecked(true);
    ui->cBox_left_sensor->setDisabled(true);
    ui->cBox_right_sensor->setDisabled(true);

    mbSonar.tryb_pracy      = Sensor::podwojny;
    mbSonar.wybrany_czujnik = Sensor::lewy;
}
