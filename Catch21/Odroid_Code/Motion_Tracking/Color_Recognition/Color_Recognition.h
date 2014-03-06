#ifndef COLOR_RECOGNITION_H
#define COLOR_RECOGNITION_H

#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"

class Color_Recognition
{
	public:
	Color_Recognition();
	void runDetection();
	void stopDetection();

	private:
	//FUNCTIONS
	IplImage* getThresholdedImage(IplImage* img);
	void initialize();

	//VARIABLES
	CvCapture* capture;
};

#endif
