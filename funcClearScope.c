#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

VOID ClearScope()
{
	int j, i;
	for (i = 0; i < _HEIGHT + 1; i++)
	{
		INFO[0][i] = 3;    //Левая граница по вертикали
		INFO[_WIDTH][i] = 3;    //Правая граница по вертикали
	}


	for (j = 0; j < _WIDTH + 1; j++)
	{

		INFO[j][0] = 3;   //Верхняя сторона по горизонтали
		INFO[j][_HEIGHT];     //Нижняя сторона по горизонтали
	}

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
}
