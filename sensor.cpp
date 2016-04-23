#include "sensor.h"

Sensor::Sensor()
{

}

void Sensor::zmien_czujnik()
{
    if (wybrany_czujnik == lewy)
        wybrany_czujnik = prawy;
    else
        wybrany_czujnik = lewy;
}
