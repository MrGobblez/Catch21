#include "Color_Recognition.h"

//PUBLIC FUNCTIONS
Color_Recognition::Color_Recognition()
{
	initialize();
}

void Color_Recognition::runDetection()
{
	// Will hold a frame captured from the camera
        IplImage* frame = 0;
        frame = cvQueryFrame(capture);
	
	IplImage* imgScribble = NULL;
	// If this is the first frame, we need to initialize it
        if(imgScribble == NULL)
        {
           	imgScribble = cvCreateImage(cvGetSize(frame), 8, 3);
        }

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
        static int posX = 0;
        static int posY = 0;

        int lastX = posX;
        int lastY = posY;

        posX = moment10/area;
        posY = moment01/area;

 	// Print it out for debugging purposes
        printf("position (%d,%d)\n", posX, posY);

        // We want to draw a line only if its a valid position
       	if(lastX>0 && lastY>0 && posX>0 && posY>0)
       	{
       		// Draw a red line from the previous point to the current point
          	cvLine(imgScribble, cvPoint(posX, posY), cvPoint(lastX, lastY), cvScalar(0,0,255), 5);
       	}

	// Add the scribbling image and the frame...
       	cvAdd(frame, imgScribble, frame);
       	cvShowImage("thresh", imgThresh);
       	cvShowImage("video", frame);

	// Release the thresholded image+moments... we need no memory leaks.. please
        cvReleaseImage(&imgThresh);
	cvReleaseImage(&imgScribble);
        delete moments;
	delete imgScribble;
}

void Color_Recognition::stopDetection()
{
	// We're done using the camera. Other applications can now use it
    	cvReleaseCapture(&capture);
}

//PRIVATE FUNCTIONS
IplImage* Color_Recognition::getThresholdedImage(IplImage* img)
{	
   	// Convert the image into an HSV image
   	IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
   	cvCvtColor(img, imgHSV, CV_BGR2HSV);

   	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	cvInRangeS(imgHSV, cvScalar(10, 160, 40), cvScalar(15, 255, 120), imgThreshed);

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
}
