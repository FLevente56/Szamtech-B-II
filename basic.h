#pragma once
#ifndef BASIC_H
#define BASIC_H

#define _CTR_SECURE_NO_WARNINGS
#define _CTR_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN

#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Karakter {
	unsigned level;
	int classtype;
	char* name;
	unsigned exp;
	unsigned baseDMG;
	unsigned HP;
	int HPregen;
	int currentHP;
	bool el;
}Karakter;

Karakter* Create();
char* nev();
int selectClassType();
void Destroy(Karakter* avatar);
Karakter* LVLUP(Karakter* avatar);
Karakter* addXP(Karakter* avatar, unsigned amount);
Karakter* takeDMG(Karakter* avatar, int amount);
Karakter* heal(Karakter* avatar);
void PrintCharacterSheet(Karakter* avatar);
void Printjust(Karakter* avatar);
Karakter* harc(Karakter* avatar);
Karakter* enemyC(int a);

#endif// !BASIC_H