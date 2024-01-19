#pragma once
#ifndef SKILL_H
#define SKILL_H
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
}Skill;



Skill* CreateSkill(SDL_Renderer* r, SDL_Rect rect, const char* apath, const char* cpath,Uint32 delta,int manacost);

void ShowSkill(SDL_Renderer* r, Skill* v);

void DestroySkill(Skill* v);

void SwitchState(Skill* h);

void UpdateSkill(SDL_Renderer* r,Skill* b);

void PressSkill(Skill* b);
#endif // !SKILL_H