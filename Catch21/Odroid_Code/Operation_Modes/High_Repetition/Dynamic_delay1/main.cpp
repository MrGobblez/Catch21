#include "opencv2/highgui/highgui.hpp"
#include <iostream>


int main()
{
    cv::VideoCapture cap(0); // open the video camera no. 0
    cv::Vector <cv::Mat> imgBuf (600); // create buffer to hold images
    int imgStoreIndex=0; // variable to keep track of in what place images are stored
    int imgDisplayIndex=0; // variable to keep track of what image place is displayed

    cv::namedWindow("Buffer",CV_WINDOW_AUTOSIZE); //create a window
    bool showd = false; // keeps track of if to show images from buffer or not

    while (1)
    {
        cv::Mat frame; // frame to hold an image frame
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


        if (cv::waitKey(1) == 27) //wait for 'esc' key press.
        {
           std::cout << "esc key is pressed by user" << std::endl;
           break;
        }
        if(cv::waitKey(1) == 119) // arrow up
        {
            std::cout << "Increase delay" << std::endl;

            int distance = imgStoreIndex-imgDisplayIndex; // measure distance in buffer

            if( abs(distance) > 10 ) // as long as stored is 10 frames separated from display
            {
                if( imgDisplayIndex-10 >= 0) // if increasing delay by 10 does not give a neg
                {
                    imgDisplayIndex = imgDisplayIndex - 10;
                }
                else // if increasing delay gives a negative int, withdraw from buffer maxindex
                {
                    imgDisplayIndex = imgDisplayIndex - 10;
                    imgDisplayIndex = std::abs(imgDisplayIndex);
                    imgDisplayIndex = 599 - imgDisplayIndex;
                }
             } // end outer if

        }
        if(cv::waitKey(1) == 115) // arrow down
        {
            std::cout << "Decrease delay" << std::endl;

            int distance = imgStoreIndex-imgDisplayIndex; // measure distance in buffer

            if( abs(distance) > 10 ) // as long as stored is 10 frames separated from display
            {
                if ( (imgDisplayIndex += 10)  <  600)
                {
                    imgDisplayIndex = imgDisplayIndex + 10;
                }
                else
                {
                    imgDisplayIndex += 10;
                    imgDisplayIndex = imgDisplayIndex - 599;
                }
             } // end outer i
        }


     } //end while

          return 0;

} // end main
