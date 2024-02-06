#pragma once
#ifndef EMANAGER_H
#define EMANAGER_H
#include"Person.h"
#define ENEMYCOUNT 6


void FillEnemyArr(SDL_Renderer* r,Person* n[ENEMYCOUNT]);

void DestroyEnemyArr(Person* n[ENEMYCOUNT]);

void ShowEnemyArr(SDL_Renderer* r,Person* n[ENEMYCOUNT]);

void AIEnemy(Person *n[ENEMYCOUNT], Person *tolik, int index);

bool IsNearEnemy(Person *p1, Person *p2);

#endif