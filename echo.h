#ifndef ECHO_H
#define ECHO_H

#include "sensor.h"
#include <QtGlobal>

using namespace std;

class Echo
{
private:
    /* Funkcje prywatne klasy */
    short    calculateEchoStrength(quint16 echoStr);

    /* Zmienne prywatne */
    unsigned int    echo_start;
    unsigned int    echo_end;
    quint16         echoStartTab[20];
    quint16         echoEndTab[20];
    quint16         waveGenerationTime;
    short           echoStrengthValues[20];
    unsigned short  objNum;
    double          range_Y_max, range_X_min, range_X_max;
    bool            transducerActive;
    bool            signalGenerationFinished;
    bool            echoDetection;

public:
    /* Konstruktor */
    Echo();

    /* Funkcje publiczne klasy */
    void    restoreToDefaultEcho();
    void    processSignal(quint16 adc, quint16 x, int threshold);
    double* calculateDetectionPoints(Sensor mySensor);
    double  getYmax();
    double  getXmin();
    double  getXmax();
    short   getNumberOfObjects();
    short   getEchoStrengthValue(short index);

    /* Zmienne */
    unsigned int    first_echo_samples_no;
    unsigned int    delta_time;

};

#endif // ECHO_H
