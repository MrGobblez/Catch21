#ifndef CONTROL_H
#define CONTROL_H

#include <QtCore>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <time.h> // for fps calculation, debug, remove in release.

class Control : public QObject
{
    Q_OBJECT
public:
    Control();
signals:
    void imageToShow(cv::Mat ingOut);
    void imageToProcess(cv::Mat imgOut);
    void imageToRecord(cv::Mat imgOut);
    void requestImage();

public slots:
    void inputImage(cv::Mat imgIn);
    void processedImage(cv::Mat imgIn);
    void startDelayMode();
    void endMode();
    void increaseDelay();
    void decreaseDelay();
    void calculateTimeshift();
    void processerReady();
    void startRecording(bool showWindow);
    void stopRecording();
    void fileHandlerReadyToWrite();
    void toggleTracking();

private:
    void stop();
    cv::Vector<cv::Mat>imageBuffer; // create buffer to hold images
    int counter;
    int delay;
    int delayedFrame;

    bool processReady;
    bool recording;
    bool showImage;
    bool readyToWrite;
    bool delayMode;
    bool tracking;

    //start and end times
    time_t start, end;
    // fps calculated using number of frames / seconds
    double fpsOrg, fpsProcessed;
    // frame counter
    int counterOrg, counterProcessed;
    // floating point seconds elapsed since start
    double sec;
};

#endif // CONTROLL_H
