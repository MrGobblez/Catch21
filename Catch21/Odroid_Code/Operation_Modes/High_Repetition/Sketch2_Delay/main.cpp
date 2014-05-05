#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0); // open the video camera no. 0
    Vector <Mat> imgBuf (100);
    int i=0;
    int j=0;

    namedWindow("Buffer",CV_WINDOW_AUTOSIZE); //create a window
    bool showd = false;
    while (1)
    {

        Mat frame;
        cap.read(frame); // read a new frame from video
        frame.copyTo(imgBuf[i]); // store images from camera in buffer
        i++;

        if(i>=100)
            i=0;

        if(j>=100)
            j=0;

        if(i > 30)
        {
            showd = true;
        }
        if(showd)
        {
            imshow("Buffer", imgBuf[j]);
            j++;
        }

       // imshow("Buffer", frame); //show the frame in "Buffer" window


          if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
          {
             cout << "esc key is pressed by user" << endl;
             break;
          }
     } //end while
          return 0;

} // end main
