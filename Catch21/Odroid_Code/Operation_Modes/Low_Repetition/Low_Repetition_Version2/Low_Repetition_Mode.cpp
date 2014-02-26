#include "Read_From_Memory.h"
#include "Write_To_Memory.h"
#include <iostream>
#include <stdio.h>


    Low_Repetition_Mode::Low_Repetition_Mode()
    {
        Write_To_Memory memoWrite;
        Read_From_Memory memoRead;

    } // end constructor


    // menu that lets users control record and replay abillities

    void menu()
    {
        while( (this->decision=cin.get()) !=EOF )
        {
            // input decisions for lowreptetition mode
            switch(decision)
            {
                case 'q': return; // exit program
                break;

                case ' ': // start recording
                memoWrite.write(getWindow());
                memoRead.read();
                break;

                case 's': // show or not show window while recording
                    setWindow();
                break;

                default: // catch all
                break;
            } // end  switch
        } // end while loop
    } // end function menu


    bool getWindow()
    {
        return window;
    }

    // setWindow toggles variable window value
    void setWindow()
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

    char getDecision()
    {
        return decision;
    }
    void setDecision( char i )
    {
        decision = i;
    }

