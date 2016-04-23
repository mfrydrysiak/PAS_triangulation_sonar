#ifndef ECHO_H
#define ECHO_H


class Echo
{
private:
    /* Funkcje prywatne klasy */
    void    calculateEchoStrength();

    /* Zmienne prywatne */
    unsigned int echo_start;
    unsigned int echo_end;

public:
    /* Konstruktor */
    Echo();

    /* Funkcje publiczne klasy */
    void    setEchoDetTime(unsigned int time_start);
    void    setEchoEndTime(unsigned int time_end);

    /* Zmienne */
    unsigned int  first_echo_samples_no;
    unsigned int  delta_time;
};

#endif // ECHO_H
