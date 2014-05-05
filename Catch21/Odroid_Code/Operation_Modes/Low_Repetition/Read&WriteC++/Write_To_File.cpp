#include "Write_To_File.h"
#include <opencv2/opencv.hpp>


Write_To_File::Write_To_File()
{
    cv::VideoCapture cap(0);

    // Check if the capture was opened
    if(!cap.isOpened())
    {
        std::cout << "Capture could not be opened Succesfully" << std::endl;
        return;
    }

    // Get the default size of frames

    cv::Size S = cv::Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH), (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));

    // Create a video writer object and initialize it at 30 fps
    cv::VideoWriter put("output.mpg",CV_FOURCC('M','P','E','G'),30,S);

    // Check if the file were created
    if(!put.isOpened())
    {
        std::cout << "File could not be created" << std::endl;
        return;
    }

    // Create a window to show the frames
    cv::namedWindow("Video");

    // Play the video in a loop till it ends
    while(char(cv::waitKey(1)) != 'q' && cap.isOpened())
    {
        cv::Mat frame;

        cap >> frame;

        // Check if the video is over
        if(frame.empty())
        {
            std::cout << "Video is over" << std::endl;
            break;
        }

        cv::imshow("Video",frame);

        put << frame;

    }

}
