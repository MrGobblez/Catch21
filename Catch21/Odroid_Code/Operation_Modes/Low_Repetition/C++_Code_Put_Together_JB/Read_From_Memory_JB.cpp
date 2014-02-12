#include "Read_From_Memory_JB.h"
#include <boost/thread.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

Read_From_Memory_JB::Read_From_Memory_JB()
{
}

void Read_From_Memory_JB::startReadThreadJB(bool speed)
{
    readingThread = boost::thread(&Read_From_Memory_JB::readFromMemoryJB,this,speed);
}

void Read_From_Memory_JB::joinReadThreadJB()
{
    readingThread.join();
}

void Read_From_Memory_JB::readFromMemoryJB(bool speed)
{
    cvNamedWindow("Replay", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Replay", 0,0);
    int milliSecondsPerFrame;

    CvCapture* capture = cvCreateFileCapture("testJB.avi");

    if (!speed)
    {
        milliSecondsPerFrame = 67;
    }

    else
    {
        milliSecondsPerFrame = 33;
    }

    IplImage* frame = NULL;

    while(1)
    {
        frame = cvQueryFrame(capture);

        if (!frame) break;

        cvShowImage("Replay",frame);

        char c = cvWaitKey(milliSecondsPerFrame);
        if(c == 27) break;
    }

    cvReleaseCapture(&capture);
    cvDestroyWindow("Replay");
}
