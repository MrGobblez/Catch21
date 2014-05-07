#include "Dynamic_Delay.h"

Dynamic_Delay::Dynamic_Delay()
{
    delayedFrames = 60;

} // end constructor


void Dynamic_Delay::increaseDelay()
{
    if( (delayedFrames + 60) <= 599)
    {
        delayedFrames += 60;
    }
    else
    {
        delayedFrames = 599;
    }
}

void Dynamic_Delay::decreaseDelay()
{
    if( (delayedFrames-60) >= 0 )
    {
        delayedFrames -= 60;
    }
    else
    {
        delayedFrames = 0;
    }
}

void Dynamic_Delay::setDelayedFrames(int frameDelay)
{
   delayedFrames = frameDelay;

}

int Dynamic_Delay::getDelayedFrames()
{
    return delayedFrames;
}


