#pragma once
#ifndef ITEM_H
#define ITEM_H
#include"Functions.h"
#include"Entity.h"
#include"Stats.h"


typedef struct {
	const char* title;
	Entity* soul;
	Stats stats;
}Item;

Item* CreateItem(SDL_Renderer* r,const char* title, int x, int y, int width, int height, const char* path, int hp, int mana, int armor, int damage);

void ShowItem(SDL_Renderer *r, Item *i);

void DestroyItem(Item*);

#endif 