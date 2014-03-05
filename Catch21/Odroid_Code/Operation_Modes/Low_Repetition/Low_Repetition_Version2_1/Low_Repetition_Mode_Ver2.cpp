// Low_Repetition_Mode.cpp

#include "Low_Repetition_Mode_Ver2.h"
#include "Read_From_Memory_Ver2.h"
#include "Write_To_Memory_Ver2.h"
#include <iostream>
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>


    Write_To_Memory_Ver2 memoWrite; // object of write to memory class
    Read_From_Memory_Ver2 memoRead; //



    Low_Repetition_Mode_Ver2::Low_Repetition_Mode_Ver2()
    {

        //Read_From_Memory memoRead;
       // cv::namedWindow("Recording", CV_WINDOW_AUTOSIZE);

	window = true;
	speed = true;

        // mouselock function in open cv
        // make empty window

    } // end constructor

    Low_Repetition_Mode_Ver2::~Low_Repetition_Mode_Ver2()
    {

    }


    // menu that lets users control record and replay abillities

    void Low_Repetition_Mode_Ver2::menu()
    {
        // char c = (char) cv::waitKey(50)
        while( true )
        {

             this->startWindow();
             decision = (char) cv::waitKey(0);
             // call startWindowBehaviour
            // input decisions for lowreptetition mode
            switch(decision)
            {
                case 'q': return; // exit program
                break;

                case ' ': // start recording
                if( window == true) // destroys keybinds window when realtime window is to be shown
                {
                    cv::destroyWindow("Key Controls");
                } //

                memoWrite.write(this->getWindow());
                if(window == false)
                {

                    cv::destroyWindow("Key Controls");
                }
                memoRead.read(speed);

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
    } // end function menu


    bool Low_Repetition_Mode_Ver2::getWindow()
    {
        return window;
    }

    // setWindow toggles variable window value
    void Low_Repetition_Mode_Ver2::setWindow()
    {
        if(window == true)
        {
            window = false;
        } // end if
        else
        {
            window = true;
        } // end if
    } // end setWindow

    // setSpeed toggles variable speed value
    void Low_Repetition_Mode_Ver2::setSpeed()
    {
        if(speed == true)
        {
            speed= false;
        } // end if
        else
        {
            speed = true;
        } // end if
    } // end setWindow

    bool Low_Repetition_Mode_Ver2::getSpeed()
    {
        return speed;
    }

    char Low_Repetition_Mode_Ver2::getDecision()
    {
        return decision;
    }
    void Low_Repetition_Mode_Ver2::setDecision( char i )
    {
        decision = i;
    }

    void Low_Repetition_Mode_Ver2::startWindow()
    {


        cv::Mat image;
        image = cv::imread("./catch21.jpg", CV_LOAD_IMAGE_COLOR); // read image file
        cv::namedWindow("Key Controls", cv::WINDOW_AUTOSIZE); // window to display image
        cvMoveWindow("Key Controls",0,0);              //!!!USING C AT THE MOMENT!!!
        cv::imshow("Key Controls", image);


    }


