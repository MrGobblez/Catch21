#include <Motor_Driver.h>
#include <Servo.h>

// Add servo files to Arduino library and include the header here.
#include <Rig_Servo.h>
#include <PS2X_lib.h>

PS2X ps2Controller;  // Playstation Controller class
Rig_Servo rigServo;  // Servo driver class name
Motor_Driver motorDriver;

// Servo variables
byte stickTiltValue = 128;
byte stickPanValue = 128;

// Playstation Controller variables
byte error = 0;      // For link status to Playstation Controller
byte type = 0;      // For checking Playstation Controller Type
byte XLS = 0;      // X-axis, Left stick
byte YLS = 0;     // Y-axis, Left stick
byte XRS = 0;    // X-axis, Right stick

void setup()
{
  // Setting up seial connection for debug purposes.
  Serial.begin(9600);

  Serial.println("starting setup");
  rigServo.setTiltPin(10);
  rigServo.setPanPin(9);
  
  // Setup motorDriver pins(posT,negT,posB,negB,enT,enB);
  motorDriver.setPins(6,7,8,11,12,13);
  
  // Playstation controller setup.
  error = ps2Controller.config_gamepad(2,4,3,5, true, true);   	//setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  
  if(error == 0){
     Serial.println("Found Controller, configured successful");
  }
   
  else if(error == 1)
     Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
     Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
     Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
  type = ps2Controller.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
   }
  // Playstation Controller setup completed.
   
}

void loop()
{
  if(error == 1) 
  { //skip loop if no controller found
    return;
  }
  
  else
  {
    // Read stick values
    ps2Controller.read_gamepad(false, 0);
    XLS = ps2Controller.Analog(PSS_LX);
    YLS = ps2Controller.Analog(PSS_LY);
    XRS = ps2Controller.Analog(PSS_RX);
    Serial.print("XLS: ");
    Serial.println(XLS);
    Serial.print("YLS");
    Serial.println(YLS);
    
    
    //Check for controller input to servo, if stick is in relaxed/middle position (+/- 5% to remove noise), run:
    if (XLS > 116 && XLS < 140)
    {
      rigServo.panServoToDefaultPosition();
    }
    
    //If the stick is not in relaxed/middle position, run:
    else
    {
      stickPanValue = map(XLS, 0, 255, 50, 142);
      rigServo.panServoPosition(stickPanValue);
    }
    
    //Check for controller input to servo, if stick is in relaxed/middle position (+/- 5% to remove noise), run:
    if (YLS > 116 && YLS < 140)
    {
      rigServo.tiltServoToDefaultPosition();
    }
    
    //If the stick is not in relaxed/middle position, run:
    else
    {
      stickTiltValue = map(YLS, 0, 255, 70, 120);
      rigServo.tiltServoPosition(stickTiltValue);
    }
  
    // Check for controller input to motor
    motorDriver.movePlatform(map(XRS, 0, 255, -512, 511));  
    delay(50);
  }
  
}
