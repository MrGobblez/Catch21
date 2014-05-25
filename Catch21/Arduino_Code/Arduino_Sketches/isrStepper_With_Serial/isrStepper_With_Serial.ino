#include <HMsTimer2.h>
#include <StepperMod.h>


// Motor pins
int in1Pin = 8;
int in2Pin = 7;
int in3Pin = 6;
int in4Pin = 5;
int enablerA = 10;
int enablerB = 9;


// Motor control
int rpm= 1;
int directionInt = 0;
int stepDelay = 0;
int pwm = 255;

StepperMod motor(200, in1Pin, in2Pin, in3Pin, in4Pin, enablerA, enablerB);

// For communication
char charIn;
String stringIn;
String temp;


// Led debug
int ledPos = 3;
int ledNeg = 4;

void setup() {
  Serial.begin(9600);
  //Change pwm frequency to 31250hz by not using prescaler
  TCCR1B |= (1<<CS20);
  TCCR1B &= ~((1<<CS22) | (1<<CS21));
  
  // Debug leds
  pinMode(ledPos, OUTPUT);
  pinMode(ledNeg, OUTPUT);
}

void loop() {
    if (Serial.available() > 0)
  
      {
        charIn = Serial.read();
        stringIn += charIn;
        if (charIn == '.')
        {
          // Disables interrupts for this section
          noInterrupts();
          
          // Checks for ID request
          if (stringIn == "12345.")
          {
            Serial.println("C");
            stringIn = "";
          }
          else
          {
            // Decodes recived info
            temp = stringIn.substring(0, 2);
            directionInt = temp.toInt();
            temp = stringIn.substring(2, 5);
            rpm = temp.toInt();
          
            //Do not divide by zero!
            if (rpm <= 0)
            {
              rpm=1;
              if(directionInt == 0)
              {
                rpm = 600;
              }
            }
            
            //Set the delay
            stepDelay = 6000 / rpm; // change 6000 to constant
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
            else
              pwm = 255;
            
            // Setup and start the timer might include a if clause and stop the timer if directionInt == 0
            HMsTimer2::stop();
            HMsTimer2::set(stepDelay, isr);
            HMsTimer2::start();
            
            // Led debug
            if (directionInt > 0)
            {
              digitalWrite(ledPos, HIGH);
              digitalWrite(ledNeg, LOW);
            }
            
            else if (directionInt <= -1)
            {
              digitalWrite(ledPos, LOW);            
              digitalWrite(ledNeg, HIGH);
            }
             
            else if (directionInt == 0)
            {
              digitalWrite(ledPos, HIGH);            
              digitalWrite(ledNeg, HIGH);
            }
            else
            {
              digitalWrite(ledPos, LOW);            
              digitalWrite(ledNeg, LOW);
            }
          }
        // enables interrupts
          interrupts();        
        }
      }
  
}

void isr() 
{
  noInterrupts();
  if (directionInt != 0)
  {
    motor.setPwm(pwm);
    motor.step(directionInt);
  }
  
  else if (directionInt == 0)
  {
    motor.enablersOff();
  }
  interrupts(); 
}
