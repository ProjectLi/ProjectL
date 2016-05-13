#include <stdio.h>
#include "FUNC.h"

VOID Classic()
{
	Interface();
	DWORD key = 0;
	RandomFirstGen();
	Ch();

	do
	{
		key = _getch();
		SecondGen();
		//key = _getch();
		DeathGen();
		//key = _getch();
		Rename();
		Ch();
	} while(key != '0');

}

