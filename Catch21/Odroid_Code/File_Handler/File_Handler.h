#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <opencv2/opencv.hpp>
#include <QtCore>

class FileHandler : public QObject
{
    Q_OBJECT
public:
    FileHandler();
public slots:
    void readFromFile();
    void writeImage(cv::Mat imageIn);
signals:
    void showFrame(cv::Mat frame);
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
