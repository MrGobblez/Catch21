#include "Serial_Communication.h"

Serial_Communication::Serial_Communication(char portID[])
{
    arduinoNumber = 0;
    sent = false;
    initialize(portID);
}

void Serial_Communication::receiveDataFromFootControllerLoop()
{
    receiveData(footController);
    if (lastReceivedChar == 'a' && !sent)
    {
        qDebug() << "emitting: " << lastReceivedChar;
        emit fromFootController(lastReceivedChar);
        sent = true;
    }
}

Serial_Communication::Serial_Communication(char portID1[], char portID2[])
{
    arduinoNumber = 0;
    initialize(portID1);
    initialize(portID2);
}

void Serial_Communication::sendDataToControlUnit(int direction, int speed)
{
    if (direction != this->oldDirection || speed != this->oldSpeed)
    {
        // Updates vars
        this->oldDirection = direction;
        this->oldSpeed = speed;

        // converting int to charbuffer and sending the data over serial.
        if(direction <= -1)
        {
            sprintf (buf, "%d%d.", direction, speed);
        }

        else
        {
            sprintf (buf, "0%d%d.", direction, speed);
        }

        // Sends data
        write(fd[controlUnit], buf, 6);
    }

    else
    {
//         qDebug() << "skipped, old == new";
    }
}

void Serial_Communication::receiveData(int targetArduino)
{
    bytesRead = read(fd[targetArduino], buf, 10);
//    qDebug() << "bytesRead :"<< bytesRead;
    if (bytesRead >= 0)
    {
      lastReceivedChar = buf[0];
      sent = false;
    }
    // Flushing buffer
    tcflush(fd[targetArduino], TCIOFLUSH);

}

void Serial_Communication::initialize(char portID[])
{
	/* open serial port */
    fd[arduinoNumber] = open(portID, O_RDWR | O_NOCTTY | O_NONBLOCK);
    printf("fd[%i] opened as %i\n", arduinoNumber, fd[arduinoNumber]);
    usleep(3500000);

	/* get current serial port settings */
    tcgetattr(fd[arduinoNumber], &toptions);
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
    tcsetattr(fd[arduinoNumber], TCSANOW, &toptions);

    // Give the correct work to the right Arduino
    setControllerID();

    // Ready for next Arduino
    arduinoNumber++;
}

void Serial_Communication::setControllerID()
{
    // Ask for ID
    write(fd[arduinoNumber], ".12345.", 7);
    usleep(100000);
    receiveData(arduinoNumber);

    // Set controller ID
    if (lastReceivedChar == 'F')
    {
        footController = arduinoNumber;
        qDebug() << "Arduino Number " << arduinoNumber << " is the Foot Controller";
    }

    else if (lastReceivedChar == 'C')
    {
        controlUnit = arduinoNumber;
        qDebug() << "Arduino Number " << arduinoNumber << " is the Control Unit";
    }

    else
    {
        qDebug() << lastReceivedChar << ", unknown ID" ;
    }
}
