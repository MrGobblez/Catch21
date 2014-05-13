#include "Window_Handler.h"

Window_Handler::Window_Handler()
{
    cv::namedWindow("video");
    // cv::namedWindow("thresh");
    cv::resizeWindow("video", 640, 480);
}

void Window_Handler::drawImage(cv::Mat image)
{
    cv::imshow("video", image);
}

