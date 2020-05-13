#pragma once
#ifndef MAP_H
#define MAP_H

#define _CTR_SECURE_NO_WARNINGS
#define _CTR_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Room {
	char roomID;
	unsigned nrofenemy;
	unsigned strofenemy;
}Room;

typedef struct Map {
	Room*** palya;
	int x;
	int y;
}Map;

Map* CreateMap(char const * file);
Room* CreateRoom(char id, unsigned i,unsigned str);
void PrintRoom(Room szoba);
void PrintMap(Map* map);
//void DestroyRoom(Room* szoba);
void DestroyMap(Map* map);
//Map* Move(Map field, char dir);
#endif// !MAP_H