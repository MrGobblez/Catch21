#ifndef TRACKING_H
#define TRACKING_H

#include <QtCore>

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
    int direction;
    int speed;
};

#endif // TRACKING_H
