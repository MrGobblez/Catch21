#include "Rig_Servo.h"

Rig_Servo::Rig_Servo()
{
    initialize();
}

//TILT FUNCTIONS
//Set tilt servo pin.
void Rig_Servo::setTiltPin(int pin)
{
    tiltServo.attach(pin);
}

//Set the max/min tilting value.
void Rig_Servo::setMaxMinTilt(int maxTilt, int minTilt)
{
    this->maxTilt = maxTilt;
    this->minTilt = minTilt;
}

//Set the "resting" position of the tilt.
void Rig_Servo::setTiltDefaultAngle(int angle)
{
    this->tiltDefault = angle;
}

//Write what position the tilt servo should move to.
void Rig_Servo::tiltServoPosition(int angle)
{
    tiltServo.write(angle);
}

//Write that tilt servo should go to "resting" position.
void Rig_Servo::tiltServoToDefaultPosition()
{
    tiltServo.write(this->tiltDefault);
}

//PAN FUNCTIONS
//Set panning servo pin.
void Rig_Servo::setPanPin(int pin)
{
    panServo.attach(pin);
}

//Set the max/min panning value.
void Rig_Servo::setMaxMinPan(int maxPan, int minPan)
{
    this->maxPan = maxPan;
    this->minPan = minPan;
}

//Set the "resting" position of the panning servo.
void Rig_Servo::setPanDefaultAngle(int angle)
{
    this->panDefault = angle;
}

//Write what position the pan servo should move to.
void Rig_Servo::panServoPosition(int angle)
{
    panServo.write(angle);
}

//Write that pan servo should go to "resting" position.
void Rig_Servo::panServoToDefaultPosition()
{
    panServo.write(this->panDefault);
}

//OTHER FUNCTIONS
//Set pins and max/min values to be used by servo.
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

