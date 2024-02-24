#include "../inc/Map.h"






Map* CreateMap(SDL_Renderer* renderer, int width, int height)
{
    Map* mp = (Map*)malloc(sizeof(Map));
    mp->width = width;
    mp->height = height;
    const char* path;
    typeoftile type;

    mp->map = (Tile**)malloc(sizeof(Tile*) * height);
    for (int i = 0; i < height; i++) {
        mp->map[i] = (Tile*)malloc(sizeof(Tile) * width);
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                path = "resource/images/Mountains.png";
                type = MOUNTAIN;
            }
            else {
                path = "resource/images/tile.png";
                type = GRASS;
            }
            mp->map[i][j].soul = CreateEntity(renderer, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE, path);
            mp->map[i][j].type = type;
        }
    }
    return mp;
}


void ShowMap(SDL_Renderer* renderer, Map* map) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            ShowTile(renderer, &map->map[i][j]);
        }
    }
    SDL_RenderPresent(renderer);
}





void DestroyMap(Map* map) {
    if (map != NULL) {
        for (int i = 0; i < map->height; i++) {
            for (int j = 0; j < map->width; j++) {
                DestroyEntity(map->map[i][j].soul);
            }
            free(map->map[i]);
        }
        free(map->map);
        free(map);
    }
}




