#ifndef SENSOR_H
#define SENSOR_H

enum czujnik { lewy  = 0,
               prawy = 1  };

enum _tryb_pracy { pojedynczy = 0,
                   podwojny   = 1  };

enum _algorithm { alg0 = 0,
                  alg1 = 1  };

class Sensor
{
public:
    /* Konstruktor */
    Sensor();

    /* Funkcje publiczne klasy */
    void zmien_czujnik();

    /* Zmienne publiczne */
    czujnik     wybrany_czujnik;
    _tryb_pracy tryb_pracy;
    _algorithm  algorithm;
    float       angleStep;
    float       angle;
    float       maxAngle;

};

#endif // SENSOR_H
