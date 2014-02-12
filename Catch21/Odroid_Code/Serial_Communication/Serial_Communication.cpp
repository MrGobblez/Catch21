#include "Serial_Communication.h"

Serial_Communication::Serial_Communication(char portID[])
{
	initialize(portID);
}

void Serial_Communication::sendData(int direction, int speed)
{
	// converting int to charbuffer and sending the data over serial.	
	if(direction < -1)
	{
		sprintf (buf, "%d%d.", direction, speed);
	}

	else
	{
		sprintf (buf, "0%d%d.", direction, speed);
	}

	write(fd, buf, 6);
}

void Serial_Communication::initialize(char portID[])
{
	/* open serial port */
	fd = open(portID, O_RDWR | O_NOCTTY);
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
}
