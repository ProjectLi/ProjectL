#include "LifeFunc.h"
#include "consolewrap.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <Windows.h>


VOID Clear(int **&INFO, int HEIGHT, int WIDTH)
{
	for (int i = 0; i < HEIGHT + 1; i++)
	{
		for (int j = 0; j < WIDTH + 1; j++)
		{
			INFO[j][i] = 3;
		}
	}
}

//�� �� ��������, �� ������ ������, ������� �� ��������� �� �����, ����� �������� ��� �� ������ ��������

VOID ClearScope(int **&INFO, int HEIGHT, int WIDTH)
{
	int j, i;
	for (i = 0; i < HEIGHT + 1; i++)
	{
		INFO[0][i] = 3;    //����� ������� �� ���������
		INFO[WIDTH][i] = 3;    //������ ������� �� ���������
	}


	for (j = 0; j < WIDTH + 1; j++)
	{

		INFO[j][0] = 3;   //������� ������� �� �����������
		INFO[j][HEIGHT];     //������ ������� �� �����������
	}

	// Up row
	FillPos(0, 0, f_darkyellow, '#', WIDTH + 1);

	// Down row

	FillPos(0, HEIGHT, f_darkyellow, '#', WIDTH + 1);
	FillPos(0, HEIGHT + 6, f_darkyellow, '#', WIDTH + 1);

	// Side columns

	for (i = 1; i < HEIGHT + 6; i += 1)
	{
		SetChar(0, i, f_darkyellow, '#');
		SetChar(WIDTH, i, f_darkyellow, '#');
	}
}

//===========================================================================
//�������� ���������� ������� ������� ��������� (�������).
VOID Ch(int **&INFO, int HEIGHT, int WIDTH)
{
	INT i, j, k = 0, ch = 0;

	for (i = 1; i < HEIGHT; i++)
	{
		for (j = 1; j < WIDTH; j++)
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
	SetPos(38, HEIGHT + 1);
	//������ �� ��������� ����������, � �������� ��, ������ ��� ������ ���� ��������.
	printf("       ");
	SetPos(40, HEIGHT + 1);
	SetColor(f_red);
	printf("%d", ch);
}

//������ ���������, ������������ �������� �� ����� ����.
VOID RandomFirstGen(int **&INFO, int HEIGHT, int WIDTH)
{
	INT i, j, k;
	//����������� �� ����������� X � Y (j � i �����.)
	for (k = 1; k < 101; k++)
	{
		i = rand() % 24 + 1;
		j = rand() % 49 + 1;
		if (INFO[j][i] != 1)
		{
			INFO[j][i] = 1;
			SetChar(j, i, b_red, ' ');
			SetPos(0, 0);
		}
		else
		{
			//���� �������� �� ������� ��� �� ������ '1', �� ������� ���� �� ������
			k--;
		}
	}
}

//�������� ������� ���� �� ����, ��� �������������� ������ �� ������� � ������, � �� ������������� � ��������
VOID Rename(int **&INFO, int HEIGHT, int WIDTH)
{
	INT i, j, k = 0;

	for (i = 1; i < HEIGHT; i++)
	{
		for (j = 1; j < WIDTH; j++)
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

VOID DeathGen(int **&INFO, int HEIGHT, int WIDTH)
{
	INT i, j, k = 0, dth = 0, ch = 0, death_ch = 0;

	for (i = 1; i < HEIGHT; i++)
	{
		for (j = 1; j < WIDTH; j++)
		{
			if (INFO[j][i] == 1)
			{

				if (INFO[j + 1][i + 1] == 1 || INFO[j + 1][i + 1] == 0)
				{
					ch++;
				}

				if (INFO[j - 1][i - 1] == 1 || INFO[j - 1][i - 1] == 0)
				{
					ch++;
				}

				if (INFO[j + 1][i - 1] == 1 || INFO[j + 1][i - 1] == 0)
				{
					ch++;
				}


				if (INFO[j - 1][i + 1] == 1 || INFO[j - 1][i + 1] == 0)
				{
					ch++;
				}

				//

				if (INFO[j + 1][i] == 1 || INFO[j + 1][i] == 0)
				{
					ch++;
				}

				if (INFO[j][i + 1] == 1 || INFO[j][i + 1] == 0)
				{
					ch++;
				}

				if (INFO[j - 1][i] == 1 || INFO[j - 1][i] == 0)
				{
					ch++;
				}

				if (INFO[j][i - 1] == 1 || INFO[j][i - 1] == 0)
				{
					ch++;
				}


				if (ch < 2 || ch > 3)
				{
					INFO[j][i] = 0;
					SetChar(j, i, c_black, ' ');
					death_ch++;
				}

				ch = 0;
			}
		}
	}

	SetPos(38, HEIGHT + 3);
	printf("       ");
	SetPos(40, HEIGHT + 3);
	SetColor(f_cyan);

	printf("%d", death_ch);
}

VOID SecondGen(int **&INFO, int HEIGHT, int WIDTH)
{
	INT i, j, k = 0, dth = 0, ch = 0;

	for (i = 1; i < HEIGHT; i++)
	{
		for (j = 1; j < WIDTH; j++)
		{
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
					SetChar(j, i, b_blue, '2');
					k++;
				}

				ch = 0;


			}
		}
	}


	SetColor(f_blue);
	SetPos(38, HEIGHT + 2);
	printf("       ");
	SetPos(40, HEIGHT + 2);
	printf("%d", k);

}

VOID Interface(int **&INFO, int HEIGHT, int WIDTH)
{
	SHORT i;

	// In case of changed background color
	SetChar(0, 0, c_black, ' ');
	system("cls");

	// Up row
	FillPos(0, 0, f_darkyellow, '#', WIDTH + 1);
	// Down row
	FillPos(0, HEIGHT, f_darkyellow, '#', WIDTH + 1);
	FillPos(0, HEIGHT + 6, f_darkyellow, '#', WIDTH + 1);
	// Side columns
	for (i = 1; i < HEIGHT + 6; i += 1)
	{
		SetChar(0, i, f_darkyellow, '#');
		SetChar(WIDTH, i, f_darkyellow, '#');
	}

	WritePos(2, HEIGHT + 1, f_red, "First Generation:                  [       ] ");
	WritePos(2, HEIGHT + 2, f_blue, "Second Generation:                  [       ] ");
	WritePos(2, HEIGHT + 3, f_cyan, "Dead:                           [       ] ");
}

//===========================================================================

VOID CustomRename(int **&INFO, int HEIGHT, int WIDTH)
{
	INT i, j, custom;

	for (i = 1; i < HEIGHT; i++)
	{
		for (j = 1; j < WIDTH; j++)
		{
			if (INFO[j][i] == 0)
			{
				INFO[j][i] = 3;
				SetChar(j, i, b_black, ' ');
			}
			else
			if (INFO[j][i] == 2)
			{
				INFO[j][i] = 1;
				SetChar(j, i, b_red, ' ');

				custom = rand() % 100000 + 1;

				if (custom > 0 && custom <= 10) //����������� ������, ���� 0,01%
				{
					INFO[j][i] = 4;
					SetChar(j, i, b_green, ' ');
				}

				if (custom > 10 && custom <= 110) //������-��������, ���� 0,1%
				{
					INFO[j][i] = 5;
					SetChar(j, i, b_yellow, ' ');
				}

				if (custom > 110 && custom <= 210) //������-��������, ���� 0,1%
				{
					INFO[j][i] = 6;
					SetChar(j, i, b_magenta, ' ');
				}
				//
			}
		}
	}
}

VOID CustomSecondGen(int **&INFO, int HEIGHT, int WIDTH)
{
	INT i, j, k = 0, dth = 0, ch = 0;

	for (i = 1; i < HEIGHT; i++)
	{
		for (j = 1; j < WIDTH; j++)
		{

			//���� � ������� ���� ������ ��������, �� ������� ����� ���������� ������ ����������
			if (INFO[j][i - 1] == 6 || INFO[j][i + 1] == 6 || INFO[j - 1][i] == 6 || INFO[j + 1][i] == 6 ||
				INFO[j + 1][i + 1] == 6 || INFO[j + 1][i - 1] == 6 || INFO[j - 1][i + 1] == 6 || INFO[j - 1][i - 1] == 6)
			{
				INFO[j][i] = 2;
				SetChar(j, i, b_blue, ' ');
				k++;
			}
			//���� ��� �� ���������, ����� ������ ���� ������ ���� ����� �������
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


				if ( ch >= 3)
				{
					INFO[j][i] = 2;
					SetChar(j, i, b_blue, ' ');
					k++;
				}

				ch = 0;

			}
		}
	}
	SetColor(f_blue);
	SetPos(38, HEIGHT + 2);
	printf("       ");
	SetPos(40, HEIGHT + 2);
	printf("%d", k);
}

VOID CustomDeathGen(int **&INFO, int HEIGHT, int WIDTH)
{
	INT i, j, k = 0, dth = 0, ch = 0, death_ch = 0;

	for (i = 1; i < HEIGHT; i++)
	{
		for (j = 1; j < WIDTH; j++)
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
					SetChar(j, i, b_cyan, ' ');
					death_ch++;
				}

				ch = 0;
			}
			else

			if (INFO[j] [i] == 5)
			{
				
				SetChar(j, i, b_cyan, ' ');
				INFO[j][i] = 0;
				//���� ���� ��� ������ ������� � ������� �� ������ �������� ����� ����� �� �������

				SetChar(j + 1, i, b_cyan, ' ');
				INFO[j + 1][i] = 0;

				SetChar(j, i + 1, b_cyan, ' ');
				INFO[j][i + 1] = 0;

				SetChar(j - 1, i, b_cyan, ' ');
				INFO[j - 1][i] = 0;

				SetChar(j, i - 1, b_cyan, ' ');
				INFO[j][i - 1] = 0;

				SetChar(j + 1, i + 1, b_cyan, ' ');
				INFO[j + 1][i + 1] = 0;

				SetChar(j + 1, i - 1, b_cyan, ' ');
				INFO[j + 1][i - 1] = 0;

				SetChar(j - 1, i + 1, b_cyan, ' ');
				INFO[j - 1][i + 1] = 0;

				SetChar(j - 1, i - 1, b_cyan, ' ');
				INFO[j - 1][i - 1] = 0;

				//���������� ������� ��������, ������� �������� � ���������� ������
				ClearScope(INFO, HEIGHT, WIDTH);
			}
		}
	}
	SetColor(f_cyan);
	SetPos(38, HEIGHT + 3);
	printf("    ");
	SetPos(40, HEIGHT + 3);
	printf("%d", death_ch);
	death_ch = 0;
}

//===========================================================================

VOID Classic(int **&INFO, int HEIGHT, int WIDTH)
{
	Interface(INFO, HEIGHT, WIDTH);
	DWORD key = 0;
	RandomFirstGen(INFO, HEIGHT, WIDTH);
	Ch(INFO, HEIGHT, WIDTH);

	do
	{
		if ( _kbhit() ) key = _getch();
		if (key == 32) key = _getch();
		else
		{
			SecondGen(INFO, HEIGHT, WIDTH);
			DeathGen(INFO, HEIGHT, WIDTH);
			Rename(INFO, HEIGHT, WIDTH);
			Ch(INFO, HEIGHT, WIDTH);
		}

	} while (key != '0');

}

VOID Custom(int **&INFO, int HEIGHT, int WIDTH)
{
	Interface(INFO, HEIGHT, WIDTH);
	DWORD key = 0;
	RandomFirstGen(INFO, HEIGHT, WIDTH);
	Ch(INFO, HEIGHT, WIDTH);

	do
	{
		if ( _kbhit() ) key = _getch();
		if (key == 32) key = _getch();
		else
		{
			CustomSecondGen(INFO, HEIGHT, WIDTH);
			CustomDeathGen(INFO, HEIGHT, WIDTH);
			CustomRename(INFO, HEIGHT, WIDTH);
			Ch(INFO, HEIGHT, WIDTH);
		}
	} while (key != '0');
}

//===========================================================================

VOID Start(int HEIGHT, int WIDTH)
{
	INT i, j, **INFO;
	
	INFO = new int*[WIDTH + 1];
	
	for (i = 0; i < WIDTH + 1; i++)
	{
		INFO[i] = new int[HEIGHT + 1];
	}
	
	DWORD key = 0;
	
	Clear(INFO, HEIGHT, WIDTH);
	
	system("CLS");
	for (i = 0; i <= HEIGHT + 7; i++)
	{
		for (j = 0; j <= WIDTH; j++)
		{
			SetChar(j, 0, f_yellow | b_yellow, ' ');
		}
		SetChar(0, i, f_yellow | b_yellow, ' ');
		SetChar(WIDTH, i, f_yellow | b_yellow, ' ');
	}


	WritePos(15, 13, f_red, "1.  Start");
	WritePos(15, 15, f_red, "2.  Exit");

	do{
		if (_kbhit()) key = _getch();
		switch (key)
		{
		case '1':
		{
					key = 0;

					WritePos(15, 13, f_red, "                      ");
					WritePos(15, 13, f_red, "1.  Classic");
					WritePos(15, 15, f_red, "                            ");
					WritePos(15, 15, f_red, "2.  Custom");

					do{
						if (_kbhit()) key = _getch();
						switch (key)
						{
						case '1':
						{
									//�����������, ������������
									Classic(INFO, HEIGHT, WIDTH);
									Start(25,50);
						}
						case '2':
						{
									//����������������
									Custom(INFO, HEIGHT, WIDTH);
									Start(25,50);
						}
						}
					} while (TRUE);
		}
		case '2': exit(0);
		}
	} while (TRUE);
}
