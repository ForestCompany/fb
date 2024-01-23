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



void Game(SDL_Renderer *renderer)
{
    Uint32 lastUpdateTime = 0;

    Map* map = CreateMap(renderer, SCREENHEIGHT / TILESIZE - 2, SCREENWIDTH / TILESIZE);

    Person* TOLIK = CreatePerson(renderer, TILESIZE, TILESIZE, TILESIZE, TILESIZE, "images/tolik.png");
    Person* EnemyArr[ENEMYCOUNT];
    FillEnemyArr(renderer,EnemyArr);

    Skill* skil  = CreateSkill(renderer,(SDL_Rect){XTABSKILL,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE},"images/sword.jpg","images/swordBLACK.jpg",5000,35);
    Skill* skil1 = CreateSkill(renderer,(SDL_Rect){XTABSKILL1,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE},"images/heal.jpg","images/healBLACK.jpg",10000,35);
    Skill* skil2 = CreateSkill(renderer,(SDL_Rect){XTABSKILL2,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE},"images/ulta.jpg","images/ultaBLACK.jpg",15000,30);

  
    Entity* hood = CreateEntity(renderer, 0, TILESIZE*HEIGHTAMOUNT, SCREENWIDTH, SCREENHEIGHT - (TILESIZE*HEIGHTAMOUNT), "images/hood.png");

    SDL_Color color = { 0,0,0,255 };




    bool cursor = false;

    SDL_Point mousecords;

    SDL_Texture* bufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREENWIDTH, SCREENHEIGHT);
    SDL_SetRenderTarget(renderer, bufferTexture);
    SDL_Event e;

    bool isexit = false;

    while (!isexit) {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastUpdateTime;
        while (SDL_PollEvent(&e) != 0) {
             
            switch (e.type) {
            case SDL_QUIT:
                isexit = true;
                break;

            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    isexit = true;
                    break;
                case SDLK_q:
           
                        if(skil->b->state == STATE1 && TOLIK->stats.mana>= skil->manacost){
                            PressSkill(skil);
                            DecrementHP(TOLIK,25);
                            DecrementMana(TOLIK,skil->manacost);
                        }
                    break;
                case SDLK_w:
                    if(skil1->b->state == STATE1 && TOLIK->stats.mana>= skil1->manacost){
                            PressSkill(skil1);
                            DecrementHP(TOLIK,25);
                            DecrementMana(TOLIK,skil1->manacost);
                        }
                    break;
                case SDLK_e:
                    if(skil2->b->state == STATE1&& TOLIK->stats.mana>= skil2->manacost){
                            PressSkill(skil2);
                            DecrementHP(TOLIK,25);
                            DecrementMana(TOLIK,skil2->manacost);
                        }
                    break;
                
                }
                break;

            case SDL_MOUSEMOTION:
                cursor = false;
                SDL_GetMouseState(&mousecords.x, &mousecords.y);

                cursor = isnearperson(TOLIK, mousecords);
                if (cursor) {
                    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
                }
                else {
                    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
                }
                break;

            case SDL_MOUSEBUTTONDOWN: {
                SDL_GetMouseState(&mousecords.x, &mousecords.y);
                SDL_Point mapcord = { mousecords.y / TILESIZE, mousecords.x / TILESIZE };
             
                typeoftile e = GetTypeOFTile(&(map->map[mapcord.y][mapcord.x]));

                if (isnearperson(TOLIK,  mousecords)) {
                    switch (e) {
                    case GRASS:
                        printf("GRASS\n");
                        TOLIK->soul->rect.x = map->map[mapcord.y][mapcord.x].soul->rect.x;
                        TOLIK->soul->rect.y = map->map[mapcord.y][mapcord.x].soul->rect.y;
                        break;

                    case MOUNTAIN:
                        printf("MOUNTAIN\n");
                        break;

                    case ENEMY:
                        printf("ENEMY\n");
                        // Person* enemy = FindEnemy(mapcord.x, mapcord.y,EnemyArr);
                        // PVP(TOLIK, enemy);
                        break;
                    }
                }
                break;
            }
            }
        }
        UpdateSkill(renderer,skil);
        UpdateSkill(renderer,skil1);
        UpdateSkill(renderer,skil2);
    
        SDL_SetRenderTarget(renderer, bufferTexture);
        ShowMap(renderer, map);
        ShowPerson(renderer, TOLIK);
      
        ShowEntity(renderer, hood);
        ShowEnemyArr(renderer,EnemyArr);
        ShowSkill(renderer,skil);
        ShowSkill(renderer,skil1);
        ShowSkill(renderer,skil2);
        ShowFontStats(renderer,TOLIK, color);
      
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
        SDL_RenderPresent(renderer);


        if (deltaTime >= 1000) {
            if (TOLIK->stats.hp < TOLIK->stats.power->cap) {
                TOLIK->stats.hp += TOLIK->stats.power->income;
            }
            if(TOLIK->stats.mana < TOLIK->stats.intellekt->cap) {
                TOLIK->stats.mana += TOLIK->stats.intellekt->income;
            }
            lastUpdateTime = currentTime; 
        }
        
      
        SDL_Delay(1000./fps);
    }

 
    SDL_DestroyTexture(bufferTexture);

    DestroyPerson(TOLIK);
    DestroyEntity(hood);
    DestroyMap(map);
    DestroyEnemyArr(EnemyArr);
    DestroySkill(skil);
    DestroySkill(skil1);
    DestroySkill(skil2);

}

// void intro(SDL_Renderer* renderer){
//     Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "images/intro.png");
//     bool isexit = false;
//     Uint32 starttimer = SDL_GetTicks();
//     while (!isexit) {
//         ShowEntity(renderer, background);
//         SDL_RenderPresent(renderer);
//         SDL_Delay(1000./fps);
//         if(SDL_GetTicks()-starttimer >=5000){
//             isexit = true;
//         }
//     }


//     DestroyEntity(background);
// }
void intro(SDL_Renderer* renderer) {
    Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "images/intro.png");
    int alpha = 255;
    bool isexit = false;
    SDL_Event e;

    while (alpha > 0 && !isexit) {
        // Обработка событий
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                isexit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        SDL_RenderClear(renderer);
        ShowEntity(renderer, background);
        SDL_RenderPresent(renderer);

        SDL_SetTextureBlendMode(background->text, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(background->text, alpha--);

        // Задержка перемещена в конец цикла
        SDL_Delay(1000. / fps);
    }

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    DestroyEntity(background);
}

void menu(SDL_Renderer* renderer){

    Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "images/backgroundMenu.png");
    Button* quitButton = CreateButton(renderer, (SDL_Rect){30, 260, 100, 50}, "images/quitButton.png","images/quitButton2.png");
    Button* startButton = CreateButton(renderer, (SDL_Rect){30, 160, 100, 50}, "images/startButton.png","images/startButton2.png");
    Button* settingsButton = CreateButton(renderer, (SDL_Rect){30, 210, 100, 50}, "images/settingsButton.png","images/settingsButton2.png");
    int mousecordsX = 0;
    int mousecordsY = 0;
    SDL_Event event;
    bool isexit = false;
    while(!isexit){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    isexit = true;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mousecordsX, &mousecordsY);
                    if(CheckButton(&(SDL_Point){mousecordsX, mousecordsY}, &quitButton->rect)){
                        isexit = true;
                        break;
                    }
                    if(CheckButton(&(SDL_Point){mousecordsX, mousecordsY}, &startButton->rect)){
                        isexit = true;
                        break;
                    }
                    if(CheckButton(&(SDL_Point){mousecordsX, mousecordsY}, &settingsButton->rect)){
                        isexit = true;
                        break;
                    }
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mousecordsX, &mousecordsY);
                    
                    if(CheckButton(&(SDL_Point){mousecordsX, mousecordsY}, &quitButton->rect)){
                        quitButton->state = STATE2;
                    }
                    else{
                        quitButton->state = STATE1;
                    }

                    if(CheckButton(&(SDL_Point){mousecordsX, mousecordsY}, &startButton->rect)){
                        startButton->state = STATE2;
                    }
                    else{
                        startButton->state = STATE1;
                    }
                    if(CheckButton(&(SDL_Point){mousecordsX, mousecordsY}, &settingsButton->rect)){
                        settingsButton->state = STATE2;
                    }
                    else{
                        settingsButton->state = STATE1;
                    }
                break;
            }
        }
        ShowEntity(renderer, background);
        ShowButton(renderer, quitButton);
        ShowButton(renderer, settingsButton);
        ShowButton(renderer, startButton);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000. / fps);
    }
    SDL_RenderPresent(renderer);
    DestroyEntity(background);
    DestroyButton(quitButton);
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