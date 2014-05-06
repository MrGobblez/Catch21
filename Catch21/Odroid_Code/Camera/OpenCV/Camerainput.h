#ifndef CAMERAINPUT_H
#define CAMERAINPUT_H

#include <QtCore>
#include <opencv2/highgui/highgui.hpp>

class CameraInput : public QObject
{
    Q_OBJECT
public:
    CameraInput();
signals:
    void capturedImage(cv::Mat *frame);
public slots:
    void captureImage();
private:
    //VARIABLES
    cv::Mat frame;
    cv::VideoCapture cap;
};

#endif // CAMERAINPUT_H
