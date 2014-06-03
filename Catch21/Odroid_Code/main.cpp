#include <QtCore>
#include <QCoreApplication>
#include <QMetaType>
#include "Camera/OpenCV/Camerainput.h"
#include "Control/Control.h"
#include "Motion_Tracking/Color_Recognition/Process.h"
#include "Motion_Tracking/Color_Recognition/Tracking.h"
#include "Serial_Communication/Serial_Communication.h"
#include "Menu/Menu.h"
//#include "Operation_Modes/Low_Repetition/Low_Repetition_Version3/Menu.h"
#include "File_Handler/File_Handler.h"
#include "GUI/Window_Handler/Window_Handler.h"

Q_DECLARE_METATYPE(cv::Mat);
int main()
{
    // Objects
    CameraInput *camera = new CameraInput();
    Control *controller = new Control();
    Process *processer = new Process();
    Tracking *tracker = new Tracking();
//    Serial_Communication *serial = new Serial_Communication("/dev/ttyUSB0", "/dev/ttyUSB1");
    Serial_Communication *serial = new Serial_Communication("/dev/ttyUSB0");// #### For testing with only one arduino
    File_Handler *file_Handler = new File_Handler();
    Window_Handler *window_Handler = new Window_Handler();
    Menu *menu = new Menu();


    // Threads
    QThread *t1 = new QThread;
    QThread *t2 = new QThread;
    QThread *t3 = new QThread;
    QThread *t4 = new QThread;
    QThread *t5 = new QThread;

    camera->moveToThread(t1);
    processer->moveToThread(t2);
    tracker->moveToThread(t3);
    serial->moveToThread(t3);
    controller->moveToThread(t4);
    file_Handler->moveToThread(t5);

    // Connect signals to slots. Whenever a signal is emitted in a function, its corresponding (connected) function will run.
    qRegisterMetaType<cv::Mat>("cv::Mat");

    //Signals calling from:
    //Main thread
    QObject::connect(menu, SIGNAL(startRecording(bool)), controller, SLOT(startRecording(bool)));
    QObject::connect(menu, SIGNAL(stopRecording()), controller, SLOT(stopRecording()));
    QObject::connect(menu, SIGNAL(displayMenu(cv::Mat)), window_Handler, SLOT(drawImage(cv::Mat)));
    QObject::connect(menu, SIGNAL(requestDataFromFootController()), serial, SLOT(receiveDataFromFootControllerLoop()));
    QObject::connect(menu, SIGNAL(startHighRep()), controller, SLOT(startDelayMode()));
    QObject::connect(menu, SIGNAL(decreaseDelay()), controller, SLOT(decreaseDelay()));
    QObject::connect(menu, SIGNAL(increaseDelay()), controller, SLOT(increaseDelay()));
    QObject::connect(menu, SIGNAL(modeSwitch()), controller, SLOT(endMode()));
    QObject::connect(menu, SIGNAL(startPlayback()), file_Handler, SLOT(readFromFile()));
    QObject::connect(menu, SIGNAL(toggleSlowMotion()), file_Handler, SLOT(toggleSlowMotion()));
    QObject::connect(menu, SIGNAL(toggleTracking()), controller, SLOT(toggleTracking()));

    //Thread 1
    QObject::connect(t1, SIGNAL(started()), camera, SLOT(captureImage()));
    QObject::connect(camera, SIGNAL(capturedImage(cv::Mat)), controller, SLOT(inputImage(cv::Mat)));

    //Thread 2
    QObject::connect(t2, SIGNAL(started()), controller, SLOT(processerReady()));
    QObject::connect(processer, SIGNAL(posXposY(int,int)), tracker, SLOT(position(int,int)));
    QObject::connect(processer, SIGNAL(readyForWork()), controller, SLOT(processerReady()));

    //Thread 3
    QObject::connect(tracker, SIGNAL(directionAndSpeed(int,int)), serial, SLOT(sendDataToControlUnit(int,int)));
    QObject::connect(serial, SIGNAL(fromFootController(char)), menu, SLOT(giveInput(char)));

    //Thread 4
    QObject::connect(t4, SIGNAL(started()), controller, SLOT(fileHandlerReadyToWrite()));
    QObject::connect(controller, SIGNAL(imageToProcess(cv::Mat)), processer, SLOT(processImage(cv::Mat)));
    QObject::connect(controller, SIGNAL(requestImage()), camera, SLOT(captureImage()));
    QObject::connect(controller, SIGNAL(imageToRecord(cv::Mat)), file_Handler, SLOT(writeImage(cv::Mat)));
    QObject::connect(controller, SIGNAL(imageToShow(cv::Mat)), window_Handler, SLOT(drawImage(cv::Mat)));
    QObject::connect(controller, SIGNAL(stopMotor()), serial, SLOT(stopMotor()));

    //Thread 5
    QObject::connect(file_Handler, SIGNAL(showFrame(cv::Mat)), window_Handler, SLOT(drawImage(cv::Mat)));
    QObject::connect(file_Handler, SIGNAL(readyToWrite()), controller, SLOT(fileHandlerReadyToWrite()));
    QObject::connect(file_Handler, SIGNAL(timeout()), file_Handler, SLOT(playVideo()));
    QObject::connect(file_Handler, SIGNAL(playbackEnded()), menu, SLOT(returnToLowRep()));

    // Starting Threads
    t1->start();
    t2->start();
//    t3->start();
    t4->start();
    t5->start();

//    menu->menu();
    menu->inputHandler();
    return 0;
}
