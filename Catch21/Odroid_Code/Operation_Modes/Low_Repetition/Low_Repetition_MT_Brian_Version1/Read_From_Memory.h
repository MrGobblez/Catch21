#ifndef READ_FROM_MEMORY_H
#define READ_FROM_MEMORY_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

class Read_From_Memory
{
public:
    void read(bool speed) // reads from file
    {
        cv::namedWindow("Replay",CV_WINDOW_AUTOSIZE);
        cv::moveWindow("Replay",0,0);
        int milliSecondsPerFrame;
        continueReplay = true;

        CvCapture* capture = cvCreateFileCapture("test.avi");
        // Videocapture cap("test.avi");

        if(!speed)
        {
            milliSecondsPerFrame = 67;
        } // end if
        else
        {
            milliSecondsPerFrame = 33;
        } // end else

        IplImage* frame = NULL;

        while(continueReplay)
        {
            frame = cvQueryFrame(capture);
            if(!frame)
                  break;

            cvShowImage("Replay", frame );
            char c = cv::waitKey(milliSecondsPerFrame);
            if(c == 27)
                break;
        } // end while

        cvReleaseCapture(&capture);
        cvDestroyWindow("Replay");
    } // end read function

    void start()
    {
        readThread = boost::thread(&Read_From_Memory::read,this, false);
    } // end start

    void join()
    {
        readThread.join();
    } // end function join

    void interrupt()
    {
        readThread.interrupt();
    } // end function interrupt

    void setContinueReplay()
    {
        if(continueReplay)
        {
            continueReplay=false;
        }
        else
        {
            continueReplay=true;
        }

    } // end setContinueReplay

private:
    boost::thread readThread;
    bool continueReplay; // variable that lets you stop replay
};  // end class Read_From_Memory

#endif // READ_FROM_MEMORY_H
