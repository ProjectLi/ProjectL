#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

extern int INFO[_WIDTH + 1][_HEIGHT + 1];

VOID CustomSecondGen()
{
	INT i, j, k = 0, dth = 0, ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{

			//если в радиусе есть клетка любовник, то клеткка сразу становится вторым поколением
			if (INFO[j][i - 1] == 6 || INFO[j][i + 1] == 6 || INFO[j - 1][i] == 6 ||  INFO[j + 1][i] == 6 ||
				INFO[j + 1][i + 1] == 6 || INFO[j + 1][i - 1] == 6 || INFO[j - 1][i + 1] == 6 || INFO[j - 1][i - 1] == 6)
			{
				INFO[j][i] = 2;
				SetChar(j, i, f_blue, '2');
				k++;
			}
			//если нет то проверяем, может клетка итак должна была стать таковой
			else

			if (INFO[j][i] == 3)
			{

				if (INFO[j + 1][i + 1] == 1)
				{
					ch++;
				}

				if (INFO[j - 1][i - 1] == 1)
				{
					ch++;
				}

				if (INFO[j + 1][i - 1] == 1)
				{
					ch++;
				}


				if (INFO[j - 1][i + 1] == 1)
				{
					ch++;
				}

				//

				if (INFO[j + 1][i] == 1)
				{
					ch++;
				}

				if (INFO[j][i + 1] == 1)
				{
					ch++;
				}

				if (INFO[j - 1][i] == 1)
				{
					ch++;
				}

				if (INFO[j][i - 1] == 1)
				{
					ch++;
				}


				if (ch == 3 || ch > 3)
				{
					INFO[j][i] = 2;
					SetChar(j, i, f_blue, '2');
					k++;
				}

				ch = 0;

			}
		}
	}

	SetPos(42, _HEIGHT + 2);
	printf("%d", k);
}
