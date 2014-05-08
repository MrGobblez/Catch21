#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <opencv2/opencv.hpp>
#include <QtCore>

class FileHandler : public QObject
{
    Q_OBJECT
public:
    FileHandler();
    void readFromFile();
public slots:
    void writeImage(cv::Mat imageIn);
private:
    void createFile();
    cv::VideoWriter inFile;
    cv::VideoCapture outFile;
    cv::Size resolution;
    int delay;
    double frameRate;
};

#endif // FILE_HANDLER_H
