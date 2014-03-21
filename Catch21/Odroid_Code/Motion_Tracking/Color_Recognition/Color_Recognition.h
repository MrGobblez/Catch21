#ifndef COLOR_RECOGNITION_H
#define COLOR_RECOGNITION_H

#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"

class Color_Recognition
{
	public:
	Color_Recognition();
	int getUserDirection();
	int getUserSpeed();
	void stopDetection();

	private:
	//FUNCTIONS
	void runDetection();
	IplImage* getThresholdedImage(IplImage* img);
	void initialize();

	//VARIABLES
	CvCapture* capture;
	int posX;
	int posY;
	int lastX;
	int lastY;
	int direction;
	int speed;
};

#endif
