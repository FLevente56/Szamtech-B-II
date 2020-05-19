#define _CTR_SECURE_NO_WARNINGS
#define _CTR_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable : 4996)

#include "map.h"
#include "basic.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int menu(Karakter* avatar, Map* mapp)// a menu
{
	printf("Menu\n");
	printf("1) Mozgas \n 2)Karakter mutatasa\n 3)Kilepes\n");
	bool done = false, done2 = false;
	int a, b;
	do {
		printf("A kovetkezo utasitas:");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			do {
				printf("Irany: 1)FEL 2)BALRA 3)JOBBRA 4)LE\nDirection=");
				scanf("%d", &b);
				switch (b)
				{
				case 1: mapp = move(mapp, 'f'); done2 = true; break;
				case 2: mapp = move(mapp, 'b'); done2 = true; break;
				case 3: mapp = move(mapp, 'j'); done2 = true; break;
				case 4: mapp = move(mapp, 'l'); done2 = true; break;
				default:; break;
				}
				if (mapp->mozg == true)
				{
					avatar = harc(avatar);
					mapp->mozg = false;
				}
			} while (!done2);
			PrintMap(mapp);
			break;
		case 2: PrintCharacterSheet(avatar); break;
		case 3: done = true; break;
		}
	} while (!done && avatar->el && !(mapp->poz == mapp->cel));
	if (mapp->poz == mapp->cel)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

int main()
{
	Karakter* kar = Create();
	Map* map = valasztmap();
	PrintMap(map);
	int outc;
	outc=menu(kar, map);
	if (outc == 1)
	{
		printf("GAME OVER\n");
	}
	else
	{
		printf("Sikeresen elerted a kijaratot\n");
	}
	DestroyMap(map);
	Destroy(kar);
	system("pause");
	return 0;
}