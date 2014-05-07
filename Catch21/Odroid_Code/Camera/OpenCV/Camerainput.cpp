#include "Camerainput.h"

CameraInput::CameraInput()
{
    // Initialize capturing live feed from the camera
    cap.open(0);

    // Check if the capture was opened
    if(!cap.isOpened())
    {
        qDebug() << "Capture could not be opened Succesfully";
        return;
    }
    qDebug() << "Capure =" << QThread::currentThreadId();
}

void CameraInput::captureImage()
{
    cap >> frame;
    //qDebug() << "capture" << QThread::currentThreadId();
    emit capturedImage(&frame);
}
