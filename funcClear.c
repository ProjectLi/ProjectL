#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

extern int INFO[_WIDTH + 1][_HEIGHT + 1];

VOID Clear()
{
	for (int i = 0; i < _HEIGHT + 1; i++)
	{
		for (int j = 0; j < _WIDTH + 1; j++)
		{
			INFO[j][i] = 3;
		}
	}
}
