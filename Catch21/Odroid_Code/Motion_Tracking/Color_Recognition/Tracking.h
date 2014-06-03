#ifndef TRACKING_H
#define TRACKING_H

#include <QtCore>
#include <time.h>
#include <stdlib.h>
#include "../Math_Library/PID.h"

class Tracking : public QObject
{
    Q_OBJECT
public:
    Tracking();

public slots:
    void position(int posX, int posY);

signals:
    void directionAndSpeed(int direction, int speed);

private:
    //Functions
    timespec diff(timespec previous, timespec now);

    //Sampling & time control
    timespec currentTime;
    timespec lastTime;

    PID pid;

    int lastUserPos;
    int userPos;
    int direction;
    double speed;
    double userSpeed;
};

#endif // TRACKING_H
