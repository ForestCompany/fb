#include "SecondLayerFunctions.h"

bool isnearperson(Person* p,  SDL_Point mousecords) {
    SDL_Point pcords = { p->soul->rect.x / TILESIZE, p->soul->rect.y / TILESIZE };
    mousecords.x = mousecords.x / TILESIZE;
    mousecords.y = mousecords.y / TILESIZE;

    if ((mousecords.x == pcords.x + 1 && mousecords.y == pcords.y) ||
        (mousecords.x == pcords.x - 1 && mousecords.y == pcords.y) ||
        (mousecords.x == pcords.x && mousecords.y == pcords.y + 1) ||
        (mousecords.x == pcords.x && mousecords.y == pcords.y - 1)) {
        return true;
    }

    return false;
}

// typeoftile gettype(Map* map, int x, int y) {
//     // for (int i = 0; i < 6; i++) {

//     //     int EnemyX = EnemyArr[i]->soul->rect.y / TILESIZE;
//     //     int EnemyY = EnemyArr[i]->soul->rect.x / TILESIZE;
//     //     if (x == EnemyX && y == EnemyY && EnemyArr[i]->alive == true) {
//     //         return ENEMY;
//     //     }
//     // }
//     typeoftile e = map->map[y][x].type;
//     return e;

// }