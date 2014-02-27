#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "Arduino.h"

class Motor_Driver
{
public:
    Motor_Driver();
    void movePlatform(int translation);
    void setPins(byte positiveTop, byte negativeTop, byte positiveBottom, byte negativeBottom, byte enablerTop, byte enablerBottom);


private:

    void initialize();
    void forward();
    void reverse();
    void speedControl(int translation);

    // Pinout
    byte positiveTop;
    byte negativeTop;
    byte positiveBottom;
    byte negativeBottom;
    byte enablerTop;
    byte enablerBottom;

    // Defining off zone
    int upperThreshold;
    int lowerThreshold;

    // Variables
    byte delayTime;

};

#endif
