#pragma once
#ifndef TILE_H
#define TILE_H

#include"Entity.h"


typedef enum {
    GRASS,
    MOUNTAIN,
    ENEMY, 
} typeoftile;



typedef struct {
    Entity* soul;
    typeoftile type;
}Tile;

Tile* CreateTile(SDL_Renderer* renderer, int x, int y, int width, int height, const char* path, typeoftile t);

void ShowTile(SDL_Renderer* r, Tile* tile);

void DestroyTile(Tile* tile);

typeoftile GetTypeOFTile(Tile* t);



#endif // 
