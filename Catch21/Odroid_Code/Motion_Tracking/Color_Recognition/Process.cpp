#include "process.h"

process::process()
{
}

void process::processImage(Mat img)
{
    Mat imgHSV = img;
    cvtColor(img, imgHSV, CV_BGR2HSV);

    Mat imgThresh = img;
    inRange(imgHSV, CvScalar(1, 130, 30), CvScalar(15, 255, 250), imgThresh);
    erode(imgThresh, imgThresh, 0, 2);

    // Calculate the moments to estimate the position of the object
    moments *moment = (CvMoments*)malloc(sizeof(CvMoments));
    moments(imgThresh, moment, 1);

    // The actual moment values
    double moment10 = cvGetSpatialMoment(moment, 1, 0);
    double moment01 = cvGetSpatialMoment(moment, 0, 1);
    double area = cvGetCentralMoment(moment, 0, 0);

    posX = 0;
    posY = 0;

    posX = moment10/area;
    posY = moment01/area;

    delete moments;
    //emit (posXposY(posX,posY));
    emit (readyForWork());
    emit (processedImage(imgThresh));
}

void process::processedImage(Mat img)
{
}
