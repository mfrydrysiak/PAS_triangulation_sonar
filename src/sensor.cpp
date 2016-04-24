#include "sensor.h"

Sensor::Sensor()
{
    alg1_radius = 0.05; // 5cm
}

void Sensor::zmien_czujnik()
{
    if (wybrany_czujnik == lewy)
        wybrany_czujnik = prawy;
    else
        wybrany_czujnik = lewy;
}
