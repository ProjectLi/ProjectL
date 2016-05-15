//
//  main.c
//  The game of life
//  Created by Mazurov Danil, Sabitov Evgeniy on 2.04.16.
//  Copyright © 2016 Team Unknown. All rights reserved.
//Осталось комменты наделать

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

#include "ConsoleWrap.h"

//Ch - обозначает счетчик

// _HEIGHT	25
// _WIDTH	50
// _SIZELIFE 100

//Массив данных, в котором мы будем хранить известные положения ячеек с координатами X и Y.
//Для которой 3 - пустое место, пробел
//0 - клетка подготовленная для смерти
//1 - клетка первого поколения
//2 - клетка второго поколения
//4 - клетка бессмертаня клетка
//5 - клетка самоубийца
//6 - клетка любовник



//Очистка массива, все клетки равны 3, что соответсвует пустому месту

VOID Clear(int **&INFO, int _HEIGHT, int _WIDTH)
{
	for (int i = 0; i < _HEIGHT + 1; i++)
	{
		for (int j = 0; j < _WIDTH + 1; j++)
		{
			INFO[j][i] = 3;
		}
	}
}

//Та же отчистка, но только границ, которые не выводятся на экран, чтобы значения там не мешали процессу

VOID ClearScope(int **&INFO, int _HEIGHT, int _WIDTH)
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

//===========================================================================
//Отдельно вынесенный счетчик первого поколения (красные).
VOID Ch(int **&INFO, int _HEIGHT, int _WIDTH)
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
	printf("       ");
	SetPos(40, _HEIGHT + 1);
	SetColor(f_red);
	printf("%d", ch);
}

//Первое поколение, генерируемое случайно по всему полю.
VOID RandomFirstGen(int **&INFO, int _HEIGHT, int _WIDTH)
{
	INT i, j, k;
	//Раскидывает по координатам X и Y (j и i соотв.)
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
			//Если попадаем на границу или на клетку '1', то счетчик идет на повтор
			k--;
		}
	}
}

//Название говорит само за себя, тут переименование клеток из мертвых в пустые, и из новорожденных в взрослых
VOID Rename(int **&INFO, int _HEIGHT, int _WIDTH)
{
	INT i, j, k = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
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

VOID DeathGen(int **&INFO, int _HEIGHT, int _WIDTH)
{
	INT i, j, k = 0, dth = 0, ch = 0, death_ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
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

	SetPos(38, _HEIGHT + 3);
	printf("       ");
	SetPos(40, _HEIGHT + 3);
	SetColor(f_cyan);

	printf("%d", death_ch);
}

VOID SecondGen(int **&INFO, int _HEIGHT, int _WIDTH)
{
	INT i, j, k = 0, dth = 0, ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
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
	SetPos(38, _HEIGHT + 2);
	printf("       ");
	SetPos(40, _HEIGHT + 2);
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

VOID CustomRename(int **&INFO, int _HEIGHT, int _WIDTH)
{
	INT i, j, custom;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
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

				if (custom > 0 && custom <= 10) //бессмертная клетка, шанс 0,01%
				{
					INFO[j][i] = 4;
					SetChar(j, i, b_green, ' ');
				}

				if (custom > 10 && custom <= 110) //клетка-сметрник, шанс 0,1%
				{
					INFO[j][i] = 5;
					SetChar(j, i, b_yellow, ' ');
				}

				if (custom > 110 && custom <= 210) //клетка-любовник, шанс 0,1%
				{
					INFO[j][i] = 6;
					SetChar(j, i, b_magenta, ' ');
				}
				//
			}
		}
	}
}

VOID CustomSecondGen(int **&INFO, int _HEIGHT, int _WIDTH)
{
	INT i, j, k = 0, dth = 0, ch = 0;

	for (i = 1; i < _HEIGHT; i++)
	{
		for (j = 1; j < _WIDTH; j++)
		{

			//если в радиусе есть клетка любовник, то клеткка сразу становится вторым поколением
			if (INFO[j][i - 1] == 6 || INFO[j][i + 1] == 6 || INFO[j - 1][i] == 6 || INFO[j + 1][i] == 6 ||
				INFO[j + 1][i + 1] == 6 || INFO[j + 1][i - 1] == 6 || INFO[j - 1][i + 1] == 6 || INFO[j - 1][i - 1] == 6)
			{
				INFO[j][i] = 2;
				SetChar(j, i, b_blue, ' ');
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
	SetPos(38, _HEIGHT + 2);
	printf("       ");
	SetPos(40, _HEIGHT + 2);
	printf("%d", k);
}

VOID CustomDeathGen(int **&INFO, int _HEIGHT, int _WIDTH)
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
				//Даже если эти клетки попадут в границы мы просто отчистим после этого их обратно

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

				//собственно функция отчистки, которая включает и прорисовку границ
				ClearScope();
			}
		}
	}
	SetColor(f_cyan);
	SetPos(38, _HEIGHT + 3);
	printf("    ");
	SetPos(40, _HEIGHT + 3);
	printf("%d", death_ch);
	death_ch = 0;
}

//===========================================================================

VOID Classic(int **&INFO, int _HEIGHT, int _WIDTH)
{
	Interface();
	DWORD key = 0;
	RandomFirstGen();
	Ch();

	do
	{
		key = _getch();
		SecondGen(INFO, _HEIGHT, _WIDTH);
		//key = _getch();
		DeathGen(INFO, _HEIGHT, _WIDTH);
		//key = _getch();
		Rename(INFO, _HEIGHT, _WIDTH);
		Ch(INFO, _HEIGHT, _WIDTH);
	} while (key != '0');

}

VOID Сustom(int **&INFO, int _HEIGHT, int _WIDTH)
{
	Interface();
	DWORD key = 0;
	RandomFirstGen(INFO, _HEIGHT, _WIDTH);
	Ch(INFO, _HEIGHT, _WIDTH);

	do
	{
		if ( _kbhit() ) key = _getch();
		//_getch();
		CustomSecondGen(INFO, _HEIGHT, _WIDTH);
		//_getch();
		CustomDeathGen(INFO, _HEIGHT, _WIDTH);
		//key = _getch();
		CustomRename(INFO, _HEIGHT, _WIDTH);
		Ch();
	} while (key != '0');
}

//===========================================================================

VOID Start()
{
	INT i, j, _HEIGHT = 25, _WIDTH = 50, **INFO;
	
	INFO = new * int[_HEIGHT + 1];
	
	for (i = 0; i < _HEIGHT + 1; i++)
	{
		INFO[i] = new int[_WIDTH + 1];
	}
	
	DWORD key = 0;
	
	Clear(INFO, _HEIGHT, _WIDTH);
	
	system("CLS");
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
									Classic(INFO, _HEIGHT, _WIDTH);
									Start();
						}
						case '2':
						{
									//Пользовательский
									Сustom(INFO, _HEIGHT, _WIDTH);
									Start();
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
