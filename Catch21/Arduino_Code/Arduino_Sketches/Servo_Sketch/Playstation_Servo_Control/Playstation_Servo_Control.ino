// Add servo files to Arduino library and include the header here.

Rig_Servo rigServo; // Servo driver class name
// Add all other needed objects for the playstation controller

void setup()
{
  rigServo.setTiltPin(TILT SERVO PIN HERE);
  rigServo.setPanPin(PAN SERVO PIN HERE);
  //Do playstation controller setups.
}

void loop()
{
  //Check for controller input, if stick is in relaxed/middle position, run:
  rigServo.tiltServoToDefaultPosition();
  rigServo.panServoToDefaultPosition();
  
  //If the stick is not in relaxed/middle position, run:
  stickTiltValue = map(stickTiltValue, lowest input value, highest input value, 70, 120);
  stickPanValue = map(stickPanValue, lowest input value, highest input value, 50, 142);
  
  rigServo.tiltServoPosition(stickTiltValue);
  rigServo.panServoPosition(stickPanValue);
  
  delay(15);
  
}
