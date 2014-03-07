#include "Color_Recognition.h"

int main()
{
	Color_Recognition test;
	int c;
	while(true)
	{
		test.runDetection();

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
