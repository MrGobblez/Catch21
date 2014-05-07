#include "Dynamic_Delay.h"
#include <iostream>

int main()
{
    Dynamic_Delay mydelay;
    int frameDelay;

    frameDelay = mydelay.getDelayedFrames();

    std::cout << "number of frames delayed by default" <<frameDelay << std::endl;

    frameDelay = mydelay.increaseDelay();
    frameDelay = mydelay.increaseDelay();


    std::cout << "number of frames after 2 increases" << frameDelay << std::endl;

    frameDelay = mydelay.decreaseDelay();

    std::cout << "number of frames after 1 decrease" << frameDelay << std::endl;

    frameDelay = mydelay.decreaseDelay();
    frameDelay = mydelay.decreaseDelay();
    frameDelay = mydelay.decreaseDelay();
    frameDelay = mydelay.decreaseDelay();
    frameDelay = mydelay.decreaseDelay();
    frameDelay = mydelay.decreaseDelay();

    std::cout << "number of frames after 6 decreases" << frameDelay << std::endl;

    return 0;




}

