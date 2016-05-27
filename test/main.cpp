#include "consolewrap.h"
#include "LifeFunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <stdio.h>
#include <Windows.h>

INT main()
{
	srand(time(NULL));
	int HEIGHT = 25, WIDTH = 50;
	if (InitConsole("LifeTime", WIDTH + 1, HEIGHT + 7, b_black & f_white))
	{
		Start(25, 50);
	}
	else
	{
		system("mode con lines=40 cols=120");
		ErrMessage("Unable to initialize console");
		Write(f_yellow, ConsoleDisplayInfo());
		Write(f_yellow, ConsoleDisplayInfoEx());
		system("@pause > nul");
	}

	//_getch();

	return 0;
}
