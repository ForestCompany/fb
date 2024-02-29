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

typedef struct wave_s {
    int waveCounter;
    int enemiesPerWave;
    int enemiesSpawned;
    bool waveInProgress; 
    int numberofwaves;
}              wave_t;

Person *CreateEnemy(SDL_Renderer *r, enemy_t e);

bool IsDead(Person *n[ENEMYCOUNT]);

void UpdateGame(wave_t *wave, Person *EnemyArr[ENEMYCOUNT], Person *tolik,Uint32 *lastUpdateTime, Uint32 *lasttimerAI);

void FillEnemyArr(SDL_Renderer* r,Person* n[ENEMYCOUNT]);

bool IsPersonAtPosition(Person *person, int x, int y);

bool IsEnemyAtPosition(Person *n[ENEMYCOUNT], int x, int y, int currentIndex);

bool IsOverlapping(Person *n[], int count, int x, int y);

void DestroyEnemyArr(Person* n[ENEMYCOUNT]);

bool IsOnDiagonal(Person *centr, Person *satelit);

void ShowEnemyArr(SDL_Renderer* r,Person* n[ENEMYCOUNT]);

void AIEnemy(Person *n[ENEMYCOUNT], Person *tolik);

bool IsNearEnemy(Person *p1, Person *p2);

const char* GetEnemyImagePath(enemy_t e);

const char* GetEnemyItemImagePath(enemy_t e);

#endif