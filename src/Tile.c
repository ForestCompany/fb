#include "../inc/Tile.h"

Tile* CreateTile(SDL_Renderer* r, int x, int y, int width, int height, const char* path, typeoftile t)
{
    Tile* te = (Tile*)malloc(sizeof(Tile));
    te->soul = CreateEntity(r,x,y,width,height,path);
    te->type = t;
    return te;
}



void ShowTile(SDL_Renderer* r, Tile* tile) {
    ShowEntity(r, tile->soul);
}

void DestroyTile(Tile* tile) {
    DestroyEntity(tile->soul);
    free(tile);
}

typeoftile GetTypeOFTile(Tile* t){
    return t->type;
}
