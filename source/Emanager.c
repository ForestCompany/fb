#include "Emanager.h"

void FillEnemyArr(SDL_Renderer *r, Person *n[ENEMYCOUNT])
{
    for(int i = 0;i<ENEMYCOUNT;i++){
        n[i] = CreatePerson(r,TILESIZE*(i+2),TILESIZE,TILESIZE,TILESIZE,"images/vrag.png");
        n[i]->stats.armor = 0;
    }
}

void ShowEnemyArr(SDL_Renderer *r, Person *n[ENEMYCOUNT])
{
    for(int i = 0;i<ENEMYCOUNT;i++){
        ShowPerson(r,n[i]);
    }
}

void DestroyEnemyArr(Person* n[ENEMYCOUNT]) {
    for(int i = 0; i < ENEMYCOUNT; i++) {
        DestroyPerson(n[i]);
    }
}

bool IsNearEnemy(Person *p1, Person *p2) {
    int P1_x = GetX(p1) / TILESIZE;
    int P1_y = GetY(p1) / TILESIZE;
    int P2_x = GetX(p2) / TILESIZE;
    int P2_y = GetY(p2) / TILESIZE;

    bool isNearHorizontal = (P2_y == P1_y) && (abs(P2_x - P1_x) == 1);
    bool isNearVertical =   (P2_x == P1_x) && (abs(P2_y - P1_y) == 1);

    return isNearHorizontal || isNearVertical;
}


void AIEnemy(Person *n[ENEMYCOUNT], Person *tolik, int index) {
    Person *ego = n[index];
    if (IsNearEnemy(ego, tolik)) {
        PVP(ego, tolik);
    }
    else {
        if (GetX(tolik) > GetX(ego)) {
            IncX(ego, TILESIZE);
        } 
        else if (GetX(tolik) < GetX(ego)){
            IncX(ego, -TILESIZE);
        }
        if (GetY(tolik) > GetY(ego)) {
            IncY(ego, TILESIZE);
        } 
        else if (GetY(tolik) < GetY(ego)) {
            IncY(ego, -TILESIZE);
        }
    }
}