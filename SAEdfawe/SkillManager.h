#pragma once
#ifndef SMANAGER_H
#define SMANAGER_H
#include"Skill.h"
#define SKILLCOUNT 3


Skill* SkillArray[SKILLCOUNT];

void FillSkillArr(SDL_Renderer* r);

void ShowSkillArr(SDL_Renderer* r);

void UpdateSkillArr(SDL_Renderer* r);

void DetroySkillArr();

#endif