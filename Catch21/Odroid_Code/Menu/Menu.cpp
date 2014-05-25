#include "Menu.h"

Menu::Menu()
{
    // Set default options and show Low Rep menu
    window = true;
    speed = true;
    newInput = false;
    lowRepetition = true;
    recording = false;
    lowRep();
}

void Menu::giveInput(char input)
{
    this->decision = input;
    this->newInput = true;
}

void Menu::inputHandler()
{
    while (true)
    {
        // Check for new input or key press
        // #### BUG: this will make 'decision' turn into sonething strange if 'newInput' is false and cv::waitKey times out,
        //      remember to have defaults in the switch to avoid trouble ####
        if (newInput || (decision = (char) cv::waitKey(1)))
        {
            if (decision == '2')
            {
                // Change mode
                changeMode();

            }
            else if (lowRepetition)
            {
                // Low Rep Menu goes here
                switch (decision)
                {
                case 'q':
                    // Quit
                    return;
                    break;
                case 'w':
                    setWindow();
                    break;
                case 's':
                    setSpeed();
                    break;
                case 'a':
                    if (!recording)
                    {
                        emit startRecording(window);
                        if (!window)
                        {
                            recNoWindow();
                        }
                        setRecording();

                    }
                    else
                    {
                        emit stopRecording();
                        setRecording();
                    }
                default:
                    break;
                }
            }
            else
            {
                // High Rep Menu goes here

            }
        }
    }
}

void Menu::changeMode()
{
    lowRepetition = !lowRepetition;
}

void Menu::setWindow()
{
    window = !window;
}

void Menu::lowRep()
{
    menuImg = cv::imread("./catch21.jpg", CV_LOAD_IMAGE_COLOR); // read image file
    emit displayMenu(menuImg);
}

void Menu::setSpeed()
{
    speed = !speed;
}

void Menu::setRecording()
{
    recording = !recording;
}

void Menu::recNoWindow()
{
    menuImg = cv::imread("./rec.jpg", CV_LOAD_IMAGE_COLOR); // read image file
    emit displayMenu(menuImg);
}
