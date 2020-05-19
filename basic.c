#define _CTR_SECURE_NO_WARNINGS
#define _CTR_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable : 4996)
#pragma warning(disable : 4703)

#include "basic.h"
#include "map.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

Karakter* Create()//Karakter keszites
{
	Karakter* uj=(Karakter*)malloc(1*sizeof(Karakter));
	uj->name = nev();
	uj->classtype = selectClassType();//osztalyvalasztas
	switch (uj->classtype)
	{
	case 1:
		uj->baseDMG=60;
		uj->HP=80;
		uj->currentHP = uj->HP;
		uj->HPregen = 15;
		break;
	case 2:
		uj->baseDMG = 50;
		uj->HP = 100;
		uj->currentHP = uj->HP;
		uj->HPregen = 10;
		break;
	case 3:
		uj->baseDMG = 40;
		uj->HP = 120;
		uj->currentHP = uj->HP;
		uj->HPregen = 5;
		break;
	}
	uj->exp = 0;
	uj->level = 1;
	uj->el = true;
	return uj;
}
char* nev()//nevadas a karakternek
{
	char* c = (char*)malloc(40 * sizeof(char));
	printf("A karaktered neve:");
	scanf("%39s", c);
	return c;
}
int selectClassType()//osztalyvalasztas
{
	bool done = false;
	printf("Karakter osztalyok:\n");
	printf("1) Bandita: DMG=60-90 HP=80 HPregen=15\n");
	printf("2) Katona: DMG=50-80 HP=100 HPregen=10\n");
	printf("3) Barbar: DMG=40-70 HP=120 HPregen=5\n");
	int a=0;
	do
	{
		printf("A karakter osztalyod:");
		scanf("%i", &a);
		switch(a)
		{
			case 1:
				printf("Sikeres karaktervalasztas! A karaktered osztalya: Bandita\n");
				done = true;
				break;
			case 2:
				printf("Sikeres karaktervalasztas! A karaktered osztalya: Katona\n");
				done = true;
				break;
			case 3:
				printf("Sikeres karaktervalasztas! A karaktered osztalya: Barbar\n");
				done = true;
				break;
			default:
				printf("Sikertelen karaktervalasztas!\n");
				break;
		}
	} while (!done);
	return a;
}
void Destroy(Karakter* avatar)
{
	free(avatar->name);
	free(avatar);
}
Karakter* LVLUP(Karakter* avatar)//Szintlepes
{
	Karakter* aavatar = avatar;
	aavatar->exp -= 250 * (aavatar->level+1);
	aavatar->level++;
	printf("A karakteres szintet lepett! Uj szint: %d\n", aavatar->level);
	printf("A karaktered meggyogyult!\n");
	printf("Valassz mit fejlesztessz 1-DMG(+10) 2-HP(+20) 3-HPregen(+5)\n");
	printf("Valaszt:=");
	int a;
	scanf("%i", &a);
	switch (a)
	{
	case 1:
		aavatar->baseDMG += 10;
		break;
	case 2:
		aavatar->HP += 20;
		break;
	case 3:
		aavatar->HPregen += 5;
		break;
	default:printf("Sikertelen szintlepes!\n"); break;
	}
	aavatar->currentHP = aavatar->HP;
	return aavatar;
}
Karakter* addXP(Karakter* avatar, unsigned amount)
{
	avatar->exp += amount;
	while(avatar->exp>=((avatar->level+1)*250))
	{
		avatar = LVLUP(avatar);//Szintlepes
	}
	Printjust(avatar);
	return avatar;
}
Karakter* takeDMG(Karakter* avatar, int amount)
{
	avatar->currentHP -= amount;
	if (avatar->currentHP <= 0)
	{
		avatar->el = false;//Karakter/Ellenseg meghal
	}
	return avatar;
}
Karakter* heal(Karakter* avatar)//Minden harc utan ha a karakter tuleli a a harcot akkor HPregen-el gyogyul
{
	avatar->currentHP += avatar->HPregen;
	if (avatar->currentHP > avatar->HP)
	{
		avatar->currentHP = avatar->HP;
	}
	return avatar;
}
void PrintCharacterSheet(Karakter* avatar)//Karakter szepen kiirasa
{
	printf("A karakter neve: %s\n", avatar->name);
	switch (avatar->classtype)
	{
	case 1:printf("A karakter osztaly: Bandita\n"); break;
	case 2:printf("A karakter osztaly: Katona\n"); break;
	case 3:printf("A karakter osztaly: Barbar\n"); break;
	}
	printf("A karakter jelenlegi szintje: %d\n", avatar->level);
	printf("A tapasztalat a kovetkezo szintig : ( %d / %d )\n", avatar->exp,(avatar->level+1)*250);
	printf("A karakter sebzese: %d - %d\n", avatar->baseDMG, avatar->baseDMG+30);
	printf("A karakter jelenlegi eletereje: ( %d / %d )\n",avatar->currentHP,avatar->HP);
	printf("A karakter gyogyulasa szobankent: %d\n", avatar->HPregen);
}
void Printjust(Karakter* avatar)// Alapveto dolgok kiirasa
{
	printf("%s - ", avatar->name);
	switch (avatar->classtype)
	{
	case 1:printf("Bandita : "); break;
	case 2:printf("Katona : "); break;
	case 3:printf("Barbar : "); break;
	}
	printf("EXP:=( %d / %d ) - ", avatar->exp, (avatar->level+1) * 250);
	printf("HP:=( %d / %d ) - ", avatar->currentHP, avatar->HP);
}

Karakter* harc(Karakter* avatar)
{
	srand(time(0));
	int a = rand() % 3 + 1;//ellenfel tipusa
	Karakter* enemy;
	printf("\n\n\n\n");
	if (a == 1)
	{
		printf("Egy gyenge ellenfel van ebben a szobaban\n");
		enemy = enemyC(a);
	}
	else
	{
		if (a == 2)
		{
			printf("Egy kozepesen eros ellenfel van ebben a szobaban\n");
			enemy = enemyC(a);
		}
		else
		{
			printf("Egy eros ellenfel van ebben a szobaban\n");
			enemy = enemyC(a);
		}
	}
	int i = 1;
	int dmg1, dmg2;
	while (enemy->el==true && avatar->el==true)
	{
		printf("KOR: %d\n", i);
		dmg1 = rand() % 30 + avatar->baseDMG;//a karakterunk sebzese
		dmg2 = rand() % 30 + enemy->baseDMG+(avatar->level-1)+10;//ellenfel sebzese
		printf("A te sebzesed:%d. Az ellenfel sebzese:%d\n", dmg1, dmg2);
		if (dmg1 > dmg2)//Az tamad eloszor akinek nagyobb a sebzese ebben a korben
		{
			enemy = takeDMG(enemy, dmg1);
			if(enemy->el)//csak akkor tamad a masik fel ha tulelte az elso sebzeset
				avatar = takeDMG(avatar, dmg2);
		}
		else
		{
			if (dmg1 = dmg2)
			{
				enemy = takeDMG(enemy, dmg1);
				avatar = takeDMG(avatar, dmg2);
			}
			else
			{
				avatar = takeDMG(avatar, dmg2);
				if (avatar->el)
					enemy = takeDMG(enemy, dmg1);
			}
		}
		printf("A te HP-d:(%d/%d). Az ellenfel HP-ja:(%d/%d)\n", avatar->currentHP, avatar->HP,enemy->currentHP, enemy->HP);
		i++;
	}
	if (avatar->el)
	{
		avatar = heal(avatar);
		avatar = addXP(avatar,( enemy->HP + enemy->baseDMG)+100);
	}
	Destroy(enemy);
	return avatar;
}
Karakter* enemyC(int a)//Elllenseg keszitese
{
	Karakter* uj = (Karakter*)malloc(1 * sizeof(Karakter));
	uj->level=0;
	uj->classtype=0;
	uj->name=NULL;
	uj->exp=0;
	uj->baseDMG = 5 * a;
	uj->HP=a*30;
	uj->HPregen=0;
	uj->currentHP= uj->HP;
	uj->el=true;
	return uj;
}

