#ifndef CONTROLL_H
#define CONTROLL_H

#include <QtCore>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

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
};

#endif // CONTROLL_H
