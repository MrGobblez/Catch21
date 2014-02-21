// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 

//Create servo objects:
Servo panservo;  // create servo object to control a servo 
Servo tiltservo;
 
 // analog pins used to connect the potentiometers
int panPot = A0;  
int tiltPot = A1;
//variables to read the value from the analog pins
int panVal = 0;    
int tiltVal = 0;
 
void setup() 
{ 
  Serial.begin(9600);
  panservo.attach(9,500,2500);  // assign the pan servo object to pin 9, define upper and lower pulse width 
  tiltservo.attach(6,500,1000); // assign the tilt servo object to pin 6, define upper and lower pulse width 
}

void loop() 
{ 
  panVal = analogRead(panPot);            // reads the value of the potentiometer (value between 0 and 1023) 
  panVal = map(panVal, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  panservo.write(panVal);                  // sets the servo position according to the scaled value 
  tiltVal = analogRead(tiltPot);
  tiltVal = map(tiltVal, 0, 1023, 0, 179);
  /*if(tiltVal > 120)
  {
    tiltVal = 120;
  }
  */
  tiltservo.write(tiltVal);
  delay(15);                           // waits for the servo to get there 
} 
