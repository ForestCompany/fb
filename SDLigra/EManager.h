#pragma once
#ifndef EMANAGER_H
#define	EMANAGER_H
#include"Person.h"
#define ENEMYCOUNT 6
typedef enum {
    EASY_ENEMY,
    MEDIUM_ENEMY,
    HARD_ENEMY,
    VERY_HARD_ENEMY,
    EXTREME_ENEMY,
    BOSS_ENEMY
} EnemyType;


Person* EnemyArr[ENEMYCOUNT];

void FillEnemyArr(SDL_Renderer* r);

Person* CreateEnemy(SDL_Renderer* r, EnemyType type);

void DestroyEnemyArr();

void ShowEnemyArr(SDL_Renderer* r);

Person* FindEnemy(int x, int y);

bool IsWin();


#endif // !EMANAGER_H