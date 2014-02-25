#include "Rig_Servo.h"

Rig_Servo::Rig_Servo()
{
    initialize();
}

//TILT FUNCTIONS
void Rig_Servo::setTiltPin(int pin)
{
    tiltServo.attach(pin);
}

void Rig_Servo::setMaxMinTilt(int maxTilt, int minTilt)
{
    this->maxTilt = maxTilt;
    this->minTilt = minTilt;
}

void Rig_Servo::setTiltDefaultAngle(int angle)
{
    this->tiltDefault = angle;
}

void Rig_Servo::tiltServoPosition(int angle)
{
    tiltServo.write(angle);
}

void Rig_Servo::tiltServoToDefaultPosition()
{
    tiltServo.write(this->tiltDefault);
}

//PAN FUNCTIONS
void Rig_Servo::setPanPin(int pin)
{
    panServo.attach(pin);
}

void Rig_Servo::setMaxMinPan(int maxPan, int minPan)
{
    this->maxPan = maxPan;
    this->minPan = minPan;
}

void Rig_Servo::setPanDefaultAngle(int angle)
{
    this->panDefault = angle;
}

void Rig_Servo::panServoPosition(int angle)
{
    panServo.write(angle);
}

void Rig_Servo::panServoToDefaultPosition()
{
    panServo.write(this->panDefault);
}

//OTHER FUNCTIONS
void Rig_Servo::initialize()
{
    tiltPin = 5;
    panPin = 11;

    maxTilt = 120;
    tiltDefault = 95;
    minTilt = 70;
    maxPan = 142;
    panDefault = 96;
    minPan = 50;
}
