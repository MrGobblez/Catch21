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
    imageBuffer[counter] = imgIn;

    //cv::imshow("video", imageBuffer[counter]); //Denne henter frame fra lowrep eller highrep
    if (showImage)
    {
        emit imageToShow(imgIn);
    }

    if (processReady) 
    {
        processReady = false;
        emit imageToProcess(imgIn);
    }

    if (recording)
    {
        emit imageToRecord(imgIn);
    }

    ++counter;
    if(counter == 600) //Check if buffer is full, if yes, start to fill it from the start.
    {
        counter = 0;
    }

    emit requestImage();

    // see how much time has elapsed
    time(&end);

    // calculate current FPS
    ++counterOrg;
    sec = difftime (end, start);

    fpsOrg = counterOrg / sec;

    // will print out Inf until sec is greater than 0
//     printf("FPS Org stream = %.2f\n", fpsOrg);

}

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

void Controll::setDelay(int timeshift)
{
    this->delay = timeshift;
}

void Controll::processerReady()
{
    processReady = true;
    //qDebug() << "processer Ready" << QThread::currentThreadId();
}

void Controll::startRecording(bool showWindow)
{
    showImage = showWindow;
    recording = true;
    emit requestImage();
}

void Controll::stopRecording()
{
    // file lock?
    recording = false;
    showImage = false;
    emit startPlayback();
}
