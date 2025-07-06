/* ‘ConLib.h’ */

 /* Avoid redefinition */
#pragma once

 /* Windows standard header file */
#include <windows.h>
#include <iostream>

 /* ConLib color codes */
 enum ConColor
 {
    ConRed = 1,
    ConGreen = 2,
    ConBlue = 4
 };

 /* ConLib control class */
 class Conlib
 {
  HANDLE m_Screen;
  HANDLE m_Keyboard;

 /* Color attributes */
  WORD m_TextColor;
  WORD m_BackgroundColor;

 public:

 /* Constructor / destructor */
    Conlib ();
    ~Conlib ();
    /* Set attributes */
    void SetBackgroundColor (WORD Color);
    void SetTextColor (WORD Color);
    void SetTitle (std::string);
    void SetPosition (COORD Position);

    /* Output methods */
    void Clear (void);
    void OutputString (std::string);

    /* Input methods */
    void Read (char * Buffer, DWORD BufferSize);
    int GetKey (void);

 };