#include "../inc/Emanager.h"

void FillEnemyArr(SDL_Renderer *r, Person *n[ENEMYCOUNT])
{
    for(int i = 0;i<ENEMYCOUNT;i++){
        n[i] = CreateEnemy(r, (enemy_t)i);
    }
}

Person *CreateEnemy(SDL_Renderer *r, enemy_t e) {
    Person *res = NULL;
    switch (e) {
        case e1: res = CreatePerson(r,TILESIZE*2,TILESIZE,TILESIZE,TILESIZE,"resource/images/vrag1.png"); SetFullStats(res, 5, 5, 5, 5); break;
        case e2: res = CreatePerson(r,TILESIZE*3,TILESIZE,TILESIZE,TILESIZE,"resource/images/vrag2.png"); SetFullStats(res, 5, 5, 5, 5); break;
        case e3: res = CreatePerson(r,TILESIZE*4,TILESIZE,TILESIZE,TILESIZE,"resource/images/vrag3.png"); SetFullStats(res, 5, 5, 5, 5); break;
        case e4: res = CreatePerson(r,TILESIZE*5,TILESIZE,TILESIZE,TILESIZE,"resource/images/vrag4.png"); SetFullStats(res, 5, 5, 5, 5); break;
        case e5: res = CreatePerson(r,TILESIZE*6,TILESIZE,TILESIZE,TILESIZE,"resource/images/vrag5.png"); SetFullStats(res, 5, 5, 5, 5); break;
        case e6: res = CreatePerson(r,TILESIZE*7,TILESIZE,TILESIZE,TILESIZE,"resource/images/vrag6.png"); SetFullStats(res, 5, 5, 5, 5); break;
        default: res = NULL; break;
    }
    return res;
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