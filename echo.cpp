#include "echo.h"

Echo::Echo()
{

}

void Echo::calculateEchoStrength()
{
    delta_time = echo_end - echo_start;
    if (delta_time <= 13)
    {
        first_echo_samples_no = 1;
    }
    else if (delta_time <= 26)
    {
        first_echo_samples_no = 2;
    }
    else
    {
        first_echo_samples_no = 3;
    }
}

void Echo::setEchoDetTime(unsigned int time_start)
{
    echo_start = time_start;
}

void Echo::setEchoEndTime(unsigned int time_end)
{
    echo_end = time_end;
    calculateEchoStrength();
}
