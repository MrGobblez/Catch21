#include "PID.h"

PID::PID()
{
    this->sampleRate = 100000000; //10samples per second.

    this->kp = 0.2;
    this->ki = 0.0;
    this->kd = 0.0;

    clock_gettime(CLOCK_REALTIME, &lastTime);
    clock_gettime(CLOCK_REALTIME, &currentTime);

    this->lastError = 0.0;
    this->error = 0.0;
    this->integral = 0.0;

    this->lastSpeed = 0.0;
    this->outputSpeed = 0.0;
}

double PID::calculate(double desiredSpeed)
{
    clock_gettime(CLOCK_REALTIME, &currentTime);
    double time = diff(lastTime, currentTime).tv_nsec;
    //Is it 0.1 or more seconds since last sample? If yes, calculate.
    if(time >= sampleRate)
    {
        //Convert from nsec to sec.
        time /= 1000000000;
        error = desiredSpeed - lastSpeed;
        integral += error*time;
        derivative = (error - lastError)/time;

        outputSpeed = (kp*error) +(ki*integral) + (kd*derivative);
        qDebug() << "error: " << error << " desiredSpeed: " << desiredSpeed << " lastSpeed: " << lastSpeed << " outputSpeed" << outputSpeed;

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
