#pragma once
#ifndef MAP_H
#define MAP_H

#define _CTR_SECURE_NO_WARNINGS
#define _CTR_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN

#include "basic.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Map {
	char* palya;
	int x;
	int y;
	int poz;
	int cel;
	bool mozg;
}Map;

Map* CreateMap(char const * file);
char* readMap(FILE* fin, int x, int y);
int returnx(Map* m);
int returny(Map* m);
void PrintRoom(char* szoba);
void PrintMap(Map* map);
void DestroyMap(Map* map);
Map* valasztmap();
int poz(Map* map);
int cel(Map* map);
Map* move(Map* map,char d);
#endif// !MAP_H