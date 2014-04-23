#include <HMsTimer2.h>
#include <StepperMod.h>


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
          
          //Do not divide by zero!
          if (rpm <= 0)
          {
            rpm=1;
          }
          
          //Set the delay
          stepDelay = 6000 / rpm;
          stringIn = "";
          
          // Setup and start the timer might include a if clause and stop the timer if directionInt == 0
          HMsTimer2::stop();
          HMsTimer2::set(stepDelay, isr);
          HMsTimer2::start();
        }
      }
      rpm=50;
      directionInt = -1;
  while(3000 > millis())
  {
    if (rpm <600)
      rpm +=25;
    stepDelay = 6000 / rpm;
    HMsTimer2::stop();
    HMsTimer2::set(stepDelay, isr);
    HMsTimer2::start();
    delay(50);
  }
  delay(50);
  HMsTimer2::stop();
  Serial.println(rpm);
  delay(100);
  rpm=50;
      directionInt = 1;
  while(6150 > millis())
  {
    if (rpm <600)
      rpm +=25;
    stepDelay = 6000 / rpm;
    HMsTimer2::stop();
    HMsTimer2::set(stepDelay, isr);
    HMsTimer2::start();
    delay(50);
  }
  delay(50);
  HMsTimer2::stop();
  motor.enablersOff();
}

void isr() 
{
  if (directionInt != 0)
  {
    motor.step(directionInt);
  }
  
  else if (directionInt == 0)
  {
    motor.enablersOff();
  }
}
