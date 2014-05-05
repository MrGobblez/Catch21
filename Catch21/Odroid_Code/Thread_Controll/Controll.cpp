#include "Controll.h"

Controll::Controll()
{
    cvNamedWindow("video");
    cvNamedWindow("thresh");
    cvResizeWindow("video", 800, 600);
    processReady = false;
}

void Controll::inputImage(IplImage *imgIn)
{
    cvShowImage("video", imgIn);
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
}

void Controll::processerReady()
{
    processReady = true;
    //qDebug() << "processer Ready" << QThread::currentThreadId();
}
