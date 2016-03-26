#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

#include "ConsoleWrap.h"

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

VOID Ch()
{
	INT i, j, k = 0, ch = 0;

	for (i = 1; i < _HEIGHT - 1; i++)
	{
		for (j = 1; j < _WIDTH - 1; j++)
		{

			if (GetChar(j, i) == '1')
			{
				ch++;
			}
		}
	}
	SetPos(42, _HEIGHT + 1);
	SetColor(f_red);
	printf("%d", ch);
}

VOID Rename()
{
	INT i, j, k = 0, ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{
			if (GetChar(j, i) == '0')
			{
				SetChar(j, i, c_black, ' ');
			}
			else
				if (GetChar(j, i) == '2')
				{
					SetChar(j, i, f_red, '1');
				}
		}
	}
}

VOID DeathGen()
{
	INT i, j, k = 0, ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{
			if (GetChar(j, i) == '1')
			{

				if (GetChar(j + 1, i + 1) == '1' || GetChar(j + 1, i + 1) == '0')
				{
					ch++;
				}

				if (GetChar(j - 1, i - 1) == '1' || GetChar(j - 1, i - 1) == '0')
				{
					ch++;
				}

				if (GetChar(j + 1, i - 1) == '1' || GetChar(j + 1, i - 1) == '0')
				{
					ch++;
				}


				if (GetChar(j - 1, i + 1) == '1' || GetChar(j - 1, i + 1) == '0')
				{
					ch++;
				}

				//

				if (GetChar(j + 1, i) == '1' || GetChar(j + 1, i) == '0')
				{
					ch++;
				}

				if (GetChar(j, i + 1) == '1' || GetChar(j, i + 1) == '0')
				{
					ch++;
				}

				if (GetChar(j - 1, i) == '1' || GetChar(j - 1, i) == '0')
				{
					ch++;
				}

				if (GetChar(j, i - 1) == '1' || GetChar(j, i - 1) == '0')
				{
					ch++;
				}


				if (ch < 2 || ch > 3)
				{
					SetChar(j, i, f_cyan, '0');
				}

				ch = 0;
			}
		}
	}
}

VOID SecondGen()
{
	INT i, j, k = 0, ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{
			if (GetChar(j, i) != '1' && GetChar(j, i) == ' ')
			{

				if (GetChar(j + 1, i + 1) == '1')
				{
					ch++;
				}

				if (GetChar(j - 1, i - 1) == '1')
				{
					ch++;
				}

				if (GetChar(j + 1, i - 1) == '1')
				{
					ch++;
				}


				if (GetChar(j - 1, i + 1) == '1')
				{
					ch++;
				}

				//

				if (GetChar(j + 1, i) == '1')
				{
					ch++;
				}

				if (GetChar(j, i + 1) == '1')
				{
					ch++;
				}

				if (GetChar(j - 1, i) == '1')
				{
					ch++;
				}

				if (GetChar(j, i - 1) == '1')
				{
					ch++;
				}


				if (ch == 3 || ch > 3)
				{
					SetChar(j, i, f_blue, '2');
				}

				ch = 0;

				if (GetChar(j, i) == '2')
				{
					k++;
				}
			}
		}
	}

	SetPos(42, _HEIGHT + 2);
	printf("%d", k);
}

VOID RandomFirstGen()
{
	INT i, j, k;

	for (k = 1; k < _SIZELIFE + 1; k++)
	{
		i = rand() % 24 + 1;
		j = rand() % 49 + 1;
		if (GetChar(i, j) != '1')
		{
			SetChar(j, i, f_red, '1');
			SetPos(42, _HEIGHT + 1);
		}
		else
		{
			k--;
		}
	}
}

VOID Interface()
{
	SHORT i;

	// In case of changed background color
	SetChar(0, 0, c_black, ' ');
	system("cls");

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

	WritePos(2, _HEIGHT + 1, f_red, "Первое поколение:                  [       ] ");
	WritePos(2, _HEIGHT + 2, f_blue, "Второе поколение:                  [       ] ");
	WritePos(2, _HEIGHT + 3, f_cyan, "Мертвые:                           [       ] ");


}

VOID Start()
{
	INT i, j;
	DWORD key = 0;

	for (i = 0; i <= _HEIGHT + 7; i++)
	{
		for (j = 0; j <= _WIDTH; j++)
		{
			SetChar(j, 0, f_yellow | b_yellow, ' ');
		}
		SetChar(0, i, f_yellow | b_yellow, ' ');
		SetChar(_WIDTH, i, f_yellow | b_yellow, ' ');
	}


	WritePos(15, 15, f_red, "1.  Старт");
	WritePos(15, 17, f_red, "2.  Настройки");
	WritePos(15, 19, f_red, "3.  Сменить цветовую схему");
	WritePos(15, 21, f_red, "4.  Выход");

	do{
	if (_kbhit()) key = _getch();
	switch (key)
	{
		case '1':
		{
			Interface();

			RandomFirstGen();
			Ch();

			for (;;)
			{
				_getch();
				SecondGen();
				_getch();
				DeathGen();
				_getch();
				Rename();
				Ch();
			}
		}
		case '2':
		case '3':
		case '4': exit(0);
	}
	} while (TRUE);
}

INT main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	if (InitConsole("LifeTime", _WIDTH + 1, _HEIGHT + 7, b_black & f_white))
	{
		Start();
	}
	else
	{
		system("mode con lines=40 cols=120");
		ErrMessage("Unable to initialize console");
		Write(f_yellow, ConsoleDisplayInfo());
		Write(f_yellow, ConsoleDisplayInfoEx());
		system("@pause > nul");
	}

	_getch();

	return 0;
}
