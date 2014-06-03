#ifndef PID_H
#define PID_H

#include <time.h>
#include <QtCore>

class PID
{
public:
    //Constructor
    PID();

public:
    //PID calculations
    double calculate(double userPosition);

private:
    //Functions
    timespec diff(timespec previous, timespec now);

    //Sampling & time control
    timespec currentTime;
    timespec lastTime;
    int sampleRate; //Has to be in nanoseconds!

    //Computing variables
    double derivative;
    double lastUserPos;
    double integral;
    double error;

    //Tuning variables
    double kp;
    double ki;
    double kd;


    //Evaluated variables
    double lastSpeed;
    double outputSpeed;
};

#endif
