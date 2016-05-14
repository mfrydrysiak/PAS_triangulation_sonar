#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:
    /* Konstruktor */
    Sensor();

    enum czujnik { lewy  = 0,
                   prawy = 1  };

    enum _tryb_pracy { pojedynczy = 0,
                       podwojny   = 1  };

    enum _algorithm { alg0 = 0,
                      alg1 = 1,
                      triangulation = 2,
                      alg1_and_trian = 3 };

    /* Funkcje publiczne klasy */
    void zmien_czujnik();

    /* Zmienne publiczne */
    czujnik         wybrany_czujnik;
    _tryb_pracy     tryb_pracy;
    _algorithm      algorithm;
    unsigned short  currentFilter;
    double          alg1_radius;
    float           angleStep;
    float           angle;
    float           maxAngle;
    bool            interpolation;

};

#endif // SENSOR_H
