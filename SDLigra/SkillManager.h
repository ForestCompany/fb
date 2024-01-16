#pragma once
#ifndef SMANAGER_H
#define SMANAGER_H
#include"Button.h"
#define SKILLCOUNT 3


Button* SkillArray[3];

void FillSkillArr(SDL_Renderer* r);

void ShowSkillArr(SDL_Renderer* r);

void UpdateSkillArr(SDL_Renderer* r);

void DetroySkillArr();

#endif