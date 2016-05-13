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
#include "FUNC.h"

/*
//Очистка массива, все клетки равны 3, что соответсвует пустому месту
#include "funcclear.h"
//Та же отчистка, но только границ, которые не выводятся на экран, чтобы значения там не мешали процессу
#include "funcClearScope.h"
//Отдельно вынесенный счетчик первого поколения (красные).
#include "funcCh.h"
//Первое поколение, генерируемое случайно по всему полю.
//Не гарантирую, что они смогут выжить ^_^
#include "funcRandomFirstGen.h"
//Название говорит само за себя, тут переименование клеток из мертвых в пустые, и из новорожденных в взрослых
#include "funcRename.h"
#include "funcDeathGen.h"
#include "funcSecondGen.h"
#include "funcInterface.h"
#include "funcCustomRename.h"
#include "funcCustomSecondGen.h"
#include "funcCustomDeathGen.h"
#include "funcClassic.h"
#include "funcCustom.h"
#include "funcStart.h"
*/
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

//Очистка массива, все клетки равны 3, что соответсвует пустому месту

//Та же отчистка, но только границ, которые не выводятся на экран, чтобы значения там не мешали процессу

//===========================================================================
//Отдельно вынесенный счетчик первого поколения (красные).

//Первое поколение, генерируемое случайно по всему полю.
//Не гарантирую, что они смогут выжить ^_^

//Название говорит само за себя, тут переименование клеток из мертвых в пустые, и из новорожденных в взрослых


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
