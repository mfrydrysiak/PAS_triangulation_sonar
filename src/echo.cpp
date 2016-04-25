#include "echo.h"
#include "sensor.h"

#define SENSOR_OFFSET   0.01175
#define ALG1_DIST       0.01

Echo::Echo()
{
    objNum                      = 0;
    transducerActive            = false;
    signalGenerationFinished    = false;
    echoDetection               = false;
    range_Y_max = range_X_max = range_X_min = 0;
    for (short i = 0; i < 20; i++)
        echoStartTab[i] = 0;
    for (short i = 0; i < 20; i++)
        echoEndTab[i] = 0;
}

void Echo::processSignal(quint16 adc, quint16 x, int threshold)
{
    /* Wait for the acoustic wave generation period */
    if (signalGenerationFinished == false && adc > threshold && transducerActive == false) {
        transducerActive = true;
        waveGenerationTime = x;
    }
    else if (signalGenerationFinished == false && adc < threshold && transducerActive == true)
        signalGenerationFinished = true;

    if (signalGenerationFinished == true) {
        if (echoDetection == false && adc > threshold) {
            echoDetection = true;
            echoStartTab[objNum] = x;
        }
        else if (echoDetection == true && adc < threshold) {
            echoDetection = false;
            echoEndTab[objNum] = x;
            objNum++;
        }
    }
}

double* Echo::calculateDetectionPoints(Sensor mySensor)
{
    double dystans[objNum];
    resultsXY = new double[(objNum*2)];
    double dystans_xy[2];
    short dt;
    short index = 0;

    /* Clear table for the algorithm 1 */
    if (mySensor.wybrany_czujnik == Sensor::lewy)
        for (short i = 0; i < 10; i++) {
            detDistanceAlg1_left[i] = 0;
            detDistanceAlg1_leftSamplesNo = 0;
            detDistanceAlg1_leftEchoStrength[i] = 0;
            detDistanceAlg1_right[i] = 0;
            detDistanceAlg1_rightSamplesNo = 0;
            detDistanceAlg1_rightEchoStrength[i] = 0;

            detDistanceAlg1[i] = 0;
            detDistanceAlg1_Strength[i] = 0;
        }

    for (short echoIndex = 0; echoIndex < objNum; echoIndex++) {
        echoStrengthValues[echoIndex] = calculateEchoStrength(echoEndTab[echoIndex] - echoStartTab[echoIndex]);

        if (mySensor.wybrany_czujnik == Sensor::lewy)
            detDistanceAlg1_leftEchoStrength[echoIndex] = echoStrengthValues[echoIndex];
        else
            detDistanceAlg1_rightEchoStrength[echoIndex] = echoStrengthValues[echoIndex];

        dt = echoEndTab[echoIndex] - waveGenerationTime;
        dystans[echoIndex] = (343*(dt*0.000025))/2;
    }

    /* Algorithm 1 - accept neighbours */
    if (mySensor.algorithm == Sensor::alg1) {
        /* Acquire data for the left sensor - max. 10 samples */
        if (mySensor.wybrany_czujnik == Sensor::lewy) {
            for (int i = 0; i < objNum && i < 10; i++) {
                detDistanceAlg1_left[i] = dystans[i];
                detDistanceAlg1_leftSamplesNo = i + 1;
            }
        }
        /* Compare data from the right sensor with data from the left one and choose only close samples */
        else if (mySensor.wybrany_czujnik == Sensor::prawy) {
            for (int i = 0; i < objNum && i < 10; i++) {
                detDistanceAlg1_right[i] = dystans[i];
                detDistanceAlg1_rightSamplesNo = i + 1;
            }
            /* Comparision */
            short index_alg1 = 0;
            for (int j = 0; j < detDistanceAlg1_rightSamplesNo; j++)
                for (int k = 0; k < detDistanceAlg1_leftSamplesNo; k++) {
                    if (abs(detDistanceAlg1_right[j] - detDistanceAlg1_left[k]) < mySensor.alg1_radius) {
                        detDistanceAlg1[index_alg1] = ((detDistanceAlg1_right[j] + detDistanceAlg1_left[k]) / 2);
                        detDistanceAlg1_Strength[index_alg1] = static_cast<short>((detDistanceAlg1_rightEchoStrength[j] +
                                                                                   detDistanceAlg1_leftEchoStrength[k]) / 2);
                        index_alg1++;
                    }
                }
        }
    }


    for (short echoIndex = 0; echoIndex < (objNum * 2); echoIndex += 2) {
        if (mySensor.wybrany_czujnik == Sensor::lewy) {
            dystans_xy[1] = cos(mySensor.angle*3.1415/180) * dystans[index] + SENSOR_OFFSET * sin(mySensor.angle*3.1415/180);
            dystans_xy[0] = sin(mySensor.angle*3.1415/180) * dystans[index] - SENSOR_OFFSET * cos(mySensor.angle*3.1415/180);
        }
        else {
            dystans_xy[1] = cos(mySensor.angle*3.1415/180) * dystans[index] - SENSOR_OFFSET * sin(mySensor.angle*3.1415/180);
            dystans_xy[0] = sin(mySensor.angle*3.1415/180) * dystans[index] + SENSOR_OFFSET * cos(mySensor.angle*3.1415/180);
        }
        resultsXY[echoIndex] = dystans_xy[0];
        resultsXY[echoIndex + 1] = dystans_xy[1];

        index++;

        if (dystans_xy[1] > range_Y_max)
            range_Y_max = dystans_xy[1];
        if (dystans_xy[0] > range_X_max)
            range_X_max = dystans_xy[0];
        if (dystans_xy[0] < range_X_min)
            range_X_min = dystans_xy[0];
    }
    return resultsXY;
}

double Echo::getYmax()
{
    return range_Y_max;
}

double Echo::getXmax()
{
    return range_X_max;
}

double Echo::getXmin()
{
    return range_X_min;
}

short Echo::getNumberOfObjects()
{
    return objNum;
}

short Echo::getEchoStrengthValue(short index)
{
    return echoStrengthValues[index];
}

short Echo::calculateEchoStrength(quint16 echoStr)
{
    return (static_cast<int>(echoStr / 13) + 1);
}

void Echo::deleteResults()
{
    delete [] resultsXY;
}

void Echo::restoreToDefaultEcho()
{
    objNum                      = 0;
    transducerActive            = false;
    signalGenerationFinished    = false;
    echoDetection               = false;
    range_Y_max = range_X_max = range_X_min = 0;
    for (short i = 0; i < 20; i++)
        echoStartTab[i] = 0;
    for (short i = 0; i < 20; i++)
        echoEndTab[i] = 0;
}
