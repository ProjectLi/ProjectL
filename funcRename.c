

#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

extern int INFO[_WIDTH + 1][_HEIGHT + 1];

VOID Rename()
{
	INT i, j, k = 0;

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
			}
		}
	}
}
