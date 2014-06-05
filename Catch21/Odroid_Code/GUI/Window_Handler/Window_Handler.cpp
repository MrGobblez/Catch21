#include "Window_Handler.h"

//Create windows for displaying video
Window_Handler::Window_Handler()
{
    /*cv::namedWindow("Video"); // Old and works
    // cv::namedWindow("thresh");  // Debug for image processing
    cv::resizeWindow("Video", 640, 480); // Old and works
    cv::moveWindow("Video", 0, 0); //*/

    cv::namedWindow("Video", CV_WINDOW_FULLSCREEN);
    cv::setWindowProperty("Video", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    cv::setWindowProperty("Video", CV_WND_PROP_AUTOSIZE, 0 ); // All images will be stretched to fit the window. Discuss.
    //*/
}

//Paint a frame onto the window
void Window_Handler::drawImage(cv::Mat image)
{
//    qDebug() << "*";
    cv::imshow("Video", image);
}

