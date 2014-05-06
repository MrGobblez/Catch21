#include <HMsTimer2.h>
#include <StepperMod.h>


// Motor
int in1Pin = 8;
int in2Pin = 7;
int in3Pin = 6;
int in4Pin = 5;
int in5Pin = 10;
int in6Pin = 9;
StepperMod motor(200, in1Pin, in2Pin, in3Pin, in4Pin, in5Pin, in6Pin);

// Other
char charIn;
String stringIn;
String temp;
int rpm= 1;
int directionInt = 0;
int stepDelay = 0;
int pwm = 255;

void setup() {
  Serial.begin(9600);
  //Change pwm frequency to 31250hz by not using prescaler
  TCCR1B |= (1<<CS20);
  TCCR1B &= ~((1<<CS22) | (1<<CS21));
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
          
          //Set the pwm
          
          //50% duty
          if (rpm < 100)
            pwm = 128;
            
          //60% duty
          else if (rpm < 200)
            pwm = 153;
            
          //70% duty
          else if (rpm < 300)
            pwm = 179;
            
          //100% duty
          else*/
            pwm = 255;
          
          // Setup and start the timer might include a if clause and stop the timer if directionInt == 0
          HMsTimer2::stop();
          HMsTimer2::set(stepDelay, isr);
          HMsTimer2::start();
        }
      }
  
}

void isr() 
{
  if (directionInt != 0)
  {
    motor.setPwm(pwm);
    motor.step(directionInt);
  }
  
  else if (directionInt == 0)
  {
    motor.enablersOff();
  }
}
