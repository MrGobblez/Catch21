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
		serial.sendData(direction, speed);

		printf("%d\n", direction);
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
