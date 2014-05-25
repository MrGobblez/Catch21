#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Menu : public QObject
{
    Q_OBJECT
public:
    Menu();
    void inputHandler();

signals:
    void startRecording(bool showWindow);
    void stopRecording();
    void displayMenu(cv::Mat menu);

public slots:
    void giveInput(char input);

private:
    void changeMode();
    void setWindow(); // toggle window to on/off
    void lowRep(); // window that shows the keycommands
    void setSpeed();
    void setRecording();
    void recNoWindow();
    bool window; // if true film is to be recorded with window showing rt
    bool speed; // toogles normal or slowmotion
    bool newInput; // true if unused input from foot controller
    bool lowRepetition; // mode toggler
    bool recording; // keeps track of recording in low rep
    char decision; // holds the key pressed that makes the decision in recording/playback video control
    cv::Mat menuImg;

};

#endif // MENU_H
