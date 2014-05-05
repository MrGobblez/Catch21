#include <StepperMod.h>
#include <MsTimer2.h>

// Motor
int in1Pin = 11;
int in2Pin = 10;
int in3Pin = 9;
int in4Pin = 8;
int in5Pin = 5;
int in6Pin = 6;
StepperMod motor(200, in1Pin, in2Pin, in3Pin, in4Pin, in5Pin, in6Pin);

// Other
char charIn;
String stringIn;
String temp;
int rpm= 1;
int directionInt = 0;
int stepDelay = 0;
long nextStep = 0;

void setup() {
  Serial.begin(9600);
  MsTimer2::set(1, isr); // 500ms period
  MsTimer2::start();
}

void loop() {
    if (Serial.available() > 0)
  
      {
        charIn = Serial.read();
        stringIn += charIn;
        if (charIn == '.')
        {
          temp = stringIn.substring(0, 2);
          directionInt = temp.toInt();
          temp = stringIn.substring(2, 5);
          rpm = temp.toInt();
          stepDelay = 300 / rpm;
          stringIn = "";
          nextStep = millis() + stepDelay;
        }
      }
  
}

void isr() 
{
  if (directionInt != 0 && millis() > nextStep)
  {
    nextStep = millis() + stepDelay;
    motor.step(directionInt);
  }
  
  else if (directionInt == 0)
  {
    motor.enablersOff();
  }
}
