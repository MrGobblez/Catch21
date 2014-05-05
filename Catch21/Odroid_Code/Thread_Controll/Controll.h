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
    void image(IplImage *imgOut);
    void requestImage();
public slots:
    void inputImage(IplImage *imgIn);
    void processedImage(IplImage *imgIn);
    void processerReady();
private:
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
