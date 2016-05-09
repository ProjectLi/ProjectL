//Вроде доделанная версия от Мазурова Данила ИП-512
//Осталось комменты наделать

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

#include "ConsoleWrap.h"

//Ch - обозначает счетчик

#define _HEIGHT	25
#define _WIDTH	50
#define _SIZELIFE 100

//Массив данных, в котором мы будем хранить известные положения ячеек с координатами X и Y.
//Для которой 3 - пустое место, пробел
//0 - клетка подготовленная для смерти
//1 - клетка первого поколения
//2 - клетка второго поколения
//4 - клетка бессмертаня клетка
//5 - клетка самоубийца
//6 - клетка любовник

int INFO[_WIDTH + 1][_HEIGHT + 1];

//===========================================================================
//Отдельно вынесенный счетчик первого поколения (красные).
VOID Ch()
{
	INT i, j, k = 0, ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{

			if (A[j][i] == 1)
			{
				ch++;
			}
			if (A[j][i] == 3)
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
//Первое поколение, генерируемое случайно по всему полю.
//Не гарантирую, что они смогут выжить ^_^
VOID RandomFirstGen()
{
	INT i, j, k;
	//Раскидывает по координатам X и Y (j и i соотв.)
	for (k = 1; k < _SIZELIFE + 1; k++)
	{
		i = rand() % 24 + 1;
		j = rand() % 49 + 1;
		if (GetChar(i, j) != '1' && GetChar(i, j) != '#')
		{
			SetChar(j, i, f_red, '1');
			SetPos(42, _HEIGHT + 1);
		}
		else
		{
			//Если попадаем на границу или на клетку '1', то счетчик идет на повтор
			k--;
		}
	}
}

//Название говорит само за себя, тут переименование клеток из мертвых в пустые, и из новорожденных в взрослых
VOID Rename()
{
	INT i, j;

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
	INT i, j, k = 0, dth = 0, ch = 0, death_ch = 0;

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
					death_ch++;
				}

				ch = 0;
			}
		}
	}

	SetPos(38, _HEIGHT + 3);
	printf("    ");
	printf("%d", death_ch);
	death_ch = 0;
}

VOID SecondGen()
{
	INT i, j, k = 0, dth = 0, ch = 0;

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

//===========================================================================

VOID CustomRename()
{
	INT i, j, custom;

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
				custom = rand() % 100000 + 1;
				if (custom > 0 && custom <= 10) //бессмертная клетка, шанс 0,01%
				{
					SetChar(j, i, f_green, '3');
				}
				else
				if (custom > 10 && custom <= 110) //клетка-сметрник, шанс 0,1%
				{
					SetChar(j, i, f_yellow, '4');
				}
				else
				if (custom > 110 && custom <= 210) //клетка-любовник, шанс 0,1%
				{
					SetChar(j, i, f_magenta, '5');
				}
				else
				{
					SetChar(j, i, f_red, '1');
				}
			}
		}
	}
}

VOID CustomSecondGen()
{
	INT i, j, k = 0, dth = 0, ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{

			if (GetChar(j, i - 1) == '5' || GetChar(j, i + 1) == '5' || GetChar(j - 1, i) == '5' || GetChar(j + 1, i) == '5' ||
				GetChar(j + 1, i + 1) == '5' || GetChar(j + 1, i - 1) == '5' || GetChar(j - 1, i + 1) == '5' || GetChar(j - 1, i - 1) == '5')
			{
				SetChar(j, i, f_blue, '2');
				k++;
			}

			if (GetChar(j, i) == ' ')
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
					k++;
				}

				ch = 0;

			}
		}
	}

	SetPos(42, _HEIGHT + 2);
	printf("%d", k);
}

VOID CustomDeathGen()
{
	INT i, j, k = 0, dth = 0, ch = 0, death_ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{
			if (GetChar(j, i) == '1' || GetChar(j, i) == '5')
			{

				if (GetChar(j + 1, i + 1) == '1' || GetChar(j + 1, i + 1) == '5' || GetChar(j + 1, i + 1) == '3' || GetChar(j + 1, i + 1) == '0')
				{
					ch++;
				}

				if (GetChar(j - 1, i - 1) == '1' || GetChar(j - 1, i - 1) == '5' || GetChar(j - 1, i - 1) == '3' || GetChar(j - 1, i - 1) == '0')
				{
					ch++;
				}

				if (GetChar(j + 1, i - 1) == '1' || GetChar(j + 1, i - 1) == '5' || GetChar(j + 1, i - 1) == '3' || GetChar(j + 1, i - 1) == '0')
				{
					ch++;
				}


				if (GetChar(j - 1, i + 1) == '1' || GetChar(j - 1, i + 1) == '5' || GetChar(j - 1, i + 1) == '3' || GetChar(j - 1, i + 1) == '0')
				{
					ch++;
				}

				//

				if (GetChar(j + 1, i) == '1' || GetChar(j + 1, i) == '5' || GetChar(j + 1, i) == '3' || GetChar(j + 1, i) == '0')
				{
					ch++;
				}

				if (GetChar(j, i + 1) == '1' || GetChar(j, i + 1) == '5' || GetChar(j, i + 1) == '3' || GetChar(j, i + 1) == '0')
				{
					ch++;
				}

				if (GetChar(j - 1, i) == '1' || GetChar(j - 1, i) == '5' || GetChar(j - 1, i) == '3' || GetChar(j - 1, i) == '0')
				{
					ch++;
				}

				if (GetChar(j, i - 1) == '1' || GetChar(j, i - 1) == '5' || GetChar(j, i - 1) == '3' || GetChar(j, i - 1) == '0')
				{
					ch++;
				}


				if (ch < 2 || ch > 3)
				{
					SetChar(j, i, f_cyan, '0');
					death_ch++;
				}

				ch = 0;
			}
			else
			if (GetChar(j, i) == '4')
			{
				SetChar(j, i, f_cyan, '0');

				if (GetChar(j + 1, i) != '#')
				{
					SetChar(j + 1, i, f_cyan, '0');
				}

				if (GetChar(j, i + 1) != '#')
				{
					SetChar(j, i + 1, f_cyan, '0');
				}

				if (GetChar(j - 1, i) != '#')
				{
					SetChar(j - 1, i, f_cyan, '0');
				}

				if (GetChar(j, i - 1) != '#')
				{
					SetChar(j, i - 1, f_cyan, '0');
				}

				if (GetChar(j + 1, i + 1) != '#')
				{
					SetChar(j + 1, i + 1, f_cyan, '0');
				}

				if (GetChar(j + 1, i - 1) != '#')
				{
					SetChar(j + 1, i - 1, f_cyan, '0');
				}

				if (GetChar(j - 1, i + 1) != '#')
				{
					SetChar(j - 1, i + 1, f_cyan, '0');
				}

				if (GetChar(j - 1, i - 1) != '#')
				{
					SetChar(j - 1, i - 1, f_cyan, '0');
				}
			}
		}
	}

	SetPos(38, _HEIGHT + 3);
	printf("    ");
	printf("%d", death_ch);
	death_ch = 0;
}

//===========================================================================

VOID Classic()
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

VOID Сustom()
{
	Interface();

	RandomFirstGen();
	Ch();

	for (;;)
	{
		//_getch();
		CustomSecondGen();
		//_getch();
		CustomDeathGen();
		//_getch();
		CustomRename();
		Ch();
	}
}

//===========================================================================

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


	WritePos(15, 13, f_red, "1.  Старт");
	WritePos(15, 15, f_red, "2.  Выход");

	do{
	if (_kbhit()) key = _getch();
	switch (key)
	{
		case '1':
		{
			key = 0;

			WritePos(15, 13, f_red, "                      ");
			WritePos(15, 13, f_red, "1.  Классический режим");
			WritePos(15, 15, f_red, "                            ");
			WritePos(15, 15, f_red, "2.  Режим с доп. настройками");

			do{
			if (_kbhit()) key = _getch();
			switch (key)
			{
				case '1':
				{
					//Стандартный, классический
					Classic();
				}
				case '2':
				{
					//Пользовательский
					Сustom();
				}
			}
			} while (TRUE);
		}
		case '2': exit(0);
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
