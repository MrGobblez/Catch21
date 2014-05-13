#ifndef CONTROLL_H
#define CONTROLL_H

#include <QtCore>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <time.h>

class Controll : public QObject
{
    Q_OBJECT
public:
    Controll();
signals:
    void image(cv::Mat imgOut);
    void requestImage();
public slots:
    void inputImage(cv::Mat imgIn);
    void processedImage(cv::Mat imgIn);
    void increaseDelay();
    void decreaseDelay();
    void setDelay(int timeshift);
    void processerReady();
private:
    cv::Vector<cv::Mat>imageBuffer; // create buffer to hold images
    int counter;
    int delay;
    bool processReady;
    // start and end times
    time_t start, end;
    // fps calculated using number of frames / seconds
    double fpsOrg, fpsProcessed;
    // frame counter
    int counterOrg, counterProcessed;
    // floating point seconds elapsed since start
    double sec;
};

#endif // CONTROLL_H
