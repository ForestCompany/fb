#include "SecondLayerFunctions.h"

bool isnearperson(Person* p, Map* m, SDL_Point mousecords) {
    SDL_Point pcords = { p->soul->rect.x / WIDTHTILE, p->soul->rect.y / WIDTHTILE };
    mousecords.x = mousecords.x / WIDTHTILE;
    mousecords.y = mousecords.y / WIDTHTILE;

    if ((mousecords.x == pcords.x + 1 && mousecords.y == pcords.y) ||
        (mousecords.x == pcords.x - 1 && mousecords.y == pcords.y) ||
        (mousecords.x == pcords.x && mousecords.y == pcords.y + 1) ||
        (mousecords.x == pcords.x && mousecords.y == pcords.y - 1)) {
        return true;
    }

    return false;
}

typeoftile gettype(Map* map, int x, int y, Person* EnemyArr[6]) {
    for (int i = 0; i < 6; i++) {
        int EnemyX = EnemyArr[i]->soul->rect.y / WIDTHTILE;
        int EnemyY = EnemyArr[i]->soul->rect.x / WIDTHTILE;
        if (x == EnemyX && y == EnemyY && EnemyArr[i]->alive == true) {
            return ENEMY;
        }
    }
    typeoftile e = map->map[y][x].type;
    return e;

}