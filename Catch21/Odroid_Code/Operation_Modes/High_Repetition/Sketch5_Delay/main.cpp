#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0); // open the video camera no. 0
    Vector <Mat> imgBuf (100); // create buffer to hold images
    int imgStoreIndex=0; // variable to keep track of in what place images are stored
    int imgDisplayIndex=0; // variable to keep track of what image place is displayed

    namedWindow("Buffer",CV_WINDOW_AUTOSIZE); //create a window
    bool showd = false; // keeps track of if to show images from buffer or not

    while (1)
    {
        Mat frame; // frame to hold an image frame
        cap.read(frame); // read a new frame from video
        frame.copyTo(imgBuf[imgStoreIndex]); // store images from camera in buffer
        imgStoreIndex++; // change the spot of where to store the image next

        if(imgStoreIndex>=100) // resets the placements of stored images
            imgStoreIndex=0;

        if(imgDisplayIndex>=100) // resets the placements of reading images
            imgDisplayIndex=0;

        if(imgStoreIndex > 30) // decides delay time - i.e. when to start reading from buffer
        {
            showd = true;
        }

        if(showd) // show from buffer if boolean is true
        {
            imshow("Buffer", imgBuf[imgDisplayIndex]);
            imgDisplayIndex++;
        }


        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms.
        {
           cout << "esc key is pressed by user" << endl;
           break;
        }
     } //end while
          return 0;

} // end main
