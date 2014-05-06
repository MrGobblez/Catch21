//#include <QtCore/QCoreApplication>
#include <opencv2/highgui/highgui.hpp>  //Gives acces to opencv libraries
#include <iostream>
#include <stdio.h>


using namespace cv;
using namespace std;


int main()
{
    
    
    bool run = true;  //Variable controls running of the code
    
    //Pauses program until a buttton is pressed
    system("stty cbreak -echo");
    getchar();
    system("stty cooked echo");
    
    
    while(run)
    {
        char decision = waitKey(0); //Waits forever for a key pressed
        if (decision == 32) // Waits for spacebar to be pressed, to start the code
        {
            run = true;
        }
        else if( decision == 'q') // Waits for q to be pressed, to exit the code
        {
            return 0;
        }
        
        //Program starts, waits for spacebar to start recording
        //set spacebar to false
        
        //Takes care of storing video to file, using opencv library classes
        
        VideoCapture captureFromCam(0); //Captures the camera
        VideoWriter outToFile; //Outputs
        Mat inFrame;//Storing format
        
        captureFromCam >> inFrame;
        outToFile.open("test.avi", CV_FOURCC('D', 'I', 'V', 'X'), 12,inFrame.size(), true); //Opens/creates a file, video format, fps et.
        //Issues: CV_FOURCC not working properly...
        
        //Writing to file
        while (1)
        {
            captureFromCam >> inFrame;
            outToFile.write(inFrame);
            namedWindow("Recording", WINDOW_AUTOSIZE);
            cvMoveWindow("Recording",0,0);
            imshow("Recording", inFrame);
            char c = (char) waitKey(50); //Spacebar will end capturing
            if (c == 32)
            {
                captureFromCam.release();
                break;
            }
        } // end storage of video to file
        
        
        //Code for displaying video
        cvNamedWindow("Example3", CV_WINDOW_AUTOSIZE);
        cvMoveWindow("Example3",0,0);
        
        CvCapture* capture = cvCreateFileCapture("test.avi"); //Captures the file
        IplImage* frame = NULL;
        
        //Displays captured video
        while(1)
        {
            frame = cvQueryFrame(capture);
            
            if (!frame)
                break;
            cvShowImage("Example3", frame);
            char e = cvWaitKey(33);
            if (e == 32) break;
        }
        
        cvReleaseCapture(&capture); //Release file
        cvDestroyWindow("Example3");
        
    } // end while loop and quit program
    
    return 0;
    
    // QCoreApplication a(argc, argv);
    // return a.exec();
}