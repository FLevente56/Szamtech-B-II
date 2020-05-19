#define _CTR_SECURE_NO_WARNINGS
#define _CTR_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable : 4996)

#include "basic.h"
#include "map.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


Map* valasztmap() //palyavalasztas
{
	int a = 0;
	bool done=false;
	Map* M = NULL;
	do
	{
		printf("Valassz playat: 1-Kicsi 2-Kozepes 3-Nagy :\n");
		scanf("%i", &a);
		switch (a)
		{
		case 1:
			M = CreateMap("palya2.txt");
			done = true;
			break;
		case 2:
			M = CreateMap("palya1.txt");
			done = true;
			break;
		case 3:
			M = CreateMap("palya3.txt");
			done = true;
			break;
		default:
			printf("Sikertelen playavalasztas!\n");
			break;
		}
	} while (!done);
	M->poz = poz(M);
M->cel = cel(M);
	return M;
}
Map* CreateMap(char const* file) //palya helyfoglalas stb
{
	printf("A palya keszul:\n");
	FILE* fin = fopen(file, "r");
	if (!fin)
	{
		printf("HIBA! Nem lehet megnyitni az allomanyt");
		return NULL;
	}
	Map* m = (Map*)malloc(1 * sizeof(Map));
	if (m == NULL)
	{
		printf("Helyfoglalas nem sikerult.\n");
		return NULL;
	}
	fscanf(fin, "%d %d\n", &m->x, &m->y);
	m->palya = readMap(fin,m->x,m->y);
	m->mozg = false;
	fclose(fin);
	return m;
}

char* readMap(FILE* fin,int x,int y) //palya beolvasasa filebol
{
	char* palya = (char*)malloc((x * y) * sizeof(char));
	if (palya == NULL)
	{
		printf("Helyfoglalas nem sikerult.\n");
		return NULL;
	}
	char* a=(char*)malloc(y*sizeof(char));
	if (a == NULL)
	{
		printf("Helyfoglalas nem sikerult.\n");
		return NULL;
	}
	if (a == NULL)
	{
		printf("Helyfoglalas nem sikerult.\n");
		return NULL;
	}
	int i = 0,ii=0;
	for(int g=0;g<x;g++)
	{
		fscanf(fin, "%s", a);
		for (int j = 0; j < y; j++)
		{
			palya[ii + j] = a[j];
		}
		ii += y;
	}
	/*printf("ii=%d\n",ii);
	for (int g = 0; g < x; g++)
	{
		for (int j = 0; j < y; j++)
		{
			printf("%c", palya[(g*x) + j]);
		}
		printf("\n");
	}*/
	return palya;
}

int returnx(Map* m)
{
	return m->x;
}
int returny(Map* m)
{
	return m->y;
}

void PrintMap(Map* map)
{
	printf("A palya :\n");
	int x, y;
	x = returnx(map);
	y = returny(map);
	char a;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (x >= y)
				a = map->palya[(x * i) + j];
			else
				a = map->palya[(y * i) + j];
			switch (a)
			{
			case '0': printf(" "); break;
			case '1': printf("B"); break;
			case '2': printf("K"); break;
			case '3': printf("E"); break;
			case '4': printf("X"); break;
			//default: printf("\n"); break;
			}
		}
		printf("\n");
		
	}
}
int poz(Map* map)//a kezdo pozicio meghatarozasa
{
	char a;
	for (int i = 0; i < map->x; i++)
	{
		for (int j = 0; j < map->y; j++)
		{
			if (map->x >= map->y)
			{
				a = map->palya[(map->x * i) + j];
				if (a == '2')
					return (map->x * i) + j;
			}
			else
			{
				a = map->palya[(map->y * i) + j];
				if (a == '2')
					return (map->y * i) + j;
			}
		}
	}
	return -1;
}
int cel(Map* map)// a cel meghatarozasa
{
	char a;
	for (int i = 0; i < map->x; i++)
	{
		for (int j = 0; j < map->y; j++)
		{
			if (map->x >= map->y)
			{
				a = map->palya[(map->x * i) + j];
				if (a == '4')
					return (map->x * i) + j;
			}
			else
			{
				a = map->palya[(map->y * i) + j];
				if (a == '4')
					return (map->y * i) + j;
			}
		}
	}
	return -1;
}
Map* move(Map* map,char d) //mozgas a palyan
{
	char b;
	int xy;
	if (map->x < map->y)
	{
		xy = map->y;
	}
	else
	{
		xy = map->x;
	}
	switch (d)
	{
	case 'f':
		b = map->palya[map->poz - xy];
		if (b == '3' || b == '1')
		{
			printf("\nErre nem lehet mozogni.\n");
		}
		else
		{
			map->palya[map->poz - xy] = '2';
			map->palya[map->poz] = '0';
			map->poz -=xy;
			map->mozg = true;
		}
		break;
	case'b':
		b = map->palya[map->poz -1];
		if (b == '3' || b == '1')
		{
			printf("\nErre nem lehet mozogni.\n");
		}
		else
		{
			map->palya[map->poz - 1] = '2';
			map->palya[map->poz] = '0';
			map->poz -=1;
			map->mozg = true;
		}
		break;
	case'j':
		b = map->palya[map->poz + 1];
		if (b == '3' || b == '1')
		{
			printf("\nErre nem lehet mozogni.\n");
		}
		else
		{
			map->palya[map->poz + 1] = '2';
			map->palya[map->poz] = '0';
			map->poz += 1;
			map->mozg = true;
		}
		break;
	case 'l':
		b = map->palya[map->poz + xy];
		if (b == '3' || b == '1')
		{
			printf("\nErre nem lehet mozogni.\n");
		}
		else
		{
			map->palya[map->poz + xy] = '2';
			map->palya[map->poz] = '0';
			map->poz += xy;
			map->mozg = true;
		}
		break;
	}
	return map;
}
void DestroyMap(Map* m)
{
	free(m->palya);
	free(m);
	printf("A palya fel lett szabaditva.\n");
}