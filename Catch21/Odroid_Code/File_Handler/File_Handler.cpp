#include "File_Handler.h"

File_Handler::File_Handler()
{
    resolution = cv::Size((int)640, (int)480);
    emit readyToWrite();
}

void File_Handler::readFromFile()
{
    qDebug() << "playback";
    inFile.release(); // Does not need it, but if not used the same file will contain all data

    // Create a Video Capture object to read from a video file
    outFile.open("video/output.avi");

    //Check if the file was opened properly
    if(!outFile.isOpened())
    {
        qDebug() << "Capture could not be opened succesfully";
        return;
    }

    // Get the framerate ****BUG! returns 0!
    frameRate = outFile.get(CV_CAP_PROP_FPS);

    // The delay between each frame in ms corresponds to video frame rate
    delay = 1000/frameRate;

    // frameRate < 0! codec bug? Sets delay for 30 fps...
    if (delay < 1)
    {
        delay = 33;
    }

    qDebug() << frameRate;
    qDebug() << delay;
    start(delay);
}

void File_Handler::writeImage(cv::Mat imageIn)
{
    // Checks if file exists, if not create
    if(!inFile.isOpened())
    {
        createFile();
        // Add error handling!
    }

    inFile << imageIn;
}

void File_Handler::toggleSlowMotion()
{
    // Toggles between normal speed (30fps) and half speed (15fps)
    qDebug() << "toggleSlowMotion";
    if (delay < 40)
    {
        delay = 66;
    }

    else if (delay > 40)
    {
        delay = 33;
    }
    setInterval(delay);
}

void File_Handler::createFile()
{

    // Create a video writer object and initialize it at 30 fps and correct resolution
    // Use CV_FOURCC('D','I','V','X') for Odroid until a faster codec is found
    inFile.open("video/output.avi",CV_FOURCC('D','I','V','X'),30,resolution, true);

    // Check if the file were created
    if(!inFile.isOpened())
    {
        qDebug() << "File could not be created";
    }
}

void File_Handler::playVideo()
{
    // Checks if the file is open and plays it with the use of Qtimer
    if (outFile.isOpened())
    {
        outFile >> frame;

        // Check if the video is over
        if(frame.empty())
        {
            qDebug() << "Video from file reached its end...";
            outFile.release();
            stop();
        }

        else
        {
            emit showFrame(frame);
        }
    }

    else
    {
        qDebug() << "No open file!";
    }
}
