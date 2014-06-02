#include "Tracking.h"

Tracking::Tracking()
{
    pid = PID();

    clock_gettime(CLOCK_REALTIME, &lastTime);
    clock_gettime(CLOCK_REALTIME, &currentTime);

    lastUserPos = 0;
}

//This whole function just checks the position of the tracked object, then moves the camera in that direction with increasing speed as the object nears the camera edge.
void Tracking::position(int posX, int posY)
{
    /*//In case posX is totally wrong for one reason or another.
    if(posX > 640 || posX < -0)
    {
        posX = 320;
    }
    //What time is it now.
    clock_gettime(CLOCK_REALTIME, &currentTime);

    //Map user position so that it's from -320 to 320 instead of 0 to 640.
    userPos = posX - 320;

    //Determine current userSpeed, convert pixels/nanosec into pixels/sec
    double temp;
    temp = (userPos - lastUserPos);
    userSpeed = temp/diff(currentTime, lastTime).tv_nsec;
    userSpeed *= 1000000000;

    speed = pid.calculate(userSpeed);
    speed = 10*speed;
    unsigned int finalSpeed = speed;
    if(posX > 280 && posX < 360)
        {
            this->direction = 0;
        }

    else if (userSpeed > 0)
        {
            this->direction = -1;
        }

    else
        {
            this->direction = 1;
        }

    //qDebug() << "userPos: " << userPos << "lastUserPos: " << lastUserPos << "temp" << temp << "movement speed" << userSpeed;
    qDebug() << "direction: " << direction << "speed: " << finalSpeed;
    lastUserPos = userPos;
    clock_gettime(CLOCK_REALTIME, &lastTime);
    emit directionAndSpeed(direction,(unsigned int) finalSpeed);*/
    // OLD TRACKING SOFTWARE
    if(posX > 280 && posX < 360)
        {
            this->direction = 0;
        }

    else if (posX < 280)
        {
            this->direction = -1;
        }

    else
        {
            this->direction = 1;
        }

    //GOING RIGHT OF PICTURE
    if (posX < 280 && posX >= 278)
        {
            this->speed = 10;
        }

    else if (posX < 278 && posX >= 276)
        {
            this->speed = 20;
        }

    else if (posX < 276 && posX >= 274)
        {
            this->speed = 30;
        }

    else if (posX < 274 && posX >= 272)
        {
            this->speed = 45;
        }

    else if (posX < 272 && posX >= 270)
        {
            this->speed = 65;
        }

    else if (posX < 270 && posX >= 265)
        {
            this->speed = 100;
        }

    else if (posX < 265 && posX >= 260)
        {
            this->speed = 150;
        }

    else if (posX < 260 && posX >= 240)
        {
            this->speed = 200;
        }

    else if (posX < 240 && posX >= 210)
        {
            this->speed = 250;
        }

    else if (posX < 210 && posX >= 180)
        {
            this->speed = 300;
        }

    else if (posX < 180 && posX >= 150)
        {
            this->speed = 316;
        }

    else if (posX < 150 && posX >= 140)
        {
            this->speed = 333;
        }

    else if (posX < 140 && posX >= 130)
        {
            this->speed = 353;
        }

    else if (posX < 130 && posX >= 120)
        {
            this->speed = 375;
        }

    else if(posX < 120 && posX >= 110)
        {
            this->speed = 400;
        }

    else if (posX < 110 && posX >= 100)
        {
            this->speed = 428;
        }

    else if (posX < 100 && posX >= 90)
        {
            this->speed = 461;
        }

    else if (posX < 90 && posX >= 80)
        {
            this->speed = 500;
        }

    else if (posX < 80 && posX >= 70)
        {
            this->speed = 545;
        }

    else if (posX < 70)
        {
            this->speed = 600;
        }

        //GOING LEFT OF PICTURE
    else if (posX > 360 && posX <= 362)
        {
            this->speed = 10;
        }

    else if (posX > 362 && posX <= 364)
        {
            this->speed = 20;
        }

    else if (posX > 364 && posX <= 366)
        {
            this->speed = 30;
        }

    else if (posX > 366 && posX <= 368)
        {
            this->speed = 45;
        }

    else if (posX > 368 && posX <= 370)
        {
            this->speed = 65;
        }

    else if (posX > 370 && posX <= 375)
        {
            this->speed = 100;
        }

    else if (posX > 375 && posX <= 380)
        {
            this->speed = 150;
        }

    else if (posX > 380 && posX <= 400)
        {
            this->speed = 200;
        }

    else if (posX > 400 && posX <= 430)
        {
            this->speed = 250;
        }

    else if (posX > 430 && posX <= 460)
        {
            this->speed = 300;
        }

    else if (posX > 460 && posX <= 490)
        {
            this->speed = 316;
        }

    else if (posX > 490 && posX <= 500)
        {
            this->speed = 333;
        }

    else if (posX > 500 && posX <= 510)
        {
            this->speed = 353;
        }

    else if (posX > 510 && posX <= 520)
        {
            this->speed = 375;
        }

    else if(posX > 520 && posX <= 530)
        {
            this->speed = 400;
        }

    else if (posX > 530 && posX <= 540)
        {
            this->speed = 428;
        }

    else if (posX > 540 && posX <= 550)
        {
            this->speed = 461;
        }

    else if (posX > 550 && posX <= 560)
        {
            this->speed = 500;
        }

    else if (posX > 560 && posX <= 570)
        {
            this->speed = 545;
        }

    else if (posX > 570)
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

//Calculates the time since last sample.
timespec Tracking::diff(timespec previous, timespec now)
{
    timespec temp;
    if ((now.tv_nsec-previous.tv_nsec)<0)
    {
        temp.tv_sec = now.tv_sec-previous.tv_sec-1;
        temp.tv_nsec = 1000000000+now.tv_nsec-previous.tv_nsec;
    }
    else
    {
        temp.tv_sec = now.tv_sec-previous.tv_sec;
        temp.tv_nsec = now.tv_nsec-previous.tv_nsec;
    }

    return temp;
}
