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
	//���� ��� ��������� ���������� �������� ���� ������ ���������, �� ���������� "������".
	//��� ������������, ������ ��� ������������ ����� �������� ��������.
	SetPos(38, _HEIGHT + 1);
	//������ �� ��������� ����������, � �������� ��, ������ ��� ������ ���� ��������.
	printf("    ");
	SetColor(f_red);
	printf("%d", ch);
}
