#ifndef WINDOW_HANDLER_H
#define WINDOW_HANDLER_H
#include <QtCore>
#include <opencv2/highgui/highgui.hpp>

class Window_Handler : public QObject
{
    Q_OBJECT
public:
    Window_Handler();
public slots:
    void drawImage(cv::Mat image);
};

#endif // WINDOW_HANDLER_H
