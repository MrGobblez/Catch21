#include "Dynamic_Delay.h"
#include <iostream>

int main()
{
    Dynamic_Delay mydelay;



    std::cout << "number of frames delayed by default" <<    mydelay.getDelayedFrames()
 << std::endl;

    mydelay.increaseDelay();
    mydelay.increaseDelay();


    std::cout << "number of frames after 2 increases" << mydelay.getDelayedFrames()<< std::endl;

    mydelay.decreaseDelay();

    std::cout << "number of frames after 1 decrease" << mydelay.getDelayedFrames() << std::endl;

     mydelay.decreaseDelay();
     mydelay.decreaseDelay();
     mydelay.decreaseDelay();
     mydelay.decreaseDelay();
     mydelay.decreaseDelay();
     mydelay.decreaseDelay();

    std::cout << "number of frames after 6 decreases " << mydelay.getDelayedFrames() << std::endl;

    return 0;




}

