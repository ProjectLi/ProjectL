#include <stdio.h>
#include "ConsoleWrap.h"
#include "FUNC.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

extern int INFO[_WIDTH + 1][_HEIGHT + 1];

VOID RandomFirstGen()
{
	INT i, j, k;
	//����������� �� ����������� X � Y (j � i �����.)
	for (k = 1; k < _SIZELIFE + 1; k++)
	{
		i = rand() % 24 + 1;
		j = rand() % 49 + 1;
		if (INFO[j][i] != 1)
		{
			INFO[j][i] = 1;
			SetChar(j, i, f_red, '1');
			SetPos(0, 0);
		}
		else
		{
			//���� �������� �� ������� ��� �� ������ '1', �� ������� ���� �� ������
			k--;
		}
	}
}
