#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "Entity.h"

typedef enum {
	STATE1,
	STATE2
}ButtonState;

typedef struct {
	SDL_Rect rect;
	SDL_Texture* state1;
	SDL_Texture* state2;
	ButtonState state;
} Button;

Button* CreateButton(SDL_Renderer* r, SDL_Rect rect, const char* state1path, const char* state2path);
bool CheckButton(SDL_Point* mousecords, SDL_Rect* rect);
void DestroyButton(Button* button);
void SwitchButtonState(Button* h);
void ShowButton(SDL_Renderer* r, Button* button);
#endif // BUTTON_H