#ifndef RIG_SERVO_H
#define RIG_SERVO_H

#include "Arduino.h"
#include "Servo.h"

class Rig_Servo
{
public:
    Rig_Servo();
    

    //TILT FUNCTIONS
    void setTiltPin(int pin);
    void setMaxMinTilt(int maxTilt, int minTilt);
    void setTiltDefaultAngle(int angle);
    void tiltServoPosition(int angle);
    void tiltServoToDefaultPosition();

    //PAN FUNCTIONS
    void setPanPin(int pin);
    void setMaxMinPan(int maxPan, int minPan);
    void setPanDefaultAngle(int angle);
    void panServoPosition(int angle);
    void panServoToDefaultPosition();

private:

    Servo tiltServo;
    Servo panServo;
    void initialize();

    int tiltPin;
    int panPin;
    int maxTilt;
    int tiltDefault;
    int minTilt;
    int maxPan;
    int panDefault;
    int minPan;
};

#endif
