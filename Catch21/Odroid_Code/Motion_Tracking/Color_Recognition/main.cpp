#include "Color_Recognition.h"

int main()
{
	Color_Recognition test;
	int c;
	int direction;

	while(true)
	{
		direction = test.getUserPosition();

		if(direction == 1)
		{
			printf("Move camera left!");
		}

		else if(direction == -1)
		{
			printf("Move camera right!");
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
