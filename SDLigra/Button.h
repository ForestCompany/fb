#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include "Functions.h"
#include "Entity.h"
typedef enum {
	ACTIVE,
	COOLDOWN
}ButtonState;

typedef struct {
	SDL_Rect rect;
	SDL_Texture* active;
	SDL_Texture* cooldown;
	ButtonState state;
	Uint32 delta;
	Uint32 StartCd;
	Uint32 counter;
	Entity* timer;
	Uint32 lastTimerUpdate;
	int manacost;
}Button;

Button* CreateButton(SDL_Renderer* r, SDL_Rect rect, const char* apath, const char* cpath,Uint32 delta,int manacost);

void ShowButton(SDL_Renderer* r, Button* v);

void DestroyButton(Button* v);

void SwitchState(Button* h);

void UpdateButton(SDL_Renderer* r,Button* b);

void PressButton(Button* b);
#endif // !VUTTON_H