#include"Conlib.h"
#include<iostream>

Conlib::Conlib (){
    m_Screen = GetStdHandle (STD_OUTPUT_HANDLE);
    m_Keyboard = GetStdHandle (STD_INPUT_HANDLE);

    SetTextColor (ConRed| ConGreen | ConBlue);
    SetBackgroundColor(0);
}

Conlib::~Conlib ()
{

}

//set Text Color

void Conlib::SetBackgroundColor (WORD Color) {
    m_BackgroundColor = 0;

    //bit manip to get color combination

    if (Color & ConRed) {
        m_BackgroundColor |= BACKGROUND_RED;

    }
     if (Color & ConGreen) {
        m_BackgroundColor |= BACKGROUND_GREEN;
        
    }
     if (Color & ConBlue) {
        m_BackgroundColor |= BACKGROUND_BLUE;
        
    }


    SetConsoleTextAttribute (m_Screen, m_TextColor | m_BackgroundColor);
}

//set Text Color
void Conlib::SetTextColor (WORD Color){
    m_TextColor |= 0;

    //bit manip for color combination
    if (Color & ConRed) {
        m_BackgroundColor |= FOREGROUND_RED;

    }
    if (Color & ConGreen) {
        m_BackgroundColor |= FOREGROUND_GREEN;

    }
    if (Color & ConBlue) {
        m_BackgroundColor |= FOREGROUND_RED;

    }

    SetConsoleTextAttribute (m_Screen, m_TextColor | m_BackgroundColor);

}

//windows title

void Conlib::SetTitle (std::string Title){
    SetConsoleTitleA(Title.c_str());
}

//clear the Screen

void Conlib::Clear(void){
    COORD Start;
    DWORD Written;
    Start.X = 0;
    Start.Y = 0;

    FillConsoleOutputAttribute(m_Screen, m_TextColor | m_BackgroundColor, 80*24, Start, &Written);
    FillConsoleOutputCharacter (m_Screen, ' ', 80*25, Start, &Written);
    SetConsoleCursorPosition(m_Screen, Start);
}

//sets cursor position

void Conlib::SetPosition (COORD Position){
    SetConsoleCursorPosition(m_Screen, Position);
}

//sets string to the screen

void Conlib::OutputString (std::string Smth){
    DWORD Written ;
    WriteConsoleA(m_Screen, Smth.c_str(), Smth.length(), &Written, NULL);
}

//key from keyboard

int Conlib::GetKey (void){
    DWORD Read;
    INPUT_RECORD Event;

    ReadConsoleInput (m_Keyboard, &Event, 1, &Read);
    if (Event.EventType == KEY_EVENT){
        if (Event.Event.KeyEvent.bKeyDown){
            return Event.Event.KeyEvent.wVirtualKeyCode;
        }
    }

    return 0;
}