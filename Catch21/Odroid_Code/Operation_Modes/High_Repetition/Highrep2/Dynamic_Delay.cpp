#include "Dynamic_Delay.h"

Dynamic_Delay::Dynamic_Delay()
{
} // end constructor

void Dynamic_Delay::increaseDelay()
{
    emit upDelay();
}

void Dynamic_Delay::decreaseDelay()
{
    emit downDelay();
}

int Dynamic_Delay::setDelayedFrames(int timeshift)
{
    emit delay(timeshift);
}



