#ifndef PROCESS_H
#define PROCESS_H

#include <QtCore>
#include <opencv/cv.h>
#include "opencv2/highgui/highgui.hpp"

class Process : public QObject
{
    Q_OBJECT
public:
    Process();
public slots:
    void processImage(IplImage *img);
signals:
    void posXposY(int posX, int posY);
    void readyForWork();
    void processedImage(IplImage *img);
private:
    int posX, posY;
};

#endif // PROCESS_H
