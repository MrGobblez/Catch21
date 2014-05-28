#include "PID.h"

PID::PID()
{
    this->sampleRate = 100000000; //10samples per second.

    this->kp = 10.5;
    this->ki = 0.0;
    this->kd = 0.0;

    clock_gettime(CLOCK_REALTIME, &lastTime);
    clock_gettime(CLOCK_REALTIME, &currentTime);

    this->lastError = 0.0;
    this->integral = 0.0;

    this->lastSpeed = 0.0;
}

double PID::calculate(int desiredSpeed)
{
    clock_gettime(CLOCK_REALTIME, &currentTime);
    //Is it 0.1 or more seconds since last sample? If yes, calculate.
    if(diff(lastTime, currentTime).tv_nsec >= sampleRate)
    {
        error = desiredSpeed - lastSpeed;
        integral += error*0.1;
        derivative = (error - lastError)/0.1;

        outputSpeed = (int) ((kp*error) +(ki*integral) + (kd*derivative));

        lastError = error;
        lastSpeed = outputSpeed;
        clock_gettime(CLOCK_REALTIME, &lastTime);

        return outputSpeed;
    }
    else
    {
        return lastSpeed;
    }
}

//Calculates the time since last sample.
timespec PID::diff(timespec previous, timespec now)
{
    timespec temp;
    if ((now.tv_nsec-previous.tv_nsec)<0)
    {
        temp.tv_sec = now.tv_sec-previous.tv_sec-1;
        temp.tv_nsec = 1000000000+now.tv_nsec-previous.tv_nsec;
    }
    else
    {
        temp.tv_sec = now.tv_sec-previous.tv_sec;
        temp.tv_nsec = now.tv_nsec-previous.tv_nsec;
    }

    return temp;
}
