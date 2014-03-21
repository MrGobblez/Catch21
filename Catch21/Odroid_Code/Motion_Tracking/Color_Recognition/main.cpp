#include "Color_Recognition.h"

int main()
{
	Color_Recognition test;
	int c;
	int direction;
	int speed;

	while(true)
	{
		direction = test.getUserDirection();
		speed = test.getUserSpeed();

		if(direction == 1)
		{
			printf("Move camera left with speed %d \n", speed);
		}

		else if(direction == -1)
		{
			printf("Move camera right with speed %d \n", speed);
		}

		else
		{
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
