#include "Low_Repetiton.h"

Low_Repetiton::Low_Repetiton()
{
    window = true;
    speed = true;
}

void Low_Repetiton::menu()
{
    while( true )
    {

         startWindow();
         decision = (char) cv::waitKey(0);

        // input decisions for lowreptetition mode
        switch(decision)
        {
            case 'q': return; // exit program
            break;

            case ' ': // start recording
            if( window == true) // destroys keybinds window when realtime window is to be shown
            {
                cv::destroyWindow("Key Controls");
            }

            // Start write here use emit to start process in bg
            // memoWrite.write(window);

            // cv::waitKey(0) press key to stop recording and start playback.
            if(window == false)
            {
                cv::destroyWindow("Key Controls");
            }
            // memoRead.read(speed);
            // Need to wait unti playback is finished

            break;

            case 's':
                this->setSpeed();
            break;

            case 'w': // show or not show window while recording
                setWindow();
            break;

            default: // catch all
            break;
        } // end  switch
    } // end while loop
}

void Low_Repetiton::setWindow()
{
    window = !window;
}

void Low_Repetiton::startWindow()
{
    cv::Mat image;
    image = cv::imread("./catch21.jpg", CV_LOAD_IMAGE_COLOR); // read image file

    // Use emit to gui class!
    cv::namedWindow("Key Controls", cv::WINDOW_AUTOSIZE); // window to display image
    cvMoveWindow("Key Controls",0,0);
    cv::imshow("Key Controls", image);
}

void Low_Repetiton::setSpeed()
{
    speed = !speed;
}
