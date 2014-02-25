#include "Motor_Driver.h"

Motor_Driver::Motor_Driver()
{
    initialize();
}


void Motor_Driver::movePlatform(int translation)
{
    // Sets speed of the motor
    speedControl(translation);

    if(translation > lowerThreshold && translation < upperThreshold)
    {
        digitalWrite(enablerTop, LOW);
        digitalWrite(enablerBottom, LOW);
        delay(10);  // Ask Øystein why. I don't think we need it
    }

    //Forward range: upper->512: enable motor, call forward function
    else if(translation >= upperThreshold)
    {
        digitalWrite(enablerTop, HIGH);
        digitalWrite(enablerBottom, HIGH);
        forward();
    }

    //Reverse range: -511->lower: enable motor, call reverse function
    else if(translation <= lowerThreshold)
    {
        digitalWrite(enablerTop, HIGH);
        digitalWrite(enablerBottom, HIGH);
        reverse();
    }
}

void Motor_Driver::setPins(byte positiveTop, byte negativeTop, byte positiveBottom, byte negativeBottom, byte enablerTop, byte enablerBottom)
{
    positiveTop = this->positiveTop;
    negativeTop = this->negativeTop;
    positiveBottom = this->positiveBottom;
    negativeBottom = this->negativeBottom;
    enablerTop = this->enablerTop;
    enablerBottom = this->enablerBottom;
}


void Motor_Driver::initialize()
{
    positiveTop = 9;    //1st pole of coil A
    negativeTop = 10;   //2nd(inversed) pole of coil A
    positiveBottom = 11;   //1st pole of coil B
    negativeBottom = 12;   //2nd(inversed) pole of coil B
    enablerTop = 6;     //Pin to provide 5V to bridge A logic circuit
    enablerBottom = 7;     //Pin to provide 5V to bridge B logic circuit
    pinMode(positiveTop,OUTPUT);
    pinMode(negativeTop,OUTPUT);
    pinMode(positiveBottom,OUTPUT);
    pinMode(negativeBottom,OUTPUT);
    pinMode(enablerTop, OUTPUT); //HIGH enable input to coil A through bridge A, LOW shuts bridge A off.
    pinMode(enablerBottom, OUTPUT); //HIGH enable input to coil B through bridge B, LOW shuts bridge B off.

    //Initial state of bridges - OFF:
    digitalWrite(enablerTop, LOW);
    digitalWrite(enablerBottom, LOW);
}


void Motor_Driver::forward()
{
    digitalWrite(positiveTop,HIGH);
    digitalWrite(negativeBottom,LOW);
    delay(delayTime);

    digitalWrite(positiveTop,LOW);
    digitalWrite(positiveBottom,HIGH);
    delay(delayTime);

    digitalWrite(negativeTop,HIGH);
    digitalWrite(positiveBottom,LOW);
    delay(delayTime);

    digitalWrite(negativeBottom,HIGH); // Change ?
    digitalWrite(negativeTop,LOW);  // Bytte plass?
    delay(delayTime);
}


void Motor_Driver::reverse()
{
    digitalWrite(negativeBottom,HIGH);
    digitalWrite(positiveTop,LOW);
    delay(delayTime);

    digitalWrite(negativeTop,HIGH);
    digitalWrite(negativeBottom,LOW);
    delay(delayTime);

    digitalWrite(positiveBottom,HIGH);
    digitalWrite(negativeTop,LOW);
    delay(delayTime);

    digitalWrite(positiveTop,HIGH);
    digitalWrite(positiveTop,LOW);
    delay(delayTime);
}


void Motor_Driver::speedControl(int translation)
{
    delayTime = map(abs(translation), 0, 512, 500,1);
}

