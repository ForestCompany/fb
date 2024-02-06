#pragma once
#ifndef PERSON
#define PERSON_H
#include"Functions.h"
#include"Item.h"
#define ENEMYCOUNT 6

typedef struct {
	Entity* soul;
	Stats stats;
	Item* inventory[6]; 
	bool alive;
}Person;

extern Person* EnemyArr[ENEMYCOUNT];

Person* CreatePerson(SDL_Renderer* r, int x, int y, int width, int height, const char* path);

void ShowFontStats(SDL_Renderer* r, Person* p, SDL_Color color);

void DestroyPerson(Person* p);

void ShowPerson(SDL_Renderer* r, Person* p);

void ShowStats(Person* p);

void PVP(Person* p1, Person* p2);

void IncrementHP(Person* p,int hp);

void DecrementHP(Person* p,int hp);

void IncrementMana(Person* p, int mana);

void DecrementMana(Person* p, int mana);

int GetX(Person *p);

int GetY(Person *p);

void GrabItem(Person *p, Item *it);

void IncX(Person *p, int x);

void IncY(Person *p, int y);

void ShowInventory(SDL_Renderer *r, Person *p);

void UpdateStats(Person *p, int index);

#endif 