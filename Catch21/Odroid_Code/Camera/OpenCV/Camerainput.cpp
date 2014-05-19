#include "Camerainput.h"

CameraInput::CameraInput()
{
    // Initialize capturing live feed from the camera
    capture.open(0);
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

     // Couldn't get a device? Throw an error and quit
    if(!capture.isOpened())
     {
        qDebug() << "Capture could not be opened successfully.";
     }
     qDebug() << "Capure =" << QThread::currentThreadId();
}

void CameraInput::captureImage()
{
    //Extract frame from video stream and save it to frame.
    capture >> frame;

    if(!frame.empty())
    {
        emit capturedImage(frame);
    }
    //qDebug() << "capture" << QThread::currentThreadId();
}
