#include "Controll.h"

Controll::Controll()
{
    cvNamedWindow("video");
    cvNamedWindow("thresh");
    cvResizeWindow("video", 800, 600);
    processReady = false;
    counterOrg = 0;
    counterProcessed = 0;
    // start the clock
    time(&start);
}

void Controll::inputImage(IplImage *imgIn)
{
    cvShowImage("video", imgIn);
    // see how much time has elapsed
    time(&end);

    // calculate current FPS
    ++counterOrg;
    sec = difftime (end, start);

    fpsOrg = counterOrg / sec;

    // will print out Inf until sec is greater than 0
    printf("FPS Org stream = %.2f\n", fpsOrg);

    if (processReady)
    {
        processReady = false;
        emit image(imgIn);
    }
    emit requestImage();

}

void Controll::processedImage(IplImage *imgIn)
{
    cvShowImage("thresh", imgIn);
    cvReleaseImage(&imgIn);
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
