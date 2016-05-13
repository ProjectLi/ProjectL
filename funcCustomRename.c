#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

extern int INFO[_WIDTH + 1][_HEIGHT + 1];

VOID CustomRename()
{
	INT i, j, custom;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{
			if (INFO[j][i] == 0)
			{
				INFO[j][i] = 3;
				SetChar(j, i, c_black, ' ');
			}
			else
			if (INFO[j][i] == 2)
			{
				INFO[j][i] = 1;
				SetChar(j, i, f_red, '1');

				custom = rand() % 100000 + 1;

				if (custom > 0 && custom <= 10) //бессмертная клетка, шанс 0,01%
				{
					INFO[j][i] = 4;
					SetChar(j, i, f_green, '3');
				}

				if (custom > 10 && custom <= 110) //клетка-сметрник, шанс 0,1%
				{
					INFO[j][i] = 5;
					SetChar(j, i, f_yellow, '4');
				}

				if (custom > 110 && custom <= 210) //клетка-любовник, шанс 0,1%
				{
					INFO[j][i] = 6;
					SetChar(j, i, f_magenta, '5');
				}
				//
			}
		}
	}
}

