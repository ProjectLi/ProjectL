#ifndef _CONSOLE_WRAP_H
#define _CONSOLE_WRAP_H

#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


// All possible console color combinations
enum colors
{
	c_black = 0x0000,			// black foreground and background
	b_black = 0xFF0F,			// use it with '& f_color'as a mask instead of '|'
	b_darkred = BACKGROUND_RED,
	b_darkgreen = BACKGROUND_GREEN,
	b_darkblue = BACKGROUND_BLUE,
	b_darkmagenta = BACKGROUND_RED | BACKGROUND_BLUE,
	b_darkyellow = BACKGROUND_RED | BACKGROUND_GREEN,
	b_darkcyan = BACKGROUND_BLUE | BACKGROUND_GREEN,
	b_grey = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN,
	b_red = BACKGROUND_INTENSITY | BACKGROUND_RED,
	b_green = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
	b_blue = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
	b_magenta = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
	b_yellow = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
	b_cyan = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN,
	b_white = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN,

	f_black = 0xFFF0,			// use it with '& b_color'as a mask instead of '|'
	f_darkred = FOREGROUND_RED,
	f_darkgreen = FOREGROUND_GREEN,
	f_darkblue = FOREGROUND_BLUE,
	f_darkmagenta = FOREGROUND_RED | FOREGROUND_BLUE,
	f_darkyellow = FOREGROUND_RED | FOREGROUND_GREEN,
	f_darkcyan = FOREGROUND_BLUE | FOREGROUND_GREEN,
	f_grey = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,
	f_red = FOREGROUND_INTENSITY | FOREGROUND_RED,
	f_green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	f_blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	f_magenta = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	f_yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	f_cyan = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN,
	f_white = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN
};


// --- API prototypes

// TODO: Feel free to include new API-functionality for your needs
// TODO: Some implementations better should be revised and refactored to some common style

BOOL InitConsole(LPSTR Title, SHORT x, SHORT y, WORD color);

//
/*inline*/	BOOL SetColor(WORD color);
/*inline*/  BOOL SetChar(SHORT x, SHORT y, WORD color, CHAR ch);
/*inline*/	BOOL SetPos(SHORT x, SHORT y);
/*inline*/	BOOL WritePos(SHORT x, SHORT y, WORD color, LPSTR string);
/*inline*/	BOOL FillPos(SHORT x, SHORT y, WORD color, CHAR _ch, DWORD qty);
/*inline*/	BOOL Write(WORD color, LPSTR string);
//


#endif
