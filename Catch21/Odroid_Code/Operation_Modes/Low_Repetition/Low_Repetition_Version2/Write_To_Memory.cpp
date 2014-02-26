#include "Write_To_Memory.h"
#include <opencv2/highgui/highgui.hpp>

Write_To_Memory::Write_To_Memory()
{

}

Write_To_Memory::~Write_To_Memory()
{

}

void Write_To_Memory::write(bool show)
{
    bool showCapturing = show;

    cv::VideoCapture captureFromCam(0); //Captures the camera
    cv::VideoWriter outToFile; //Outputs
    cv::Mat inFrame;//Storing format

    captureFromCam >> inFrame;
    outToFile.open("test.avi", CV_FOURCC('D', 'I', 'V', 'X'), 30,inFrame.size(), true); //Opens/creates a file, video format, fps et.
    //!!!Issues: CV_FOURCC not working properly!!!

    //Writing to file
    while (1)
    {
        captureFromCam >> inFrame;
        outToFile.write(inFrame);

        if(showCapturing)
        {
            cv::namedWindow("Recording", CV_WINDOW_AUTOSIZE);
            //cv::moveWindow("Recording",0,0);              //!!!USING C AT THE MOMENT!!!
            cv::imshow("Recording", inFrame);
        }//end if

        char c = (char) cv::waitKey(50);                    //Spacebar will end capturing

        if (c == 32)
        {
            captureFromCam.release();
            break;
        }//end if

    } // end storage of video to file

}
