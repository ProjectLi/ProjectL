#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

extern int INFO[_WIDTH + 1][_HEIGHT + 1];

VOID Ch()
{
	INT i, j, k = 0, ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{

			if (INFO[j][i] == 1)
			{
				ch++;
			}
			if (INFO[j][i] == 3)
			{
				SetChar(j, i, c_black, ' ');
			}
		}
	}
	//Если при отрисовке предыдущее значение было больше нынешнего, то нарисуется "поверх".
	//Это нежелательно, потому как отображаться будет неверное значение.
	SetPos(38, _HEIGHT + 1);
	//Потому мы указываем координаты, и затираем их, прежде чем писать наше значение.
	printf("    ");
	SetColor(f_red);
	printf("%d", ch);
}
