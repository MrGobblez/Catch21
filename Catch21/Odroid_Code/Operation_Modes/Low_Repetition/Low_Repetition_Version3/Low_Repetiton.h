#ifndef LOW_REPETITON_H
#define LOW_REPETITON_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Low_Repetiton
{
public:
    Low_Repetiton();
    void menu(); // control functions for recording video

private:
    void setWindow(); // toggle window to on/off
    void startWindow(); // window that shows the keycommands
    void setSpeed();
    bool window; // if true film is to be recorded with window showing rt
    bool speed; // toogles normal or slowmotion
    char decision; // holds the key pressed that makes the decision in recording/playback video control
};

#endif // LOW_REPETITON_H
