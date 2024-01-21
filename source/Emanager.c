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

void DestroyEnemyArr(Person* n[ENEMYCOUNT]){
    for(int i = 0;i<ENEMYCOUNT;i++){
        DestroyPerson(n[i]);
    }
}