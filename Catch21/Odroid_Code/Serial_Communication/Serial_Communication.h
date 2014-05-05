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
	Serial_Communication(char portID[]);

public slots:
	void sendData(int direction, int speed);
	
private:
	void initialize(char portID[]);
	int fd;
  	char buf[];
  	struct termios toptions;
};

#endif
