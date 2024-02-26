#pragma once
#ifndef	SECONDLFINCTIONS_H
#define SECONDLFINCTIONS_H

#include "Emanager.h"
#include "Map.h"
#include "Skill.h"


void FillBufferArr(Map *map, Item ***BufferArr);

bool IsMouseNearPerson(Person* p,  SDL_Point mousecords);

void Init(SDL_Window* w,SDL_Renderer* r);

void Quit(SDL_Window* w,SDL_Renderer* r);

// typeoftile gettype(Map* map, int x, int y);
void intro(SDL_Renderer* renderer);

typeoftile GetType(Map* map,SDL_Point mouse,Person* EnemyArr[ENEMYCOUNT]);

void Game(SDL_Renderer* renderer);

Person* FindEnemy(SDL_Point mapcords,Person* EnemyArr[ENEMYCOUNT]);
#endif 


