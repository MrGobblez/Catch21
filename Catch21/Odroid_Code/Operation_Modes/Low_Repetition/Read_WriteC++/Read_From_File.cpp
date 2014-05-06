#include "Read_From_File.h"
#include <opencv2/opencv.hpp>

Read_From_File::Read_From_File()
{
    // Create a Video Capture object to read from a video file
    cv::VideoCapture cap("output.mpg");

    //Check if the file was opened properly
    if(!cap.isOpened())
    {
        std::cout << "Capture could not be opened succesfully" << std::endl;
        return;
    }

    // Get the framerate
    double frameRate = cap.get(CV_CAP_PROP_FPS);

    // The delay between each frame in ms corresponds to video frame rate
    int delay = 1000/frameRate;

    cv::namedWindow("Video from file");

    // Play the video in a loop till it ends
    while(char(cv::waitKey(1)) != 'q' && cap.isOpened())
    {
        cv::Mat frame;
        cap >> frame;

        // Check if the video is over
        if(frame.empty())
        {
            std::cout << "Video from file reached its end..." << std::endl;
            break;
        }

        cv::imshow("Video from file",frame);

        // Introduce an artificial delay between the refreshing of each frame
        if(cv::waitKey(delay)>= 0)
        {
             std::cout << "!!!Manually Stopped!!!" << std::endl;
             break;
        }

    }


}
