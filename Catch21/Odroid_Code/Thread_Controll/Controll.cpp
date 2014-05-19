#include "Controll.h"

Controll::Controll()
{
    processReady = false;
    counterOrg = 0;
    counterProcessed = 0;
    // start the clock
    time(&start);
    imageBuffer = cv::Vector<cv::Mat>(600);
    counter = 0;
    delay = 0;
    recording = false;
    showImage = false;
}

void Controll::inputImage(cv::Mat imgIn)
{
    //Add new frame to buffer
    imageBuffer[counter] = imgIn;

    //If stream is to be shown, send an image
    if (showImage)
    {
        emit imageToShow(imgIn);
    }

    //If the Process object is ready, pass a new frame for processing
    if (processReady) 
    {
        processReady = false;
        emit imageToProcess(imgIn);
    }

    //If recording video, pass a frame to be written to file
    if (recording)
    {
        emit imageToRecord(imgIn);
    }

    ++counter;
    if(counter == 600) //Check if buffer is full, if yes, start to fill it from the start.
    {
        counter = 0;
    }

    //Ask for a new frame
    emit requestImage();


    /////////////////////////////////////////////////FPS DEBUGING/////////////////////////////////////////////////
    // see how much time has elapsed
    time(&end);

    // calculate current FPS
    ++counterOrg;
    sec = difftime (end, start);

    fpsOrg = counterOrg / sec;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

//This whole function is to debug processed images
void Controll::processedImage(cv::Mat imgIn)
{
    qDebug() << "About to show thresh image...";
    cv::imshow("thresh", imgIn);  // move to gui obj by emit
    // see how much time has elapsed
    time(&end);

    // calculate current FPS
    ++counterProcessed;
    sec = difftime (end, start);

    fpsProcessed = counterProcessed / sec;

    // will print out Inf until sec is greater than 0
    printf("FPS processed stream = %.2f\n", fpsProcessed);
}

//Increase video delay by 15 frames.
void Controll::increaseDelay()
{
    if(this->delay < 584)
    {
        delay += 15;
    }

    else
    {
        int temp = 0;
        temp = (this->delay+15)-599;
        this->delay = temp;
    }
}

//Decrease video delay by 15 frames.
void Controll::decreaseDelay()
{
    if(this->delay > 15)
    {
        delay -= 15;
    }

    else
    {
        int temp = 0;
        temp = 599 - (this->delay-15);
        this->delay = temp;
    }
}

//Specify video delay.
void Controll::setDelay(int timeshift)
{
    this->delay = timeshift;
}

//Set Process object ready for new frame.
void Controll::processerReady()
{
    processReady = true;
}

//Start recording, causing frames to be written to file and a window to display frames from buffer.
void Controll::startRecording(bool showWindow)
{
    showImage = showWindow;
    recording = true;
    emit requestImage();
}

//Stop writing files to file and show the recorded stream in the window.
void Controll::stopRecording()
{
    // file lock?
    recording = false;
    showImage = false;
    emit startPlayback();
}
