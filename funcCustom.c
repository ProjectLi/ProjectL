#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

extern int INFO[_WIDTH + 1][_HEIGHT + 1];

VOID Custom()
{
	Interface();
	DWORD key = 0;
	RandomFirstGen();
	Ch();

	do
	{
		_getch();
		CustomSecondGen();
		_getch();
		CustomDeathGen();
		key = _getch();
		CustomRename();
		Ch();
	} while(key != '0');
}

