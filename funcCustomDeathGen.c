#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

extern int INFO[_WIDTH + 1][_HEIGHT + 1];

VOID CustomDeathGen()
{
	INT i, j, k = 0, dth = 0, ch = 0, death_ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{
			if (INFO[j][i] == 1 || INFO[j][i] == 6)
			{

				if (INFO[j + 1][i + 1] == 1 || INFO[j + 1][i + 1] == 6 || INFO[j + 1][i + 1] == 4 || INFO[j + 1][i + 1] == 0)
				{
					ch++;
				}

				if (INFO[j - 1][i - 1] == 1 || INFO[j - 1][i - 1] == 6 || INFO[j - 1][i - 1] == 4 || INFO[j - 1][i - 1] == 0)
				{
					ch++;
				}

				if (INFO[j + 1][i - 1] == 1 || INFO[j + 1][i - 1] == 6 || INFO[j + 1][i - 1] == 4 || INFO[j + 1][i - 1] == 0)
				{
					ch++;
				}


				if (INFO[j - 1][i + 1] == 1 || INFO[j - 1][i + 1] == 6 || INFO[j - 1][i + 1] == 4 || INFO[j - 1][i + 1] == 0)
				{
					ch++;
				}

				//

				if (INFO[j + 1][i] == 1 || INFO[j + 1][i] == 6 || INFO[j + 1][i] == 4 || INFO[j + 1][i] == 0)
				{
					ch++;
				}

				if (INFO[j][i + 1] == 1 || INFO[j][i + 1] == 6 || INFO[j][i + 1] == 4 || INFO[j][i + 1] == 0)
				{
					ch++;
				}

				if (INFO[j - 1][i] == 1 || INFO[j - 1][i] == 6 || INFO[j - 1][i] == 4 || INFO[j - 1][i] == 0)
				{
					ch++;
				}

				if (INFO[j][i - 1] == 1 || INFO[j][i - 1] == 6 || INFO[j][i - 1] == 4 || INFO[j][i - 1] == 0)
				{
					ch++;
				}


				if (ch < 2 || ch > 3)
				{
					INFO[j][i] = 0;
					SetChar(j, i, f_cyan, '0');
					death_ch++;
				}

				ch = 0;
			}
			else
			if (GetChar(j, i) == '4')
			{
				INFO[j][i] = 0;
				SetChar(j, i, f_cyan, '0');

				//Даже если эти клетки попадут в границы мы просто отчистим после этого их обратно

					SetChar(j + 1, i, f_cyan, '0');
					INFO[j + 1][i] = 0;

					SetChar(j, i + 1, f_cyan, '0');
					INFO[j][i + 1] = 0;

					SetChar(j - 1, i, f_cyan, '0');
					INFO[j - 1][i] = 0;

					SetChar(j, i - 1, f_cyan, '0');
					INFO[j][i - 1] = 0;

					SetChar(j + 1, i + 1, f_cyan, '0');
					INFO[j + 1][i + 1] = 0;

					SetChar(j + 1, i - 1, f_cyan, '0');
					INFO[j + 1][i - 1] = 0;

					SetChar(j - 1, i + 1, f_cyan, '0');
					INFO[j - 1][i + 1] = 0;

					SetChar(j - 1, i - 1, f_cyan, '0');
					INFO[j - 1][i - 1] = 0;

				//собственно функция отчистки, которая включает и прорисовку границ
				ClearScope();
			}
		}
	}

	SetPos(38, _HEIGHT + 3);
	printf("    ");
	printf("%d", death_ch);
	death_ch = 0;
}
