#include "Window_Handler.h"

//Create windows for displaying video
Window_Handler::Window_Handler()
{
    cv::namedWindow("video");
    // cv::namedWindow("thresh");
    cv::resizeWindow("video", 640, 480);
}

//Paint a frame onto the window
void Window_Handler::drawImage(cv::Mat image)
{
    cv::imshow("video", image);
}

