#ifndef MODE_H
#define MODE_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <boost/thread.hpp>
#include <Write_To_Memory.h>
#include <Read_From_Memory.h>

class Mode
{
public:
    Write_To_Memory modeWrite;
    Read_From_Memory modeRead;

    void menu() // function takes care of control input
    {
        // set variables
        first = true;
        speed = true;
        window = true;
        record = true;

        while(true)
        {
            this->menuWindow();
            decision = (char) cv::waitKey(0);


            switch(decision)
            {
            case 'q': // exit program
                return;
                break;
            case 's': // toggle normal/slow motion
                break;
            case ' ': // toggles record/replay
                if( record == true)
                {
                    startWriteToFile(); //all recording prep and actions
                } // end if recording
                else
                {
                    startReadFromFile(); //all reading prep and actions
                } // end else reading
                break;
            default: // default
                std::cout << "Press key: space, s, w, or q!" << std::endl;
                break;
            } // end switch
        } // end while
    } // end function menu

    void menuWindow() // creates window that holds the start menu
    {
        cv::Mat image;
        image = cv::imread("./catch21.jpg", CV_LOAD_IMAGE_COLOR ); // read jpg fil
        cv::namedWindow("Key Controls", cv::WINDOW_AUTOSIZE); // window to hold img
        cv::moveWindow("Key Controls",0,0);
        // cv::imshow("Key Controls", image); // show image


    } // end function menuWindow

    void setSpeed() // toggles normal/slow motion playback
    {
            if(speed == true)
            {
                speed=false;
            }
            else
            {
                speed = true;
            }

    } // end function setSpeed

    void startWriteToFile()
    {
        if(!first)
        {
            modeRead.setContinueReplay();
        }
        else
        {
            first=false;
        }
        record = false; // next time space is pressed you replay
        modeWrite.start(); // start thread that writes to memory


    } // end startWriteToFile

    void stopWriteToFile()
    {
        modeWrite.interrupt();

    } // end stopWriteToFile

    void startReadFromFile() // deals with all replay issues
    {
        record = true; // toggle record/replay value
        modeWrite.setContinueRecording();
        modeRead.start();

    } // end startReadFromFile

    void stopReadFromFile()
    {
        modeRead.interrupt();
    } // end stopReadFromFile

private:
    bool window;
    bool speed;
    bool record;
    bool first;
    char decision;
}; // end class Low_Repetition

#endif // MODE_H
