#ifndef ECHO_H
#define ECHO_H

#include "sensor.h"
#include <QtGlobal>

using namespace std;

class Echo
{
private:
    /* Funkcje prywatne klasy */
    short   calculateEchoStrength(quint16 echoStr);
    void    echoTriangulation(Sensor mySensor, double echoL, double echoR, short index);

    /* Zmienne prywatne */
    unsigned int    echo_start;
    unsigned int    echo_end;
    quint16         echoStartTab[20];
    quint16         echoEndTab[20];
    quint16         waveGenerationTime;
    short           echoStrengthValues[20];
    unsigned short  objNum;
    double          range_Y_max, range_X_min, range_X_max;
    double          *resultsXY;
    double          triangulationX[10];
    double          triangulationY[10];
    double          detDistanceAlg1_left[10];
    double          detDistanceAlg1_right[10];
    double          detDistTrian[10];
    short           detDistanceAlg1_leftSamplesNo;
    short           detDistanceAlg1_rightSamplesNo;
    short           detDistanceAlg1_leftEchoStrength[10];
    short           detDistanceAlg1_rightEchoStrength[10];
    bool            transducerActive;
    bool            signalGenerationFinished;
    bool            echoDetection;

public:
    /* Konstruktor */
    Echo();

    /* Funkcje publiczne klasy */
    void    restoreToDefaultEcho();
    void    processSignal(quint16 adc, quint16 x, int threshold);
    void    deleteResults();
    double* calculateDetectionPoints(Sensor mySensor, unsigned short adjL, unsigned short adjR);
    double  getYmax();
    double  getXmin();
    double  getXmax();
    short   getNumberOfObjects();
    short   getEchoStrengthValue(short index);
    double  getTrianX(short i);
    double  getTrianY(short i);

    /* Zmienne */
    unsigned int    first_echo_samples_no;
    unsigned int    delta_time;
    double          filterDistTab_Left[5], filterDistTab_Right[5];
    double          detDistanceAlg1[10];
    short           detDistanceAlg1_Strength[10];

};

#endif // ECHO_H
