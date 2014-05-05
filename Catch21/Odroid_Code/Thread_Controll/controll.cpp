#include "controll.h"

controll::controll()
{
    cvNamedWindow("video");
    cvNamedWindow("thresh");
    cvResizeWindow("video", 800, 600);
    processReady = false;
}

void controll::inputImage(IplImage *imgIn)
{
    cvShowImage("video", imgIn);
    if (processReady)
    {
        processReady = false;
        emit image(imgIn);
    }
    emit requestImage();

}

void controll::processedImage(IplImage *imgIn)
{
    cvShowImage("thresh", imgIn);
    cvReleaseImage(&imgIn);
}

void controll::processerReady()
{
    processReady = true;
    qDebug() << "processer Ready" << QThread::currentThreadId();
}
