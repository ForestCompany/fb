#pragma once
#ifndef MAP_H
#define MAP_H
#include"Functions.h"
#include"Tile.h"



typedef struct {
	Tile** map; // ��������� ������ ����������
	int width;
	int height;
}Map;






Map* CreateMap(SDL_Renderer* renderer, int width, int height);

void DestroyMap(Map* map);

void ShowMap(SDL_Renderer* renderer, Map* map);


#endif // MAP_H