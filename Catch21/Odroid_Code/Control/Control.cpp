#include "Control.h"

Control::Control()
{
    processReady = false;
    counterOrg = 0;
    counterProcessed = 0;
    // start the clock
    time(&start);
    imageBuffer = cv::Vector<cv::Mat>(600);
    counter = 0;
    delay = 150;        // Default 5s. delay
    recording = false;
    showImage = false;
    readyToWrite = false;
    delayMode = false;
    tracking = false;
}

void Control::inputImage(cv::Mat imgIn)
{
    //Add new frame to buffer
    imageBuffer[counter] = imgIn.clone();
//    qDebug() << "showImage: " << showImage << "processReady: " << processReady << "Recording: " << recording;

    // Calculate delayedFrame
    if (delayMode)
    {
        calculateTimeshift();
    }

    //If stream is to be shown, send an image
    if (showImage)
    {
        if (delayMode)
        {
            emit imageToShow(imageBuffer[delayedFrame]);
        }

        else
        {
            emit imageToShow(imageBuffer[counter]);
        }
    }

    //If the Process object is ready, pass a new frame for processing
    if (processReady && tracking)
    {
        processReady = false;
        emit imageToProcess(imageBuffer[counter]);
    }

    //If recording video, pass a frame to be written to file
    if (recording)// && readyToWrite)
    {
        readyToWrite = false;
        emit imageToRecord(imageBuffer[counter]);
    }

    ++counter;
    if(counter == 600) //Check if buffer is full, if yes, start to fill it from the start.
    {
        counter = 0;
    }

    // Chek if there are frames in the buffer before trying to show them!
    if (delayMode && counter > 150)
    {
        showImage = true;
    }

//    qDebug() << "delay is: " << delay;
    // Add stuff for checking if the Delay mode is just started, and wait before enabling the imageToShow();
    // Crashes if given a possition in the buffer with no frame!

    // Ask for a new frame
    emit requestImage();


//    /////////////////////////////////////////////////FPS DEBUGING/////////////////////////////////////////////////
//    // see how much time has elapsed
//    time(&end);

//    // calculate current FPS
//    ++counterOrg;
//    sec = difftime (end, start);

//    fpsOrg = counterOrg / sec;
//    qDebug() << "Calling for new image: " << fpsOrg;
//    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

//This whole function is to debug processed images
void Control::processedImage(cv::Mat imgIn)
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

void Control::startDelayMode()
{
    // Adjust setting to enable delay mode
    delayMode = true;
}

void Control::endMode()
{
    stop();
}

//Increase video delay by 15 frames.
void Control::increaseDelay()
{
    if(this->delay < 584)
    {
        delay += 15;
    }

    else
    {
        qDebug() << "Max delay reached!";
    }
}

//Decrease video delay by 15 frames.
void Control::decreaseDelay()
{
    if(this->delay > 15)
    {
        delay -= 15;
    }

    else
    {
        qDebug() << "No delay!";
    }
}

void Control::calculateTimeshift()
{
    delayedFrame = counter - delay;
    if (delayedFrame < 0)
    {
        delayedFrame = delayedFrame + 599;
    }
}

//Set Process object ready for new frame.
void Control::processerReady()
{
    processReady = true;
}

//Start recording, causing frames to be written to file and a window to display frames from buffer.
void Control::startRecording(bool showWindow)
{
    showImage = showWindow;
    recording = true;
}

//Stop writing files to file and show the recorded stream in the window.
void Control::stopRecording()
{
    qDebug() << "In stopRecording()";
    stop();
}

void Control::fileHandlerReadyToWrite()
{
    readyToWrite = true;
}

void Control::toggleTracking()
{
    tracking = !tracking;
    if (!tracking)
    {
        emit stopMotor();
    }
}

void Control::stop()
{
    recording = false;
    showImage = false;
    delayMode = false;
}
