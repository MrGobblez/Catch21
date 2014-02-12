#include "Write_To_Memory_JB.h"
#include <boost/thread.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

Write_To_Memory_JB::Write_To_Memory_JB()
{
}

void Write_To_Memory_JB::startWritingThreadJB(bool window)
{
    writingThread = boost::thread(&Write_To_Memory_JB::writeToMemoryJB,this,window);
}

void Write_To_Memory_JB::joinWritingThreadJB()
{
    writingThread.join();
}

void Write_To_Memory_JB::writeToMemoryJB(bool showWind)
{
    cv::VideoCapture captureFromCam(0);
    cv::VideoWriter outToFile;
    cv::Mat inframe;

    captureFromCam >> inframe;
    outToFile.open("testJB.avi",CV_FOURCC('D','I','V','X'),30,inframe.size(),true);

    if(showWind)
    {
        cv::namedWindow("Recording",CV_WINDOW_AUTOSIZE);
        cv::moveWindow("Recording", 0,0);
    }

    while(1)
    {
        captureFromCam >> inframe;
        outToFile.write(inframe);

        if(showWind)
        {
            cv:imshow("Recording",inframe);
        }

        char c = (char) cv::waitKey(5);

        if(c == 32)
        {
            captureFromCam.release();
            cv::destroyWindow("Recording");
            break;
        }
    }


}
