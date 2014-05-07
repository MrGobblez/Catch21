#ifndef DYNAMIC_DELAY_H
#define DYNAMIC_DELAY_H

class Dynamic_Delay
{
public:
    Dynamic_Delay();
    int increaseDelay();
    int decreaseDelay();
    void setDelayedFrames(int frameDelay);
    int getDelayedFrames();

private:
    int delayedFrames;
};

#endif // DYNAMIC_DELAY_H
