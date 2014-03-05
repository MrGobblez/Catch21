#ifndef LOWREPETITIONMODE_H
#define LOWREPETITIONMODE_H

class Low_Repetition_Mode_Ver2
{
public:
    Low_Repetition_Mode_Ver2(); // constructor
    ~Low_Repetition_Mode_Ver2(); // destructor

    void menu(); // control functions for recording video
    bool getWindow(); // return if window is shown or not
    void setWindow(); // toggle window to on/off
    char getDecision(); // return key pressed for control of recording and playback
    void setDecision(char); // start recording, playback, toggle display window on and off
    void startWindow(); // window that shows the keycommands
    void setSpeed();
    bool getSpeed();

private:
    bool window; // if true film is to be recorded with window showing rt
    bool speed; // toogles normal or slowmotion
    char decision; // holds the key pressed that makes the decision in recording/playback video control
    };
#endif // LOWREPETITIONMODE_H
