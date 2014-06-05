#include "Process.h"

Process::Process()
{
}

void Process::processImage(cv::Mat img)
{
    //Clone the passed image, then convert it to HSV color space
    cv::Mat imgHSV = img.clone();
    cvtColor(img, imgHSV, CV_BGR2HSV);

    //Create another copy, fill it in white wherever the color is between the two cv::Scalar values in the HSV image and black in any other area.
    cv::Mat imgThresh = img;
    cv::inRange(imgHSV, cv::Scalar(8, 150, 20), cv::Scalar(20, 255, 250), imgThresh);

    //Erode the image two times
    erode(imgThresh, imgThresh, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);

    // Calculate the moments to estimate the position of the detected color.
    cv::Moments moment = moments(imgThresh);

    // The actual moment values
    double moment10 = moment.m10;
    double moment01 = moment.m01;
    double area = moment.m00;

    posX = 0;
    posY = 0;

    //Find the centroid of the color on each axis.
    posX = moment10/area;
    posY = moment01/area;

    //Send the positions for tracking, the processed image for debugging and set the object ready for more work.
    emit (posXposY(posX,posY));
    emit (processedImage(imgThresh));
    emit (readyForWork());
}
