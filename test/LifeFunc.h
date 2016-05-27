#ifndef _LIFEFUNC_H
#define _LIFEFUNC_H

#include "consolewrap.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <stdio.h>
#include <Windows.h>

VOID Clear(int **&INFO, int HEIGHT, int WIDTH);

VOID ClearScope(int **&INFO, int HEIGHT, int WIDTH);

VOID Ch(int **&INFO, int HEIGHT, int WIDTH);

VOID RandomFirstGen(int **&INFO, int HEIGHT, int WIDTH);

VOID Rename(int **&INFO, int HEIGHT, int WIDTH);

VOID DeathGen(int **&INFO, int HEIGHT, int WIDTH);

VOID SecondGen(int **&INFO, int HEIGHT, int WIDTH);

VOID Interface(int **&INFO, int HEIGHT, int WIDTH);

VOID CustomRename(int **&INFO, int HEIGHT, int WIDTH);

VOID CustomSecondGen(int **&INFO, int HEIGHT, int WIDTH);

VOID CustomDeathGen(int **&INFO, int HEIGHT, int WIDTH);

VOID Classic(int **&INFO, int HEIGHT, int WIDTH);

VOID Custom(int **&INFO, int HEIGHT, int WIDTH);

VOID Start(int HEIGHT, int WIDTH);

#endif