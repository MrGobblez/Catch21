#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <opencv2/opencv.hpp>
#include <QtCore>
#include <unistd.h>

class File_Handler : public QObject
{
    Q_OBJECT
public:
    File_Handler();
public slots:
    void readFromFile();
    void writeImage(cv::Mat imageIn);
signals:
    void showFrame(cv::Mat frame);
    void readyToWrite();
private:
    void createFile();

    cv::VideoWriter inFile;
    cv::VideoCapture outFile;
    cv::Size resolution;
    cv::Mat frame;

    int delay;
    double frameRate;
};

#endif // FILE_HANDLER_H
