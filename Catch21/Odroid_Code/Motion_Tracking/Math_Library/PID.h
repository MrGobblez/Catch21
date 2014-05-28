#ifndef PID_H
#define PID_H

#include <time.h>

class PID
{
public:
    //Constructor
    PID();

public:
    //PID calculations
    double calculate(int desiredSpeed);

private:
    //Functions
    timespec diff(timespec previous, timespec now);

    //Sampling & time control
    clock_gettime currentTime;
    clock_gettime lastTime;
    int sampleRate; //Has to be in nanoseconds!

    //Computing variables
    double derivative;
    double lastError;
    double integral;
    double error;

    //Tuning variables
    double kp;
    double ki;
    double kd;


    //Evaluated variables
    int lastSpeed;
    int outputSpeed;
};

#endif
