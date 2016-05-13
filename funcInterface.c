#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

extern int INFO[_WIDTH + 1][_HEIGHT + 1];

VOID Interface()
{
	SHORT i;

	// In case of changed background color
	SetChar(0, 0, c_black, ' ');
	system("cls");

	// Up row
	FillPos(0, 0, f_darkyellow, '#', _WIDTH + 1);
	// Down row
	FillPos(0, _HEIGHT, f_darkyellow, '#', _WIDTH + 1);
	FillPos(0, _HEIGHT + 6, f_darkyellow, '#', _WIDTH + 1);
	// Side columns
	for (i = 1; i < _HEIGHT + 6; i += 1)
	{
		SetChar(0, i, f_darkyellow, '#');
		SetChar(_WIDTH, i, f_darkyellow, '#');
	}

	WritePos(2, _HEIGHT + 1, f_red, "Первое поколение:                  [       ] ");
	WritePos(2, _HEIGHT + 2, f_blue, "Второе поколение:                  [       ] ");
	WritePos(2, _HEIGHT + 3, f_cyan, "Мертвые:                           [       ] ");
}
