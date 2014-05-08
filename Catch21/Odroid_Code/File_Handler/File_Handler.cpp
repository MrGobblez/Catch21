#include "File_Handler.h"

FileHandler::FileHandler()
{
    resolution = cv::Size((int)640, (int)480);
}

void FileHandler::readFromFile()
{
    // inFile.release(); does not need, but if not used the same file will all data
    // Create a Video Capture object to read from a video file
    outFile.open("output.mpg");

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

    // frameRate == 0! codec bug? Sets delay for 30 fps...
    delay = 33;

    cv::namedWindow("Video from file");

    // Play the video in a loop till it ends
    while(char(cv::waitKey(1)) != 'q' && outFile.isOpened())
    {
        cv::Mat frame;
        outFile >> frame;

        // Check if the video is over
        if(frame.empty())
        {
            qDebug() << "Video from file reached its end...";
            break;
        }

        cv::imshow("Video from file",frame);

        // Introduce an artificial delay between the refreshing of each frame
        if(char(cv::waitKey(delay)) == ' ')
        {
             qDebug() << "!!!Manually Stopped!!!";
             break;
        }

    }
    outFile.release();
}

void FileHandler::writeImage(cv::Mat imageIn)
{
    // Checks if file exists, if not create
    if(!inFile.isOpened())
    {
        createFile();
        // Add error handling!
    }
    inFile << imageIn;
}

void FileHandler::createFile()
{

    // Create a video writer object and initialize it at 30 fps and correct resolution
    inFile.open("output.mpg",CV_FOURCC('M','J','P','G'),30,resolution);

    // Check if the file were created
    if(!inFile.isOpened())
    {
        qDebug() << "File could not be created";
    }
}
