#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "consolewrap.h"


// --- Temporal internal variables
static DWORD tmpDword;

// --- Console abstraction structure for internal use
static struct
{
	CONSOLE_SCREEN_BUFFER_INFOEX propEx;
	CONSOLE_SCREEN_BUFFER_INFO prop;
	CONSOLE_FONT_INFOEX font;
	CONSOLE_CURSOR_INFO cursor;
	HANDLE hIn, hOut;
	COORD pos;
}
console;


// TODO: Feel free to include new API-functionality for your needs
// TODO: Some implementations better should be revised and refactored to some common style


// --- API implementations

// Initializes console window with predefined title, size, font and cursor settings
BOOL InitConsole(LPSTR Title, SHORT x, SHORT y, WORD color)
{
	BOOL result;
	// COORD NNEW;

	// Standard handle obtaining
	console.hIn = GetStdHandle(STD_INPUT_HANDLE);
	console.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	result = (console.hIn != INVALID_HANDLE_VALUE && console.hOut != INVALID_HANDLE_VALUE);

	// Title
	result = SetConsoleTitle(Title);

	// Font setup
	console.font.cbSize = sizeof(console.font);  // (!) structure size needs to be specified first
	//result = result && GetCurrentConsoleFontEx(console.hOut, FALSE, &console.font);
	console.font.nFont = 8;
	console.font.dwFontSize.X = 7;
	console.font.dwFontSize.Y = 14;
	console.font.FontFamily = 54;
	console.font.FontWeight = 400;
	wsprintfW(console.font.FaceName, L"%s", L"Consolas");
	result = result && SetCurrentConsoleFontEx(console.hOut, FALSE, &console.font);

	// Screen buffer info obtaining and setup
	console.propEx.cbSize = sizeof(console.propEx);  // (!) structure size needs to be specified first
	result = result && GetConsoleScreenBufferInfoEx(console.hOut, &console.propEx);
	console.propEx.dwSize.X = console.propEx.srWindow.Right = console.propEx.dwMaximumWindowSize.X = x;
	console.propEx.dwSize.Y = console.propEx.srWindow.Bottom = console.propEx.dwMaximumWindowSize.Y = y;
	console.propEx.wAttributes = color;
	// console.propEx.bFullscreenSupported = TRUE; /* Makes no sense */
	result = result && SetConsoleScreenBufferInfoEx(console.hOut, &console.propEx);

	// Can't be done under win server 2012
	// result = result && SetConsoleDisplayMode(console.hOut, CONSOLE_FULLSCREEN_MODE, &NNEW);

	// Cursor info replacing to invisible
	console.cursor.bVisible = FALSE;
	console.cursor.dwSize = 1;
	result = result && SetConsoleCursorInfo(console.hOut, &console.cursor);

	// The best is yet to come...

	/**/
	return result;
}



// Gets current console size
/*inline*/ COORD GetSize()
{
	return console.propEx.dwSize;
}




// Gets current cursor position in console
/*inline*/ COORD GetPos()
{
	return console.pos;
}



// Sets the cursor position to specified coordinates
/*inline*/ BOOL SetPos(SHORT x, SHORT y)
{
	console.pos.X = x;
	console.pos.Y = y;
	return SetConsoleCursorPosition(console.hOut, console.pos);
}



// Sets the color attributes for console output
/*inline*/ BOOL SetColor(WORD color)
{
	return SetConsoleTextAttribute(console.hOut, color);
}

// Sets the color attributes for console output
/*inline*/ BOOL FlushConsole(WORD color)
{
	DWORD count = console.propEx.dwSize.X*console.propEx.dwSize.Y;
	console.pos.X = 0;
	console.pos.Y = 0;
	return FillConsoleOutputAttribute(console.hOut, color, count, console.pos, &tmpDword) && FillConsoleOutputCharacter(console.hOut, ' ', count, console.pos, &tmpDword);
}


// Changes console window size to specified rows and columns count
BOOL ResizeConsole(SHORT x, SHORT y)
{
	BOOL result;

	// Screen buffer info obtaining and setup
	console.propEx.cbSize = sizeof(console.propEx);  // (!) structure size needs to be specified first
	result = GetConsoleScreenBufferInfoEx(console.hOut, &console.propEx);
	console.propEx.dwSize.X = console.propEx.srWindow.Right = console.propEx.dwMaximumWindowSize.X = x;
	console.propEx.dwSize.Y = console.propEx.srWindow.Bottom = console.propEx.dwMaximumWindowSize.Y = y;
	// console.propEx.bFullscreenSupported = TRUE; /* Makes no sense */
	result = result && SetConsoleScreenBufferInfoEx(console.hOut, &console.propEx);
	return result;
}

// Changes console window size to specified rows and columns count, filling new areas with specified color
/*inline*/ BOOL ResizeConsoleEx(SHORT x, SHORT y, WORD color)
{
	console.pos.X = 0;
	console.pos.Y = 0;
	return SetConsoleTextAttribute(console.hOut, color) && ResizeConsole(x, y) &&
		FillConsoleOutputAttribute(console.hOut, color, x*y, console.pos, &tmpDword);
}



// Retrieves singlebyte character from current cursor position
/*inline*/ CHAR GetCurrentChar()
{
	CHAR result = 0x0;
	ReadConsoleOutputCharacter(console.hOut, &result, 1, console.pos, &tmpDword);
	return result;
}

// Retrieves singlebyte character from current cursor position
/*inline*/ CHAR GetChar(SHORT x, SHORT y)
{
	CHAR result = 0x0;
	console.pos.X = x;
	console.pos.Y = y;
	ReadConsoleOutputCharacter(console.hOut, &result, 1, console.pos, &tmpDword);
	return result;
}

// Retrieves singlebyte character from current cursor position
/*inline*/ CHAR GetCharEx(COORD _pos)
{
	CHAR result = 0x0;
	ReadConsoleOutputCharacter(console.hOut, &result, 1, _pos, &tmpDword);
	return result;
}

// Writes singlebyte character to console output with selected attributes from cursor position
/*inline*/ BOOL SetCurrentChar(WORD color, CHAR ch)
{
	if (SetConsoleTextAttribute(console.hOut, color))
	{
		putchar(ch);
		return TRUE;
	}
	return FALSE;
}

// Writes singlebyte character to console output with selected attributes from cursor position
/*inline*/ BOOL SetChar(SHORT x, SHORT y, WORD color, CHAR ch)
{
	if (SetPos(x, y) && SetConsoleTextAttribute(console.hOut, color))
	{
		putchar(ch);
		return TRUE;
	}
	return FALSE;
}

// Writes singlebyte character to console output with selected attributes from cursor position
/*inline*/ BOOL SetCharEx(COORD _pos, WORD color, CHAR ch)
{
	if (SetPosEx(_pos) && SetConsoleTextAttribute(console.hOut, color))
	{
		putchar(ch);
		return TRUE;
	}
	return FALSE;
}



// Writes plain text string to console output with selected attributes from cursor position
extern /*inline*/ BOOL Write(WORD color, LPSTR string)
{
	if (SetConsoleTextAttribute(console.hOut, color))
	{
		printf(string);
		return TRUE;
	}
	return FALSE;
}

// Writes plain text string to console output with selected attributes from cursor position
/*inline*/ BOOL WritePos(SHORT x, SHORT y, WORD color, LPSTR string)
{
	if (SetPos(x, y) && SetConsoleTextAttribute(console.hOut, color))
	{
		printf(string);
		return TRUE;
	}
	return FALSE;
}







// Internal error info text buffer
static char info[2048] = "(null)";

// Inline bool to text substitution macro
#define I2BStr(x) ((x)?"TRUE":"FALSE")

