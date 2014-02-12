#ifndef WRITE_TO_MEMORY_H
#define WRITE_TO_MEMORY_H
#include <opencv2/highgui/highgui.hpp>
#include <boost/thread.hpp>

class Write_To_Memory
{
public:




    void write(bool showCapturing)
    {
        continueRecording = true;
        cv::VideoCapture captureFromCam(0); //Captures the camera
        cv::VideoWriter outToFile; //Outputs
        cv::Mat inFrame;//Storing format

        captureFromCam >> inFrame;
        outToFile.open("test.avi", CV_FOURCC('D', 'I', 'V', 'X'), 30,inFrame.size(), true); //Opens/creates a file, video format, fps et.
        //!!!Issues: CV_FOURCC not working properly!!!

        if(showCapturing)
        {
            cv::namedWindow("Recording", CV_WINDOW_AUTOSIZE);
            cvMoveWindow("Recording", 0,0);
        }

        //Writing to file-storage of video to file
        while (continueRecording)
        {
            captureFromCam >> inFrame;
            outToFile.write(inFrame);

            if(showCapturing)
            {
                cv::imshow("Recording", inFrame);
            }//end if
        } // end while

        captureFromCam.release();
        cv::destroyWindow("Recording");
    } // end write

    void start() // show capture set to default true ---!!!!!
    {
        writeThread = boost::thread(&Write_To_Memory::write, this, true);
    } // end start thread function

    void join()
    {
       writeThread.join();
    } // end join

    void interrupt()
    {
         //captureFromCam.release();
         //cv::destroyWindow("Recording");
        writeThread.interrupt();
    } // end interrupt

    void setContinueRecording()
    {
        if(continueRecording)
        {
            continueRecording = false;
        }
        else
        {
            continueRecording=true;
        }

    } // end function

private:
    boost::thread writeThread;
    bool continueRecording;
}; // end class

#endif // WRITE_TO_MEMORY_VER2_H


