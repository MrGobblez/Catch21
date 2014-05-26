#include "Tracking.h"

Tracking::Tracking()
{
}

//This whole function just checks the position of the tracked object, then moves the camera in that direction with increasing speed as the object nears the camera edge.
void Tracking::position(int posX, int posY)
{
    if(posX < 300)
        {
            this->direction = -1;
        }

    else if (posX > 340)
        {
            this->direction = 1;
        }

    else
        {
            this->direction = 0;
        }


        //GOING RIGHT OF PICTURE
    if (posX < 300 && posX >= 280)
        {
            this->speed = 20;
        }

    else if (posX < 280 && posX >= 260)
        {
            this->speed = 30;
        }

    else if (posX < 260 && posX >= 250)
        {
            this->speed = 50;
        }

    else if (posX < 250 && posX >= 245)
        {
            this->speed = 70;
        }

    else if (posX < 245 && posX >= 240)
        {
            this->speed = 80;
        }

    else if (posX < 240 && posX >= 235)
        {
            this->speed = 90;
        }

    else if (posX < 235 && posX >= 230)
        {
            this->speed = 140;
        }

    else if (posX < 230 && posX >= 225)
        {
            this->speed = 200;
        }

    else if (posX < 225 && posX >= 220)
        {
            this->speed = 270;
        }

    else if (posX < 220 && posX >= 210)
        {
            this->speed = 300;
        }

    else if (posX < 210 && posX >= 200)
        {
            this->speed = 316;
        }

    else if (posX < 200 && posX >= 180)
        {
            this->speed = 333;
        }

    else if (posX < 180 && posX >= 160)
        {
            this->speed = 353;
        }

    else if (posX < 160 && posX >= 140)
        {
            this->speed = 375;
        }

    else if(posX < 140 && posX >= 120)
        {
            this->speed = 400;
        }

    else if (posX < 120 && posX >= 100)
        {
            this->speed = 428;
        }

    else if (posX < 100 && posX >= 80)
        {
            this->speed = 461;
        }

    else if (posX < 80 && posX >= 60)
        {
            this->speed = 500;
        }

    else if (posX < 60 && posX >= 40)
        {
            this->speed = 545;
        }

    else if (posX < 40)
        {
            this->speed = 600;
        }

        //GOING LEFT OF PICTURE
    else if (posX > 340 && posX <= 360)
        {
            this->speed = 20;
        }

    else if (posX > 360 && posX <= 380)
        {
            this->speed = 30;
        }

    else if (posX > 380 && posX <= 390)
        {
            this->speed = 50;
        }

    else if (posX > 390 && posX <= 395)
        {
            this->speed = 70;
        }

    else if (posX > 395 && posX <= 400)
        {
            this->speed = 80;
        }

    else if (posX > 400 && posX <= 405)
        {
            this->speed = 90;
        }

    else if (posX > 405 && posX <= 410)
        {
            this->speed = 140;
        }

    else if (posX > 410 && posX <= 415)
        {
            this->speed = 200;
        }

    else if (posX > 415 && posX <= 420) 
        {
            this->speed = 270;
        }

    else if (posX > 420 && posX <= 430)
        {
            this->speed = 300;
        }

    else if (posX > 430 && posX <= 440)
        {
            this->speed = 316;
        }

    else if (posX > 440 && posX <= 460)
        {
            this->speed = 333;
        }

    else if (posX > 460 && posX <= 480)
        {
            this->speed = 353;
        }

    else if (posX > 480 && posX <= 500)
        {
            this->speed = 375;
        }

    else if(posX > 500 && posX <= 520)
        {
            this->speed = 400;
        }

    else if (posX > 520 && posX <= 540)
        {
            this->speed = 428;
        }

    else if (posX > 540 && posX <= 560)
        {
            this->speed = 461;
        }

    else if (posX > 560 && posX <= 580)
        {
            this->speed = 500;
        }

    else if (posX > 580 && posX <= 600)
        {
            this->speed = 545;
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
    qDebug() << "direction: " << direction << "speed: " << speed;
    emit directionAndSpeed(direction,speed);
}
