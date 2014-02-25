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
    void speedControl();

    // Pinout
    byte positiveTop;
    byte negativeTop;
    byte positiveBottom;
    byte negativeBottom;
    byte enablerTop;
    byte enablerBottom;

    // Defining off zone
    byte upperThreshold;
    byte lowerThreshold;

    // Variables
    byte delayTime;

};

#endif
