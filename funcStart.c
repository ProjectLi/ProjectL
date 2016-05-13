
#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

int INFO[_WIDTH + 1][_HEIGHT + 1];

VOID Start()
{
	INT i, j;
	DWORD key = 0;
	Clear();
	for (i = 0; i <= _HEIGHT + 7; i++)
	{
		for (j = 0; j <= _WIDTH; j++)
		{
			SetChar(j, 0, f_yellow | b_yellow, ' ');
		}
		SetChar(0, i, f_yellow | b_yellow, ' ');
		SetChar(_WIDTH, i, f_yellow | b_yellow, ' ');
	}


	WritePos(15, 13, f_red, "1.  Старт");
	WritePos(15, 15, f_red, "2.  Выход");

	do{
	if (_kbhit()) key = _getch();
	switch (key)
	{
		case '1':
		{
			key = 0;

			WritePos(15, 13, f_red, "                      ");
			WritePos(15, 13, f_red, "1.  Классический режим");
			WritePos(15, 15, f_red, "                            ");
			WritePos(15, 15, f_red, "2.  Режим с доп. настройками");

			do{
			if (_kbhit()) key = _getch();
			switch (key)
			{
				case '1':
				{
					//Стандартный, классический
					Classic();
					Start();
				}
				case '2':
				{
					//Пользовательский
					Custom();
					Start();
				}
			}
			} while (TRUE);
		}
		case '2': exit(0);
	}
	} while (TRUE);
}
