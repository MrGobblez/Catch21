#include "Color_Recognition.h"
#include "../../Serial_Communication/Serial_Communication.h"
int main()
{
	Color_Recognition test;
	Serial_Communication serial("/dev/ttyUSB0");
	int c;
	int direction;
	int speed;

	while(true)
	{
		direction = test.getUserDirection();
		speed = test.getUserSpeed();

		if(direction == 1)
		{
			serial.sendData(direction, speed);
			printf("Move camera left with speed %d \n", speed);
		}

		else if(direction == -1)
		{
			serial.sendData(direction, speed);
			printf("Move camera right with speed %d \n", speed);
		}

		else
		{
			serial.sendData(direction, speed);
			printf("Stand still.");
		}
		// Wait for a keypress
        	c = cvWaitKey(10);
		if(c!=-1)
       		{
           	// If pressed, break out of the loop
           	break;
       		}
	}

	test.stopDetection();
}
