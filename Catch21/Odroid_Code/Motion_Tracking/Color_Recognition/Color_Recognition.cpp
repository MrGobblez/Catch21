#include "Color_Recognition.h"

//PUBLIC FUNCTIONS
Color_Recognition::Color_Recognition()
{
	initialize();
}

int Color_Recognition::getUserPosition()
{
	int direction;
	runDetection();

	if(posX < 150)
	{
		direction = 1;
	}

	else if (posX > 490)
	{
		direction = -1;
	}

	else
	{
		direction = 0;
	} 

	return direction;
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
        printf("position (%d,%d)\n", posX, posY);

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
