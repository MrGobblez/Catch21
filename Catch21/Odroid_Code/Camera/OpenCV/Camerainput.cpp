#include "Camerainput.h"

CameraInput::CameraInput()
{
    // Initialize capturing live feed from the camera
    capture = cvCaptureFromCAM(0);
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 800 );

    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 600 );

     // Couldn't get a device? Throw an error and quit
     if(!capture)
     {
         printf("Could not initialize capturing...\n");
     }
     qDebug() << "Capure =" << capture << QThread::currentThreadId();
}

void CameraInput::captureImage()
{
    frame = cvQueryFrame(capture);
    qDebug() << "capture" << QThread::currentThreadId();
    emit capturedImage(frame);
}
