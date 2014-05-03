#include "File_Handler.h"

File_Handler::File_Handler()
{
    resolution = cv::Size((int)640, (int)480);
    emit readyToWrite();
}

void File_Handler::readFromFile()
{
    inFile.release(); // Does not need it, but if not used the same file will contain all data
    // Create a Video Capture object to read from a video file
    outFile.open("video/output.mpg");

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
    // Play the video in a loop till it ends
    while(char(cv::waitKey(1)) != 'q' && outFile.isOpened())
    {
        outFile >> frame;

        // Check if the video is over
        if(frame.empty())
        {
            qDebug() << "Video from file reached its end...";
            outFile.release();
            return;
        }

        emit showFrame(frame);
        // Introduce an artificial delay between the refreshing of each frame to keep correct frame rate
        if(char(cv::waitKey(delay)) == ' ')
        {
             qDebug() << "!!!Manually Stopped!!!";
             break;
        }
    }
}

void File_Handler::writeImage(cv::Mat imageIn)
{
    // Checks if file exists, if not create
    if(!inFile.isOpened())
    {
        createFile();
        // Add error handling!
    }

    qDebug() << "_";
    inFile << imageIn;
    emit readyToWrite();
}

void File_Handler::createFile()
{

    // Create a video writer object and initialize it at 30 fps and correct resolution
    inFile.open("video/output.mpg",CV_FOURCC('M','J','P','G'),30,resolution);

    // Check if the file were created
    if(!inFile.isOpened())
    {
        qDebug() << "File could not be created";
    }
}
