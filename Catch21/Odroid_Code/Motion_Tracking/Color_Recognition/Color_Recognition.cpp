#include "Color_Recognition.h"

//PUBLIC FUNCTIONS
Color_Recognition::Color_Recognition()
{
	initialize();
}

int Color_Recognition::getUserDirection()
{
	runDetection();

	if(posX < 150)
	{
		this->direction = 1;
	}

	else if (posX > 490)
	{
		this->direction = -1;
	}

	else
	{
		this->direction = 0;
	} 

	return this->direction;
}

int Color_Recognition::getUserSpeed()
{
	//GOING LEFT OF PICTURE
	if(posX < 160 && posX > 140)
	{
		this->speed = 100;
	}

	else if (posX < 140 && posX > 120)
	{
		this->speed = 140;
	}

	else if (posX < 120 && posX > 80)
	{
		this->speed = 180;
	}

	else if (posX < 80 && posX > 40)
	{
		this->speed = 250;
	}

	else if (posX < 40)
	{
		this->speed = 300;
	}

	//GOING RIGHT OF PICTURE
	else if (posX > 480 && posX < 500)
	{
		this->speed = 0;
	}

	else if (posX > 500 && posX < 520)
	{
		this->speed = 140;
	}

	else if (posX > 520 && posX < 560)
	{
		this->speed = 180;
	}

	else if (posX > 560 && posX < 600)
	{
		this->speed = 250;
	}

	else if (posX > 600)
	{
		this->speed = 300;
	}

	//IN THE MIDDLE OF THE PICTURE
	else
	{
		this->speed = 0;
	}

	return this->speed;
}

void Color_Recognition::stopDetection()
{
	// We're done using the camera. Other applications can now use it
    	cvReleaseCapture(&capture);
}

void Color_Recognition::runDetection()
{
	// Will hold a frame captured from the camera
        IplImage* frame = 0;
        frame = cvQueryFrame(capture);

	// Holds the thresholded image (detected color = white, rest = black)
       	IplImage* imgThresh = getThresholdedImage(frame);

	// Calculate the moments to estimate the position of the ball
       	CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
       	cvMoments(imgThresh, moments, 1);
	
       	// The actual moment values
	double moment10 = cvGetSpatialMoment(moments, 1, 0);
   	double moment01 = cvGetSpatialMoment(moments, 0, 1);
  	double area = cvGetCentralMoment(moments, 0, 0);


	// Holding the last and current ball positions
        posX = 0;
        posY = 0;

        posX = moment10/area;
        posY = moment01/area;

 	// Print it out for debugging purposes
        // printf("position (%d,%d)\n", posX, posY);

       	cvShowImage("thresh", imgThresh);
       	cvShowImage("video", frame);

	// Release the thresholded image+moments... we need no memory leaks.. please
        cvReleaseImage(&imgThresh);
        delete moments;
}

//PRIVATE FUNCTIONS
IplImage* Color_Recognition::getThresholdedImage(IplImage* img)
{	
   	// Convert the image into an HSV image
   	IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
   	cvCvtColor(img, imgHSV, CV_BGR2HSV);

   	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	cvInRangeS(imgHSV, cvScalar(10, 130, 40), cvScalar(20, 230, 200), imgThreshed);

	cvReleaseImage(&imgHSV);
    	return imgThreshed;
}

void Color_Recognition::initialize()
{
	// Initialize capturing live feed from the camera
    	capture = cvCaptureFromCAM(0);

    	// Couldn't get a device? Throw an error and quit
    	if(!capture)
    	{
        	printf("Could not initialize capturing...\n");
    	}

	// One window for video, one window for debugging purposes. 
    	cvNamedWindow("video");
    	cvNamedWindow("thresh");
	cvResizeWindow("video", 640, 480);
}
