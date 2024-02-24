#pragma once
#ifndef EMANAGER_H
#define EMANAGER_H
#include"Person.h"
#define ENEMYCOUNT 6

typedef enum enemy_e {
    e1,
    e2,
    e3,
    e4,
    e5,
    e6,
}           enemy_t;
Person *CreateEnemy(SDL_Renderer *r, enemy_t e);

void FillEnemyArr(SDL_Renderer* r,Person* n[ENEMYCOUNT]);

void DestroyEnemyArr(Person* n[ENEMYCOUNT]);

void ShowEnemyArr(SDL_Renderer* r,Person* n[ENEMYCOUNT]);

void AIEnemy(Person *n[ENEMYCOUNT], Person *tolik, int index);

bool IsNearEnemy(Person *p1, Person *p2);

#endif