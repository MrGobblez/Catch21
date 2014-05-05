#include "process.h"

process::process()
{
}

void process::processImage(IplImage *img)
{
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);

    IplImage* imgThresh = cvCreateImage(cvGetSize(img), 8, 1);
    cvInRangeS(imgHSV, cvScalar(1, 130, 30), cvScalar(15, 255, 250), imgThresh);
    cvErode(imgThresh, imgThresh, 0, 2);

    cvReleaseImage(&imgHSV);

    // Calculate the moments to estimate the position of the object
    CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
    cvMoments(imgThresh, moments, 1);

    // The actual moment values
    double moment10 = cvGetSpatialMoment(moments, 1, 0);
    double moment01 = cvGetSpatialMoment(moments, 0, 1);
    double area = cvGetCentralMoment(moments, 0, 0);

    posX = 0;
    posY = 0;

    posX = moment10/area;
    posY = moment01/area;

    delete moments;
    //emit (posXposY(posX,posY));
    emit (readyForWork());
    emit (processedImage(imgThresh));
}
