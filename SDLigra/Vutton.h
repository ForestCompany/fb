#pragma once
#ifndef VUTTON_H
#define VUTTON_H

#include<SDL.h>
#include<stdbool.h>
#include "Functions.h"

typedef enum {
	ACTIVE,
	COOLDOWN
}VuttonState;

typedef struct {
	SDL_Rect rect;
	SDL_Texture* active;
	SDL_Texture* cooldown;
}Vutton;

Vutton* CreateVutton(SDL_Renderer* r, SDL_Rect rect, const char* apath, const char* cpath);

void ShowVutton(SDL_Renderer* r, Vutton* v);

void DestroyVutton(Vutton* v);

#endif // !VUTTON_H
