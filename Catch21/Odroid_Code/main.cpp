#include <QtCore>
#include <QCoreApplication>
#include <QMetaType>
#include "Camera/OpenCV/Camerainput.h"
#include "Thread_Controll/Controll.h"
#include "Motion_Tracking/Color_Recognition/Process.h"
#include "Motion_Tracking/Color_Recognition/Tracking.h"
#include "Serial_Communication/Serial_Communication.h"


Q_DECLARE_METATYPE(cv::Mat)
int main()
{
    int c;

    // Objects
    CameraInput *camera = new CameraInput();
    Controll *troller = new Controll();
    Process *processer = new Process();
    Tracking *tracker = new Tracking();
    Serial_Communication *serial = new Serial_Communication("/dev/ttyUSB0");

    // Threads
    QThread *t1 = new QThread;
    QThread *t2 = new QThread;
    QThread *t3 = new QThread;
    camera->moveToThread(t1);
    processer->moveToThread(t2);
    tracker->moveToThread(t3);
    serial->moveToThread(t3);

    // Connections
    qRegisterMetaType<cv::Mat>("cv::Mat");
    QObject::connect(t1, SIGNAL(started()), camera, SLOT(captureImage()));
    QObject::connect(camera, SIGNAL(capturedImage(cv::Mat)), troller, SLOT(inputImage(cv::Mat)));
    QObject::connect(t2, SIGNAL(started()), troller, SLOT(processerReady()));
    QObject::connect(troller, SIGNAL(image(cv::Mat)), processer, SLOT(processImage(cv::Mat)));
    QObject::connect(troller, SIGNAL(requestImage()), camera, SLOT(captureImage()));
    QObject::connect(processer, SIGNAL(posXposY(int,int)), tracker, SLOT(position(int,int)));
    QObject::connect(tracker, SIGNAL(directionAndSpeed(int,int)), serial, SLOT(sendData(int,int)));
    QObject::connect(processer, SIGNAL(readyForWork()), troller, SLOT(processerReady()));
    QObject::connect(processer, SIGNAL(processedImage(cv::Mat)), troller, SLOT(processedImage(cv::Mat)));
    // Need to add finish/clean up stuff for terminating threads.

    // Starting Threads
    t1->start();
    t2->start();
    t3->start();

    // wait for key to exit
    while (true) {
         c = cvWaitKey(1);
        if(c!=-1)
        {
            // Add thread termination before breaking the loop.
            // If pressed, break out of the loop
            break;
        }
    }
    return 0;
}
