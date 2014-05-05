#ifndef CAMERAINPUT_H
#define CAMERAINPUT_H

#include <QtCore>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

class CameraInput : public QObject
{
    Q_OBJECT
public:
    CameraInput();
signals:
    void capturedImage(IplImage *img);
public slots:
    void captureImage();
private:
    //VARIABLES
    CvCapture *capture;
    IplImage *frame;
};

#endif // CAMERAINPUT_H
