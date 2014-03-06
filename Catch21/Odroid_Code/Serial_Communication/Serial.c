/*
Prototype for serial communication between Linux (Odroid) and arduino over serial connection. Currently a mix of c and c++, compile with g++.

This code is based on:

https://github.com/cheydrick/Canonical-Arduino-Read/blob/master/canonicalarduinoread.c
www.chrisheydrick.com
June 23 2012

CanonicalArduinoRead write a byte to an Arduino, and then
receives a serially transmitted string in response.
*/

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

#define DEBUG 1
  
int main(int argc, char *argv[])
{
  int fd, n, i;
  char inDigi[1];
  char buf[64] = "temp text";
  struct termios toptions;

  /* open serial port */
  fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
  printf("fd opened as %i\n", fd);
  
  /* wait for the Arduino to reboot * Removed the reboot with capacitor between gnd and rst pins. Remove to reflash!
  usleep(3500000);*/
  
  /* get current serial port settings */
  tcgetattr(fd, &toptions);
  /* set 9600 baud both ways */
  cfsetispeed(&toptions, B9600);
  cfsetospeed(&toptions, B9600);
  /* 8 bits, no parity, no stop bits */
  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;
  /* Canonical mode */
  toptions.c_lflag |= ICANON;
  /* commit the serial port settings */
  tcsetattr(fd, TCSANOW, &toptions);

  // Takes in a char from keyboard and sends it to the arduino will be removed later when implemented in our main software.
  std::cout << "Please input a digit to send to the arduino" << std::endl;
  std::cin >> inDigi[0];
  
  write(fd, inDigi, 1);
  /* Receive string from Arduino will wait until something is transmitted, have tested with delay(1000) on arduino*/
  n = read(fd, buf, 64);
  /* insert terminating zero in the string */
  buf[n] = 0;

  printf("%i bytes read, buffer contains: %s\n", n, buf);

  // Not needed
  if(DEBUG)
    {
      printf("Printing individual characters in buf as integers...\n\n");
      for(i=0; i<n; i++)
	{
		printf("Byte %i:%i, ",i+1, (int)buf[i]);
	}
      printf("\n");
    }

  return 0;
}
