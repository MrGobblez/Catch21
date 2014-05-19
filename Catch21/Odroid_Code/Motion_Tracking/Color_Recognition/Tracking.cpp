#include "Tracking.h"

Tracking::Tracking()
{
}

//This whole function just checks the position of the tracked object, then moves the camera in that direction with increasing speed as the object nears the camera edge.
void Tracking::position(int posX, int posY)
{
    if(posX < 150)
        {
            this->direction = -1;
        }

    else if (posX > 490)
        {
            this->direction = 1;
        }

    else
        {
            this->direction = 0;
        }


        //GOING LEFT OF PICTURE
    if(posX < 160 && posX > 140)
        {
            this->speed = 150;
        }

    else if (posX < 140 && posX > 120)
        {
            this->speed = 200;
        }

    else if (posX < 120 && posX > 80)
        {
            this->speed = 300;
        }

    else if (posX < 80 && posX > 40)
        {
            this->speed = 540;
        }

    else if (posX < 40)
        {
            this->speed = 600;
        }

        //GOING RIGHT OF PICTURE
    else if (posX > 480 && posX < 500)
        {
            this->speed = 150;
        }

    else if (posX > 500 && posX < 520)
        {
            this->speed = 200;
        }

    else if (posX > 520 && posX < 560)
        {
            this->speed = 300;
        }

    else if (posX > 560 && posX < 600)
        {
            this->speed = 540;
        }

    else if (posX > 600)
        {
            this->speed = 600;
        }

        //IN THE MIDDLE OF THE PICTURE
    else
        {
            this->speed = 0;
        }
    //qDebug() << "tracker" << direction << speed << QThread::currentThreadId();
    emit directionAndSpeed(direction,speed);
}
