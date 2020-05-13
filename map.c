#define _CTR_SECURE_NO_WARNINGS
#define _CTR_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable : 4996).

#include "map.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

Room* CreateRoom(char id, unsigned nr1, unsigned nr2)
{
	Room* uj;
	uj->roomID = id;
	uj->nrofenemy = nr1;
	uj->strofenemy = nr2;
	return uj;
}
Map* CreateMap(char const* file)
{
	FILE* fin = fopen(file, "r");
	if (!fin)
	{
		printf("HIBA! Nem lehet megnyitni az allomanyt");
		return NULL;
	}
	Map* m = (Map*)malloc(1 * sizeof(Map));
	fscanf(fin, "%i %i", &m->x, &m->y);
	Room** palya = (Room**)malloc(m->x * sizeof(Room*));
	if (palya == NULL)
	{
		printf("Helyfoglalas nem sikerult.\n");
		return NULL;
	}
	for (int i = 0; i < m->x; i++)
	{
		palya[i] = (Room*)malloc(m->y * sizeof(Room));
		if (palya[i] == NULL)
		{
			printf("Helyfoglalas nem sikerult.\n");
			return NULL;
		}
	}
	srand(time(0));
	char id;
	for (int i = 0; i < m->x; i++)
	{
		for (int j = 0; i < m->y; j++)
		{
			fscanf(fin, "%c", &id);
			palya[i][j] = CreateRoom(id,rand()%3,(rand()%3)+1);
		}
	}
	m->palya = palya;
	fclose(fin);
	return m;
}
void PrintRoom(Room szoba)
{
	printf("Ebben a szobaban %i ellenseg van, ezek fejenkent %i. erosek.\n",szoba.nrofenemy,szoba.strofenemy);
}

void PrintMap(Map* map)
{
	if (map != NULL) 
	{
		for (int i = 0; i < map->x; i++)
		{
			for (int j = 0; j < map->y; j++)
			{
				switch (map->palya[i][j]->roomID)
				{
				case '0': printf(" "); break;
				case '1': printf("B"); break;
				case '3': printf("E"); break;
				case 'R': printf("X"); break;
				}

			}
			printf("\n");
		}
	}
}
void DestroyMap(Map* m)
{
	for (int i = 0; i < m->x; i++)
	{
		for (int j = 0; i < m->y; j++)
		{
			free(m->palya[i][j]);
		}
	}
	for (int i = 0; i < m->x; i++)
	{
		free(m->palya[i]);
	}
	free(m->palya);
	free(m);
	printf("A palya fel lett szabaditva.\n");
}