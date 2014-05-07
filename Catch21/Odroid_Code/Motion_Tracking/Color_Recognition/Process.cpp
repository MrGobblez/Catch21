#include "Process.h"

Process::Process()
{
}

void Process::processImage(cv::Mat img)
{
    cv::Mat imgHSV = img.clone();
    cvtColor(img, imgHSV, CV_BGR2HSV);

    cv::Mat imgThresh = img;
    cv::inRange(imgHSV, cv::Scalar(1, 130, 30), cv::Scalar(15, 255, 250), imgThresh);
    erode(imgThresh, imgThresh, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);

    // Calculate the moments to estimate the position of the object
    cv::Moments moment = moments(imgThresh);

    // The actual moment values
    double moment10 = moment.m10;
    double moment01 = moment.m01;
    double area = moment.m00;

    posX = 0;
    posY = 0;

    posX = moment10/area;
    posY = moment01/area;

    qDebug() << "Done tampering with picture. Emitting...";

    emit (posXposY(posX,posY));
    emit (processedImage(imgThresh));
    emit (readyForWork());
}
