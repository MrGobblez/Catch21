#ifndef DYNAMIC_DELAY_H
#define DYNAMIC_DELAY_H

class Dynamic_Delay
{
public:
    Dynamic_Delay();
signals:
    void upDelay();
    void downDelay();
    void delay(int timeshift);
public slots:
    void increaseDelay();
    void decreaseDelay();
    void setDelayedFrames(int timeshift);
};

#endif // DYNAMIC_DELAY_H
