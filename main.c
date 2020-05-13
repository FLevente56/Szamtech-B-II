#define _CTR_SECURE_NO_WARNINGS
#define _CTR_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#include "map.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int main()
{
	Map* M = CreateMap("palya1.txt");
	PrintMap(M);
	DestroyMap(M);
	return 0;
}