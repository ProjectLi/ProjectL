
//Вроде доделанная версия от Мазурова Данила ИП-512
//Осталось комменты наделать

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

#include "ConsoleWrap.c"
#include "Custom.c"

//ch - обозначает счетчик

//Массив данных, в котором мы будем хранить известные положения ячеек с координатами X и Y.
//Для которой 3 - пустое место, пробел
//0 - клетка подготовленная для смерти
//1 - клетка первого поколения
//2 - клетка второго поколения
//4 - клетка бессмертаня клетка
//5 - клетка самоубийца
//6 - клетка любовник

void clear(int **&info, int height, int width)
{
	for (int i = 0; i < height + 1; i++)
	{
		for (int j = 0; j < width + 1; j++)
		{
			info[j][i] = 3;
		}
	}
}

//Та же отчистка, но только границ, которые не выводятся на экран, чтобы значения там не мешали процессу

void clear_Scope(int **&info, int height, int width)
{
	int j, i;
	for (i = 0; i < height + 1; i++)
	{
		info[0][i] = 3;    //Левая граница по вертикали
		info[width][i] = 3;    //Правая граница по вертикали
	}


	for (j = 0; j < width + 1; j++)
	{

		info[j][0] = 3;   //Верхняя сторона по горизонтали
		info[j][height];     //Нижняя сторона по горизонтали
	}

	// Up row
	FillPos(0, 0, f_darkyellow, '#', width + 1);

	// Down row

	FillPos(0, height, f_darkyellow, '#', width + 1);
	FillPos(0, height + 6, f_darkyellow, '#', width + 1);

	// Side columns

	for (i = 1; i < height + 6; i += 1)
	{
		SetChar(0, i, f_darkyellow, '#');
		SetChar(width, i, f_darkyellow, '#');
	}
}

//===========================================================================
//Отдельно вынесенный счетчик первого поколения (красные).
void ch(int **&info, int height, int width)
{
	int i, j, k = 0, ch = 0;

	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{

			if (info[j][i] == 1)
			{
				ch++;
			}

			if (info[j][i] == 3)
			{
				SetChar(j, i, c_black, ' ');
			}
		}
	}
	//Если при отрисовке предыдущее значение было больше нынешнего, то нарисуется "поверх".
	//Это нежелательно, потому как отображаться будет неверное значение.
	SetPos(38, height + 1);
	//Потому мы указываем координаты, и затираем их, прежде чем писать наше значение.
	printf("       ");
	SetPos(40, height + 1);
	SetColor(f_red);
	printf("%d", ch);
}

//Первое поколение, генерируемое случайно по всему полю.
void classic_RandomFirstGen(int **&info, int height, int width)
{
	int i, j, k;
	//Раскидывает по координатам X и Y (j и i соотв.)
	for (k = 1; k < 101; k++)
	{
		i = rand() % 24 + 1;
		j = rand() % 49 + 1;
		if (info[j][i] != 1)
		{
			info[j][i] = 1;
			SetChar(j, i, f_red, '1');
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
void rename(int **&info, int height, int width)
{
	int i, j, k = 0;

	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{
			if (info[j][i] == 0)
			{
				info[j][i] = 3;
				SetChar(j, i, c_black, ' ');
			}
			else
			if (info[j][i] == 2)
			{
				info[j][i] = 1;
				SetChar(j, i, f_red, '1');
			}
		}
	}
}

void deathGen(int **&info, int height, int width)
{
	int i, j, k = 0, dth = 0, ch = 0, death_ch = 0;

	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{
			if (info[j][i] == 1)
			{

				if (info[j + 1][i + 1] == 1 || info[j + 1][i + 1] == 0)
				{
					ch++;
				}

				if (info[j - 1][i - 1] == 1 || info[j - 1][i - 1] == 0)
				{
					ch++;
				}

				if (info[j + 1][i - 1] == 1 || info[j + 1][i - 1] == 0)
				{
					ch++;
				}


				if (info[j - 1][i + 1] == 1 || info[j - 1][i + 1] == 0)
				{
					ch++;
				}

				//

				if (info[j + 1][i] == 1 || info[j + 1][i] == 0)
				{
					ch++;
				}

				if (info[j][i + 1] == 1 || info[j][i + 1] == 0)
				{
					ch++;
				}

				if (info[j - 1][i] == 1 || info[j - 1][i] == 0)
				{
					ch++;
				}

				if (info[j][i - 1] == 1 || info[j][i - 1] == 0)
				{
					ch++;
				}


				if (ch < 2 || ch > 3)
				{
					info[j][i] = 0;
					SetChar(j, i, c_black, ' ');
					death_ch++;
				}

				ch = 0;
			}
		}
	}

	SetPos(38, height + 3);
	printf("       ");
	SetPos(40, height + 3);
	SetColor(f_cyan);

	printf("%d", death_ch);
}

void secondGen(int **&info, int height, int width)
{
	int i, j, k = 0, dth = 0, ch = 0;

	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{
			if (info[j][i] == 3)
			{

				if (info[j + 1][i + 1] == 1)
				{
					ch++;
				}

				if (info[j - 1][i - 1] == 1)
				{
					ch++;
				}

				if (info[j + 1][i - 1] == 1)
				{
					ch++;
				}

				if (info[j - 1][i + 1] == 1)
				{
					ch++;
				}

				//

				if (info[j + 1][i] == 1)
				{
					ch++;
				}

				if (info[j][i + 1] == 1)
				{
					ch++;
				}

				if (info[j - 1][i] == 1)
				{
					ch++;
				}

				if (info[j][i - 1] == 1)
				{
					ch++;
				}


				if (ch == 3 || ch > 3)
				{
					info[j][i] = 2;
					SetChar(j, i, b_blue, '2');
					k++;
				}

				ch = 0;


			}
		}
	}


	SetColor(f_blue);
	SetPos(38, height + 2);
	printf("       ");
	SetPos(40, height + 2);
	printf("%d", k);

}

void interface(int **&info, int height, int width)
{
	SHORT i;

	// In case of changed background color
	SetChar(0, 0, c_black, ' ');
	system("cls");

	// Up row
	FillPos(0, 0, f_darkyellow, '#', width + 1);
	// Down row
	FillPos(0, height, f_darkyellow, '#', width + 1);
	FillPos(0, height + 6, f_darkyellow, '#', width + 1);
	// Side columns
	for (i = 1; i < height + 6; i += 1)
	{
		SetChar(0, i, f_darkyellow, '#');
		SetChar(width, i, f_darkyellow, '#');
	}

	WritePos(2, height + 1, f_red, "Первое поколение:                  [       ] ");
	WritePos(2, height + 2, f_blue, "Второе поколение:                  [       ] ");
	WritePos(2, height + 3, f_cyan, "Мертвые:                           [       ] ");
}

//===========================================================================

//Первое поколение, генерируемое случайно по всему полю.
void custom_RandomFirstGen(int **&info, int height, int width)
{
	int i, j, k;
	//Раскидывает по координатам X и Y (j и i соотв.)
	for (k = 1; k < 101; k++)
	{
		i = rand() % 24 + 1;
		j = rand() % 49 + 1;
		if (info[j][i] != 1)
		{
			info[j][i] = 1;
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

void custom_Rename(int **&info, int height, int width)
{
	int i, j, custom;

	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{
			if (info[j][i] == 0)
			{
				info[j][i] = 3;
				SetChar(j, i, b_black, ' ');
			}
			else
			if (info[j][i] == 2)
			{
				info[j][i] = 1;
				SetChar(j, i, b_red, ' ');

				custom = rand() % 100000 + 1;

				if (custom > 0 && custom <= 10) //бессмертная клетка, шанс 0,01%
				{
					info[j][i] = 4;
					SetChar(j, i, b_green, ' ');
				}

				if (custom > 10 && custom <= 110) //клетка-сметрник, шанс 0,1%
				{
					info[j][i] = 5;
					SetChar(j, i, b_yellow, ' ');
				}

				if (custom > 110 && custom <= 210) //клетка-любовник, шанс 0,1%
				{
					info[j][i] = 6;
					SetChar(j, i, b_magenta, ' ');
				}
				//
			}
		}
	}
}

void custom_SecondGen(int **&info, int height, int width)
{
	int i, j, k = 0, dth = 0, ch = 0;

	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{

			//если в радиусе есть клетка любовник, то клеткка сразу становится вторым поколением
			if (info[j][i - 1] == 6 || info[j][i + 1] == 6 || info[j - 1][i] == 6 || info[j + 1][i] == 6 ||
				info[j + 1][i + 1] == 6 || info[j + 1][i - 1] == 6 || info[j - 1][i + 1] == 6 || info[j - 1][i - 1] == 6)
			{
				info[j][i] = 2;
				SetChar(j, i, b_blue, ' ');
				k++;
			}
			//если нет то проверяем, может клетка итак должна была стать таковой
			else

			if (info[j][i] == 3)
			{

				if (info[j + 1][i + 1] == 1)
				{
					ch++;
				}

				if (info[j - 1][i - 1] == 1)
				{
					ch++;
				}

				if (info[j + 1][i - 1] == 1)
				{
					ch++;
				}


				if (info[j - 1][i + 1] == 1)
				{
					ch++;
				}

				//

				if (info[j + 1][i] == 1)
				{
					ch++;
				}

				if (info[j][i + 1] == 1)
				{
					ch++;
				}

				if (info[j - 1][i] == 1)
				{
					ch++;
				}

				if (info[j][i - 1] == 1)
				{
					ch++;
				}


				if (ch >= 3)
				{
					info[j][i] = 2;
					SetChar(j, i, b_blue, ' ');
					k++;
				}

				ch = 0;

			}
		}
	}
	SetColor(f_blue);
	SetPos(38, height + 2);
	printf("       ");
	SetPos(40, height + 2);
	printf("%d", k);
}

void custom_DeathGen(int **&info, int height, int width)
{
	int i, j, k = 0, dth = 0, ch = 0, death_ch = 0;

	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{
			if (info[j][i] == 1 || info[j][i] == 6)
			{

				if (info[j + 1][i + 1] == 1 || info[j + 1][i + 1] == 6 || info[j + 1][i + 1] == 4 || info[j + 1][i + 1] == 0)
				{
					ch++;
				}

				if (info[j - 1][i - 1] == 1 || info[j - 1][i - 1] == 6 || info[j - 1][i - 1] == 4 || info[j - 1][i - 1] == 0)
				{
					ch++;
				}

				if (info[j + 1][i - 1] == 1 || info[j + 1][i - 1] == 6 || info[j + 1][i - 1] == 4 || info[j + 1][i - 1] == 0)
				{
					ch++;
				}


				if (info[j - 1][i + 1] == 1 || info[j - 1][i + 1] == 6 || info[j - 1][i + 1] == 4 || info[j - 1][i + 1] == 0)
				{
					ch++;
				}

				//

				if (info[j + 1][i] == 1 || info[j + 1][i] == 6 || info[j + 1][i] == 4 || info[j + 1][i] == 0)
				{
					ch++;
				}

				if (info[j][i + 1] == 1 || info[j][i + 1] == 6 || info[j][i + 1] == 4 || info[j][i + 1] == 0)
				{
					ch++;
				}

				if (info[j - 1][i] == 1 || info[j - 1][i] == 6 || info[j - 1][i] == 4 || info[j - 1][i] == 0)
				{
					ch++;
				}

				if (info[j][i - 1] == 1 || info[j][i - 1] == 6 || info[j][i - 1] == 4 || info[j][i - 1] == 0)
				{
					ch++;
				}


				if (ch < 2 || ch > 3)
				{
					info[j][i] = 0;
					SetChar(j, i, b_cyan, ' ');
					death_ch++;
				}

				ch = 0;
			}
			else

			if (info[j][i] == 5)
			{

				SetChar(j, i, b_cyan, ' ');
				info[j][i] = 0;
				//Даже если эти клетки попадут в границы мы просто отчистим после этого их обратно

				SetChar(j + 1, i, b_cyan, ' ');
				info[j + 1][i] = 0;

				SetChar(j, i + 1, b_cyan, ' ');
				info[j][i + 1] = 0;

				SetChar(j - 1, i, b_cyan, ' ');
				info[j - 1][i] = 0;

				SetChar(j, i - 1, b_cyan, ' ');
				info[j][i - 1] = 0;

				SetChar(j + 1, i + 1, b_cyan, ' ');
				info[j + 1][i + 1] = 0;

				SetChar(j + 1, i - 1, b_cyan, ' ');
				info[j + 1][i - 1] = 0;

				SetChar(j - 1, i + 1, b_cyan, ' ');
				info[j - 1][i + 1] = 0;

				SetChar(j - 1, i - 1, b_cyan, ' ');
				info[j - 1][i - 1] = 0;

				//собственно функция отчистки, которая включает и прорисовку границ
				clear_Scope(info, height, width);
			}
		}
	}
	SetColor(f_cyan);
	SetPos(38, height + 3);
	printf("    ");
	SetPos(40, height + 3);
	printf("%d", death_ch);
	death_ch = 0;
}

//===========================================================================

void classic(int **&info, int height, int width)
{
	bool f = 0;
	interface(info, height, width);
	DWORD key = 0;
	classic_RandomFirstGen(info, height, width);
	ch(info, height, width);

	do
	{
		if (_kbhit())
		{
			key = _getch();
			f = 0;
		}
		if (key == 32 && f == 0)
		{
			key = _getch();
			f = 1;
		}
		else
		{
			secondGen(info, height, width);
			deathGen(info, height, width);
			rename(info, height, width);
			ch(info, height, width);
		}
	} while (key != '0' && key != 27);

}

void custom(int **&info, int height, int width)
{
	bool f = 0;
	interface(info, height, width);
	DWORD key = 0;
	custom_RandomFirstGen(info, height, width);
	ch(info, height, width);

	do
	{
		if (_kbhit())
		{
			key = _getch();
			f = 0;
		}
		if (key == 32 && f == 0)
		{
			key = _getch();
			f = 1;
		}
		else
		{
			custom_SecondGen(info, height, width);
			custom_DeathGen(info, height, width);
			custom_Rename(info, height, width);
			ch(info, height, width);
		}
	} while (key != '0' && key != 27);
}

//===========================================================================

void start(int height, int width)
{
	int i, j, **info;

	info = new int*[width + 1];

	for (i = 0; i < width + 1; i++)
	{
		info[i] = new int[height + 1];
	}

	DWORD key = 0;

	clear(info, height, width);

	system("CLS");
	for (i = 0; i <= height + 7; i++)
	{
		for (j = 0; j <= width; j++)
		{
			SetChar(j, 0, f_yellow | b_yellow, ' ');
		}
		SetChar(0, i, f_yellow | b_yellow, ' ');
		SetChar(width, i, f_yellow | b_yellow, ' ');
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
									classic(info, height, width);
									start(25, 50);
						}
						case '2':
						{
									//Пользовательский
									custom(info, height, width);
									start(25, 50);
						}
						}
					} while (TRUE);
		}
		case '2': exit(0);
		}
	} while (TRUE);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	int height = 25, width = 50;

	if (InitConsole("LifeTime", width + 1, height + 7, b_black & f_white))
	{
		start(25, 50);
	}

	return 0;
}