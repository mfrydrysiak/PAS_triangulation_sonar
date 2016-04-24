#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"
#include "settingsserialdialog.h"
#include "echo.h"
#include "sensor.h"

#include <QMainWindow>
#include <QSerialPort>
#include <QPoint>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void drawMap(QCustomPlot *customPlot);
    void drawSignalPlot(QCustomPlot *customPlot);
    ~MainWindow();

private slots:
    void sendAngleToSTM();
    void readSerialData();
    void drawDataOnMap(Echo *echoCpy);
    void threshold_changed();

    void on_actionSerial_port_triggered();
    void on_actionConnect_triggered();

    void contextMenuRequest(QPoint pos);

    void on_singleMeasurementBtn_clicked();

    void contexMenu_setBothSonarsInvisible();
    void contexMenu_setBothSonarsVisible();

    void on_scanBtn_clicked();

    void on_updateAngleBtn_clicked();

    void on_connectBtn_clicked();

    void on_cBox_left_sensor_stateChanged(int arg1);

    void on_cBox_right_sensor_stateChanged(int arg1);

    void on_cBox_alg1_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    SettingsSerialDialog *settingsSerDialog;

    enum measurementType {
        none = 0,
        single = 1,
        scan = 2
    };

    measurementType currentMeasurementType;

    int             threshold_value;
    Sensor          mbSonar;
    QSerialPort     *stm32_serial;
    QString         stm32_port_name;
    bool            stm32_available;
    short           t1, dt;
    double          dystans_y_max;
    double          dystans_x_min;
    double          dystans_x_max;
    QString         serialBuffer;
    QStringList     bufferSplit;
};

#endif // MAINWINDOW_H
