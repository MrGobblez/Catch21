#include "Read_From_Memory_Ver2.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

Read_From_Memory_Ver2::Read_From_Memory_Ver2()
{

}

Read_From_Memory_Ver2::~Read_From_Memory_Ver2()
{

}

//!!! C code "work in progress" !!!

void Read_From_Memory_Ver2::read(bool speed)
{
    cvNamedWindow("Replay", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Replay",0,0);
    int milliSecondsPerFrame;

    CvCapture* capture = cvCreateFileCapture("test.avi");

    if(!speed)
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
        //std::cout << "Inside loop\n";
        if (!frame) break;

        cvShowImage("Replay", frame);

        char c = cvWaitKey(milliSecondsPerFrame);
        if (c == 27) break;
    }

    cvReleaseCapture(&capture);
    cvDestroyWindow("Replay");

}
