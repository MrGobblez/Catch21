#include "Controll.h"

Controll::Controll()
{
    cv::namedWindow("video");
    cv::namedWindow("thresh");
    cv::resizeWindow("video", 640, 480);
    processReady = false;
    counterOrg = 0;
    counterProcessed = 0;
    // start the clock
    time(&start);
}

void Controll::inputImage(cv::Mat imgIn)
{
    cv::imshow("video", imgIn);
    if (processReady) 
    {
        processReady = false;
        emit image(imgIn);
    }

    emit requestImage();

    // see how much time has elapsed
    time(&end);

    // calculate current FPS
    ++counterOrg;
    sec = difftime (end, start);

    fpsOrg = counterOrg / sec;

    // will print out Inf until sec is greater than 0
    printf("FPS Org stream = %.2f\n", fpsOrg);

}

void Controll::processedImage(cv::Mat imgIn)
{
    qDebug() << "About to show thresh image...";
    cv::imshow("thresh", imgIn);
    // see how much time has elapsed
    time(&end);

    // calculate current FPS
    ++counterProcessed;
    sec = difftime (end, start);

    fpsProcessed = counterProcessed / sec;

    // will print out Inf until sec is greater than 0
    printf("FPS processed stream = %.2f\n", fpsProcessed);
}

void Controll::processerReady()
{
    processReady = true;
    //qDebug() << "processer Ready" << QThread::currentThreadId();
}
