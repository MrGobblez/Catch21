#include "Motor_Driver.h"

Motor_Driver::Motor_Driver()
{
    initialize();
}


void Motor_Driver::movePlatform(int translation)
{
    // Sets speed of the motor
    speedControl(translation);
    Serial.print("translation: ");
    Serial.println(translation);

    if(translation > lowerThreshold && translation < upperThreshold)
    {
        Serial.println("Stille");
        digitalWrite(enablerTop, LOW);
        digitalWrite(enablerBottom, LOW);
    }

    //Forward range: upper->512: enable motor, call forward function
    else if(translation >= upperThreshold)
    {
        Serial.println("forward");
        digitalWrite(enablerTop, HIGH);
        digitalWrite(enablerBottom, HIGH);
        forward();
    }

    //Reverse range: -511->lower: enable motor, call reverse function
    else if(translation <= lowerThreshold)
    {
        Serial.println("reverse");
        digitalWrite(enablerTop, HIGH);
        digitalWrite(enablerBottom, HIGH);
        reverse();
    }
}

void Motor_Driver::setPins(byte positiveTop, byte negativeTop, byte positiveBottom, byte negativeBottom, byte enablerTop, byte enablerBottom)
{
    this->positiveTop = positiveTop;
    this->negativeTop = negativeTop;
    this->positiveBottom = positiveBottom;
    this->negativeBottom = negativeBottom;
    this->enablerTop = enablerTop;
    this->enablerBottom = enablerBottom;

    Serial.print("lowerThreshold: ");
    Serial.println(lowerThreshold);
    Serial.print("upperThreshold: ");
    Serial.println(upperThreshold);

}


void Motor_Driver::initialize()
{
    positiveTop = 6;    //1st pole of coil A
    negativeTop = 7;   //2nd(inversed) pole of coil A
    positiveBottom = 8;   //1st pole of coil B
    negativeBottom = 11;   //2nd(inversed) pole of coil B
    enablerTop = 12;     //Pin to provide 5V to bridge A logic circuit
    enablerBottom = 13;     //Pin to provide 5V to bridge B logic circuit
    pinMode(positiveTop,OUTPUT);
    pinMode(negativeTop,OUTPUT);
    pinMode(positiveBottom,OUTPUT);
    pinMode(negativeBottom,OUTPUT);
    pinMode(enablerTop, OUTPUT); //HIGH enable input to coil A through bridge A, LOW shuts bridge A off.
    pinMode(enablerBottom, OUTPUT); //HIGH enable input to coil B through bridge B, LOW shuts bridge B off.

    //Initial state of bridges - OFF:
    digitalWrite(enablerTop, LOW);
    digitalWrite(enablerBottom, LOW);

    // setting Threshold
    upperThreshold = 32;
    lowerThreshold = (-32);
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

    digitalWrite(negativeTop,LOW);
    digitalWrite(negativeBottom,HIGH);
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
    digitalWrite(positiveBottom,LOW);
    delay(delayTime);
}


void Motor_Driver::speedControl(int translation)
{
    delayTime = map(abs(translation), 0, 512, 500,1);
}

