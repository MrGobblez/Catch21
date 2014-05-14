#ifndef LOW_REPETITON_H
#define LOW_REPETITON_H
#include <QtCore>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Menu : public QObject
{
    Q_OBJECT
public:
    Menu();
    void menu(); // control functions for recording video
signals:
    void startRecording(bool showWindow);
    void stopRecording();
    void displayMenu(cv::Mat menu);
private:
    void setWindow(); // toggle window to on/off
    void startWindow(); // window that shows the keycommands
    void setSpeed();
    void recNoWindow();
    bool window; // if true film is to be recorded with window showing rt
    bool speed; // toogles normal or slowmotion
    char decision; // holds the key pressed that makes the decision in recording/playback video control
    cv::Mat menuImg;
};

#endif // LOW_REPETITON_H
