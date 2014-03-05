#include "Write_To_Memory_Ver2.h"
#include <opencv2/highgui/highgui.hpp>

Write_To_Memory_Ver2::Write_To_Memory_Ver2()
{

}

Write_To_Memory_Ver2::~Write_To_Memory_Ver2()
{

}

void Write_To_Memory_Ver2::write(bool showCapturing)
{
    cv::VideoCapture captureFromCam(0); //Captures the camera
    cv::VideoWriter outToFile; //Outputs
    cv::Mat inFrame;//Storing format

    captureFromCam >> inFrame;
    outToFile.open("test.avi", CV_FOURCC('D', 'I', 'V', 'X'), 30,inFrame.size(), true); //Opens/creates a file, video format, fps et.
    //!!!Issues: CV_FOURCC not working properly!!!

    if(showCapturing)
    {
	cv::namedWindow("Recording", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Recording", 0,0);
    } 
    //Writing to file
    while (1)
    {
        captureFromCam >> inFrame;
        outToFile.write(inFrame);

        if(showCapturing)
        {
            cv::imshow("Recording", inFrame);
        }//end if

        char c = (char) cv::waitKey(5);                    //Spacebar will end capturing

        if (c == 32)
        {
            captureFromCam.release();
            cv::destroyWindow("Recording");
            break;
        }//end if

    } // end storage of video to file

}
