#ifndef SERIAL_COMMUNICATION_H
#define SERIAL_COMMUNICATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <iostream>
#include <QtCore>

class Serial_Communication : public QObject
{
    Q_OBJECT
public:
    Serial_Communication(char portID1[], char portID2[]);
    Serial_Communication(char portID[]);

public slots:
    void sendDataToControlUnit(int direction, int speed);
    void receiveDataFromFootControllerLoop();
	
signals:
    void fromFootController(char fromFootController);

private:
    void receiveData(int targetArduino);
	void initialize(char portID[]);
    void setControllerID();
    int arduinoNumber;
    int controlUnit;
    int footController;
    int fd[2];
    int oldDirection;
    int oldSpeed;
  	char buf[10];
    char lastReceivedChar;
  	struct termios toptions;
    bool sent;
};

#endif
