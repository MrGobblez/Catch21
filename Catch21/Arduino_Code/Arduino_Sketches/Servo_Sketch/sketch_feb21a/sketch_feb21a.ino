#include <Servo.h> 

//Create servo objects:
Servo panservo;  // create servo object to control a servo 
Servo tiltservo;
int panAngle;
int tiltAngle;

void setup() 
{ 
  Serial.begin(9600);
  panservo.attach(11); // assign the pan servo object to pin 11
  tiltservo.attach(5); // assign the tilt servo object to pin 5
  panAngle = 0;
  tiltAngle = 0;
}

void loop() 
{
  panAngle = analogRead(A0);
  panAngle = map(panAngle, 0, 1023, 50, 142);
  panservo.write(panAngle);
  tiltAngle = analogRead(A1);
  tiltAngle = map(tiltAngle, 0, 1023, 70, 120);
  tiltservo.write(tiltAngle);
    
  delay(15);                           // waits for the servo to get there 
} 


/*Tilt:
  midt: 95
  opp: 120
  ned: 70
*/

/*Pan:
  midt: 96
  venstre: 50
  høyre: 142
*/
