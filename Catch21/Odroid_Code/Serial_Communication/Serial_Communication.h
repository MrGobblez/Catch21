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

class Serial_Communication
{
	public:
	Serial_Communication(String portID);
	void sendData(int data);
	
	private:
	void initialize(String portID);
	int fd;
  	char buf[6] = "00000.";
  	struct termios toptions;

#endif
