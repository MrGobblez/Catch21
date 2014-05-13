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

            emit startRecording(window);
            if (!window)
            {
                recNoWindow();
            }

            cv::waitKey(0); //press key to stop recording and start playback.
            emit stopRecording();

            // Need to wait unti playback is finished ** Needs better solution!
            cv::waitKey(0); // press key to continiue

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
    menuImg = cv::imread("./catch21.jpg", CV_LOAD_IMAGE_COLOR); // read image file
    emit displayMenu(menuImg);
}

void Low_Repetiton::setSpeed()
{
    speed = !speed;
}

void Low_Repetiton::recNoWindow()
{
    menuImg = cv::imread("./rec.jpg", CV_LOAD_IMAGE_COLOR); // read image file
    emit displayMenu(menuImg);
}
