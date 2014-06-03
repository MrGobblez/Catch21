#include "Menu.h"

Menu::Menu()
{
    // Set default options and show Low Rep menu
    window = true;
    newInput = false;
    lowRepetition = true;
    recording = false;
    highRepetitionRunning = false;
}

void Menu::giveInput(char input)
{
    this->decision = input;
    this->newInput = true;

    // Not a good fix, if going with two seperate menus we need mutex or there will be chaos
    // Added something like kind of mutex, for testing
    if (newInput && !keyInputRunning)
    {
        newInput = false;
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
            case 'a':

                qDebug() << "foot rec: " << recording;
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
                break;
            case 's':
                setSpeed();
                break;
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

void Menu::inputHandler()
{
    lowRep();
    while (true)
    {
        // Check for new input or key press
        // #### BUG: this will make 'decision' turn into sonething strange if 'newInput' is false and cv::waitKey times out,
        //      remember to have defaults in the switch to avoid trouble ####
//        qDebug() << "char: " << this->decision;
//        qDebug() << " newInput: " << newInput;
        if (!newInput && (decision = (char) cv::waitKey(100)))
        {
            keyInputRunning = true;
            if (decision == '2')
            {
                // Change mode
                changeMode();
                highRepetitionRunning = false;
                qDebug() << "Mode switch";

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
                case 'a':
                    qDebug() << "key rec: " << recording;
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
                        qDebug() << "Stops recording.";
                        emit stopRecording();
                        emit startPlayback();
                        setRecording();
                    }
                    break;
                case 's':
                    setSpeed();
                    break;
                case 'd':
                    break;
                case '1':
                    // Tracking goes here
                    break;
                default:
                    break;
                }
            }
            else
            {
                // High Rep Menu goes here
                switch (decision)
                {
                case 'q':
                    return;
                    break;
                case 'w':
                    break;
                case 'a':
                    qDebug() << "a";
                    if (!highRepetitionRunning)
                    {
                        emit startHighRep();
                    }
                    else
                    {
                        qDebug() << "High rep is allready running!";
                    }
                    break;
                case 's':
                    emit decreaseDelay();
                    break;
                case 'd':
                    emit increaseDelay();
                    break;
                case '1':
                    // Tracking goes here
                    break;
                default:
                    break;
                }
            }
        }
        keyInputRunning = false;
        emit requestDataFromFootController();
    }
}

void Menu::changeMode()
{
    lowRepetition = !lowRepetition;
    // Stops the current mode
    emit modeSwitch();
    if (!lowRepetition)
    {
        highRep();
    }
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

void Menu::highRep()
{
    menuImg = cv::imread("./Menu/delayMode.jpg", CV_LOAD_IMAGE_COLOR); // read image file
    emit displayMenu(menuImg);
}

void Menu::setSpeed()
{
    emit toggleSlowMotion();
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

void Menu::highRepetitionTogle()
{
    highRepetitionRunning = !highRepetitionRunning;
}
