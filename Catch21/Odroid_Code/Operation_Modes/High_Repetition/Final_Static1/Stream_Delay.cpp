#include <opencv2/highgui/highgui.hpp>
#include "Stream_Delay.h"
#include <iostream>


void Stream_Delay::delay()
{

    cv::VideoCapture cap(0); // open the video camera no. 0
    cv::Vector <cv::Mat> imgBuf (600); // create buffer to hold images
    int imgStoreIndex=0; // variable to keep track of in what place images are stored
    int imgDisplayIndex=0; // variable to keep track of what image place is displayed

    cv::namedWindow("Buffer",CV_WINDOW_AUTOSIZE); //create a window
    bool showd = false; // keeps track of if to show images from buffer or not
    cv::Mat frame; // frame to hold an image frame

    while (1)
    {

        cap.read(frame); // read a new frame from video
        frame.copyTo(imgBuf[imgStoreIndex]); // store images from camera in buffer
        imgStoreIndex++; // change the spot of where to store the image next

        if(imgStoreIndex>=600) // resets the placements of stored images
            imgStoreIndex=0;

        if(imgDisplayIndex>=600) // resets the placements of reading images
            imgDisplayIndex=0;

        if(imgStoreIndex > 15) // decides delay time - i.e. when to start reading from buffer
        {
            showd = true;
        }

        if(showd) // show from buffer if boolean is true
        {
            cv::imshow("Buffer", imgBuf[imgDisplayIndex]);
            imgDisplayIndex++;
        }


        if (cv::waitKey(1) == 27) //wait for 'esc' key .
        {
           std::cout << "esc key is pressed" << std::endl;
           break;
        }
     } //end while
}
