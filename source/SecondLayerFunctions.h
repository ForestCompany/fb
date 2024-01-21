#pragma once
#ifndef	SECONDLFINCTIONS_H
#define SECONDLFINCTIONS_H

#include "Emanager.h"
#include "Map.h"
#include"Skill.h"




bool isnearperson(Person* p,  SDL_Point mousecords);

void Init(SDL_Window* w,SDL_Renderer* r);

void Quit(SDL_Window* w,SDL_Renderer* r);

// typeoftile gettype(Map* map, int x, int y);
void intro(SDL_Renderer* renderer);

void menu(SDL_Renderer* renderer);

void Game(SDL_Renderer* renderer);

#endif 


