#include "opencv2/highgui/highgui.hpp"
#include <iostream>

//!! Based on the code example from http://opencv-srf.blogspot.no/2011/09/capturing-images-videos.html !!


int main()
{
    cv::VideoCapture cap(0); // open the video camera no. 0
    std::Vector <Mat> imgBuf (900);
    int i=0;
    int j=0;

    cv::namedWindow("Buffer",CV_WINDOW_AUTOSIZE); // create a window
    cv::Mat frame;
    while (1)
    {

        // read a new frame from video
        cap >> frame;
        frame.copyTo(imgBuf[i]); // store images from camera in buffer
        i++;

        if(i > 60)
        {
            cv::imshow("Buffer", imgBuf[j]); // show the frame in "Buffer" window
            j++;
        }




          if (cv::waitKey(30) == 27) // wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
          {
             std::cout << "esc key is pressed by user" << std::endl;
             break;
          }
     } //end while
          return 0;

} // end main
