#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "Functions.h"

typedef struct {
	SDL_Rect rect;
	SDL_Texture* text;
}Entity;

Entity* CreateEntity(SDL_Renderer* renderer, int x, int y, int width, int height, const char* path);

Entity* CreateEntityTTF(SDL_Renderer* renderer, int x, int y, int width, int height, const char* font, char text[20], int fontsize, SDL_Color color);

bool CheckEntity(SDL_Point* mousecords, SDL_Rect* rect);

void DestroyEntity(Entity* b);

void ShowEntity(SDL_Renderer* renderer, Entity* but);







#endif // BUTTON_H