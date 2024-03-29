#include "../inc/Emanager.h"


bool IsOverlapping(Person *n[], int count, int x, int y) {
    for (int i = 0; i < count; i++) {
        if (n[i]->soul->rect.x == x && n[i]->soul->rect.y == y) {
            return true; // Враг уже на этой позиции
        }
    }
    return false; // Нет наложения
}



void FillEnemyArr(SDL_Renderer *r, Person *n[ENEMYCOUNT])
{
        for (int i = 0; i < ENEMYCOUNT; i++) {
        n[i] = CreateEnemy(r, (enemy_t)i);
    }
}


int NumStats(enemy_t e, int count)
{
    return (e + 2) * count;
}
   
Person *CreateEnemy(SDL_Renderer *r, enemy_t e) {
    Person *res = NULL;
    Item *it = NULL;
    static int count = 1;

    int power = NumStats(e, count)-1;
    int intellekt = NumStats(e, count);
    int armor = NumStats(e, count)-count;
    int damage = NumStats(e, count)-count*2;


    switch (e) {
        case e1: res = CreatePerson(r,TILESIZE*2,TILESIZE,TILESIZE,TILESIZE,GetEnemyImagePath(e)); 
            SetFullStats(res, power, intellekt, armor, damage+2); 
            it = CreateItem(r,"a", 0,0,0,0,GetEnemyItemImagePath(e),10,0,0,0); 
            res->inventory[0] = it;break;
        case e2: res = CreatePerson(r,TILESIZE*3,TILESIZE,TILESIZE,TILESIZE,GetEnemyImagePath(e)); 
            SetFullStats(res, power, intellekt, armor, damage+2); 
            it = CreateItem(r,"b", 0,0,0,0,GetEnemyItemImagePath(e),0,15,0,0); 
            res->inventory[0] = it;  break;
        case e3: res = CreatePerson(r,TILESIZE*4,TILESIZE,TILESIZE,TILESIZE,GetEnemyImagePath(e)); 
            SetFullStats(res, power, intellekt, armor, damage);
            it = CreateItem(r,"c", 0,0,0,0,GetEnemyItemImagePath(e),0,0,0,10); 
            res->inventory[0] = it; count++; break;
        case e4: res = CreatePerson(r,TILESIZE*5,TILESIZE,TILESIZE,TILESIZE,GetEnemyImagePath(e)); 
            SetFullStats(res, power, intellekt, armor, damage); 
            it = CreateItem(r,"d", 0,0,0,0,GetEnemyItemImagePath(e),0,0,15,0); 
            res->inventory[0] = it; count++; break;
        case e5: res = CreatePerson(r,TILESIZE*6,TILESIZE,TILESIZE,TILESIZE,GetEnemyImagePath(e));
            SetFullStats(res, power, intellekt, armor, damage);  
            it = CreateItem(r,"e", 0,0,0,0,GetEnemyItemImagePath(e),0,0,10,0); 
            res->inventory[0] = it; count++; break;
        case e6: res = CreatePerson(r,TILESIZE*7,TILESIZE,TILESIZE,TILESIZE,GetEnemyImagePath(e));
            SetFullStats(res, power, intellekt, armor, damage); 
            it = CreateItem(r,"ё", 0,0,0,0,GetEnemyItemImagePath(e),15,0,0,0); 
            res->inventory[0] = it; count++; break;
        default: res = NULL; break;
    }
    res->alive = false;
    return res;
}


const char* GetEnemyImagePath(enemy_t e) {
    const char* enemyImages[] = {
        "resource/images/vrag1.png",
        "resource/images/vrag2.png",
        "resource/images/vrag3.png",
        "resource/images/vrag4.png",
        "resource/images/vrag5.png",
        "resource/images/vrag6.png"
    };
    return enemyImages[e];
}

const char* GetEnemyItemImagePath(enemy_t e) {
    const char* enemyItemImages[] = {
        "resource/images/profile1.png",
        "resource/images/profile2.png",
        "resource/images/profile3.png",
        "resource/images/profile4.png",
        "resource/images/profile5.png",
        "resource/images/profile6.png"
    };
    return enemyItemImages[e];
}

void UpdateEnemyArrStats(Person *n[ENEMYCOUNT]) {
    for (int i = 0; i < ENEMYCOUNT; i++) {
        Person *ego = n[i];
        SetFullStats(ego, ego->stats.power->kolik + 5, ego->stats.intellekt->kolik, ego->stats.armor + 5,ego->stats.damage + 7);
        ego->stats.hp = ego->stats.power->cap;
        ego->stats.mana = ego->stats.intellekt->cap;
        ego->soul->rect.x = TILESIZE * 18;
        ego->soul->rect.y = TILESIZE * (rand()%7 + 1);
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

bool IsDead(Person *n[ENEMYCOUNT]) {
    for (int i = 0; i < ENEMYCOUNT; i++) {
        if (n[i]->alive == true) {
            return false;
        }
    }
    return true;
}

void UpdateGame(wave_t *wave, Person *EnemyArr[ENEMYCOUNT], Person *tolik, Uint32 *lastUpdateTime, Uint32 *lasttimerAI) {
    if (wave->numberofwaves != 0 && IsDead(EnemyArr)) {
        if ((*wave).waveInProgress == false) {
            wave->waveInProgress = true;
            wave->numberofwaves--;
            UpdateEnemyArrStats(EnemyArr);
            tolik->soul->rect.x = TILESIZE;
            tolik->soul->rect.y = TILESIZE;
            wave->waveCounter++;
            wave->enemiesSpawned = 0;
        }
    }

    if (wave->waveInProgress && wave->enemiesSpawned < wave->enemiesPerWave) {
        if (SDL_GetTicks() - *lastUpdateTime >= 500) {
            EnemyArr[wave->enemiesSpawned]->alive = true;
            wave->enemiesSpawned++;
            *lastUpdateTime = SDL_GetTicks();
        }
    }

    if (SDL_GetTicks() - *lasttimerAI >= 500 && wave->waveInProgress) {
        AIEnemy(EnemyArr, tolik);
        *lasttimerAI = SDL_GetTicks();
    }
    if (IsDead(EnemyArr) && wave->enemiesSpawned == wave->enemiesPerWave) {
        wave->waveInProgress = false;
    }
}

// void AIEnemy(Person *n[ENEMYCOUNT], Person *tolik, int index) {
//     Person *ego = n[index];
//     if (IsNearEnemy(ego, tolik)) {
//         PVP(ego, tolik);
//     }
//     else {
//         if (GetX(tolik) > GetX(ego)) {
//             IncX(ego, TILESIZE);
//         } 
//         else if (GetX(tolik) < GetX(ego)){
//             IncX(ego, -TILESIZE);
//         }
//         if (GetY(tolik) > GetY(ego)) {
//             IncY(ego, TILESIZE);
//         } 
//         else if (GetY(tolik) < GetY(ego)) {
//             IncY(ego, -TILESIZE);
//         }
//     }
// }


// bool IsEnemyAtPosition(Person *n[ENEMYCOUNT], int x, int y, int currentIndex) {
//     for (int i = 0; i < ENEMYCOUNT; ++i) {
//         if (i != currentIndex && n[i] != NULL && GetX(n[i]) == x && GetY(n[i]) == y) {
//             return true;
//         }
//     }
//     return false;
// }

// bool IsPersonAtPosition(Person *person, int x, int y) {
//     return person != NULL && GetX(person) == x && GetY(person) == y;
// }
Person *FindEnemy(SDL_Point mapcords, Person *EnemyArr[ENEMYCOUNT])
{
    for(int i = 0;i<ENEMYCOUNT;i++){
        int EnemyX = GetY(EnemyArr[i]) / TILESIZE;
        int EnemyY = GetX(EnemyArr[i]) / TILESIZE;
        if(mapcords.x == EnemyX && mapcords.y == EnemyY && EnemyArr[i]->alive){
            return EnemyArr[i];
        }
    }
    return NULL;
}


void AIEnemy(Person *n[ENEMYCOUNT], Person *tolik) {
    for (int i = 0; i < ENEMYCOUNT; ++i) {
        if (n[i]->alive) {
            Person *ego = n[i];
            SDL_Point TOLIKXY = {GetX(tolik) / TILESIZE, GetY(tolik) / TILESIZE};
            SDL_Point EGOXY = {GetX(ego) / TILESIZE, GetY(ego) / TILESIZE};
            if (IsOnDiagonal(tolik, ego)){
                SDL_Point mas[2] = {0};
                FindCommonPoints(mas, tolik, ego);
                if (FindEnemy(mas[0], n) == NULL && FindEnemy(mas[1], n) == NULL) {
                    Move(ego, mas[rand()%2]);
                }
                else if (FindEnemy(mas[0], n) != NULL && FindEnemy(mas[1], n) == NULL) {
                    Move(ego, mas[1]);
                }
                else if (FindEnemy(mas[0], n) == NULL && FindEnemy(mas[1], n) != NULL) {
                    Move(ego, mas[0]);
                }
                continue;
            }
            if (IsNearEnemy(ego, tolik)) {
                PVP(ego, tolik);
                continue;
            }
            if (TOLIKXY.x > EGOXY.x) {
                Move(ego, (SDL_Point){EGOXY.x + 1, EGOXY.y});
                continue;
            }
            if (TOLIKXY.x < EGOXY.x) {
                Move(ego, (SDL_Point){EGOXY.x - 1, EGOXY.y});
                continue;
            }
            if (TOLIKXY.y > EGOXY.y) {
                Move(ego, (SDL_Point){EGOXY.x, EGOXY.y + 1});
                continue;
            }
            if (TOLIKXY.y < EGOXY.y) {
                Move(ego, (SDL_Point){EGOXY.x, EGOXY.y - 1});
                continue;
            }
        }
    }
}






