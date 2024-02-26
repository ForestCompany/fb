#include "../inc/SecondLayerFunctions.h"

bool IsMouseNearPerson(Person* p,  SDL_Point mousecords) {
    int P_X = GetX(p) / TILESIZE;
    int P_Y = GetY(p) / TILESIZE;
    mousecords.x = mousecords.x / TILESIZE;
    mousecords.y = mousecords.y / TILESIZE;
    bool isNearHorizontal = P_Y == mousecords.y && abs(mousecords.x - P_X) == 1; 
    bool isNearVertical = P_X == mousecords.x && abs(mousecords.y - P_Y ) == 1; 
    return  isNearHorizontal || isNearVertical;
}



void Game(SDL_Renderer *renderer)
{
    Mix_Chunk *footstepSound = Mix_LoadWAV("resource/sounds/Z.wav");

    int NOMERVRAGA = 0;
    Uint32 lastUpdateTime = 0;

    Map* map = CreateMap(renderer, SCREENHEIGHT / TILESIZE - 2, SCREENWIDTH / TILESIZE);

    Person* TOLIK = CreatePerson(renderer, TILESIZE, TILESIZE, TILESIZE, TILESIZE, "resource/images/tolik.png");
    Person* EnemyArr[ENEMYCOUNT];
    FillEnemyArr(renderer,EnemyArr);

    Skill* skil  = CreateSkill(renderer,(SDL_Rect){XTABSKILL,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE}, "resource/images/sword.jpg","resource/images/swordBLACK.jpg", 5000, 35);
    Skill* skil1 = CreateSkill(renderer,(SDL_Rect){XTABSKILL1,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE}, "resource/images/heal.jpg", "resource/images/healBLACK.jpg", 10000, 35);
    Skill* skil2 = CreateSkill(renderer,(SDL_Rect){XTABSKILL2,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE}, "resource/images/ulta.jpg", "resource/images/ultaBLACK.jpg", 15000, 30);


    card_t *card1 = CreateCard(renderer, XTABCARD, YTABCARD, WIDTHCARD, HEIGHTCARD, "resource/images/karta.jpg");
    card_t *card2 = CreateCard(renderer, XTABCARD + WIDTHCARD, YTABCARD, WIDTHCARD, HEIGHTCARD, "resource/images/karta.jpg");
    card_t *card3 = CreateCard(renderer, XTABCARD + WIDTHCARD * 2, YTABCARD, WIDTHCARD, HEIGHTCARD, "resource/images/karta.jpg");
    bool PointedKarta = false;
    //Item *item1 = CreateItem(renderer, "item1", TILESIZE * 5, TILESIZE * 5, TILESIZE, TILESIZE, "images/Victoryscreen.png", 1, 1, 1, 1);
    Entity* hood = CreateEntity(renderer, 0, TILESIZE*HEIGHTAMOUNT, SCREENWIDTH, SCREENHEIGHT - (TILESIZE*HEIGHTAMOUNT), "resource/images/hood.png");

    SDL_Color color = { 0,0,0,255 };




    bool cursor = false;
    bool poshel = false;
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
                        if(skil->b->state == STATE1 && TOLIK->stats.mana>= skil->manacost) {
                            PressSkill(skil);
                            DecrementHP(TOLIK,25);
                            DecrementMana(TOLIK,skil->manacost);
                        }
                    break;
                case SDLK_w:
                    if(skil1->b->state == STATE1 && TOLIK->stats.mana>= skil1->manacost) {
                            PressSkill(skil1);
                            IncrementHP(TOLIK,25);
                            DecrementMana(TOLIK,skil1->manacost);
                        }
                    break;
                case SDLK_e:
                    if(skil2->b->state == STATE1 && TOLIK->stats.mana>= skil2->manacost) {
                            PressSkill(skil2);
                            DecrementMana(TOLIK,skil2->manacost);
                            for(int i = 0; i<ENEMYCOUNT;i++) {
                                DecrementHP(EnemyArr[i],0.6*EnemyArr[i]->stats.hp);
                            }
                        }
                    break;
                case SDLK_9:
                      Mix_PlayChannel(-1, footstepSound, 0);
                }
                break;

            case SDL_MOUSEMOTION:
                cursor = false;
                SDL_GetMouseState(&mousecords.x, &mousecords.y);

                cursor = IsMouseNearPerson(TOLIK, mousecords);
                if (cursor) {
                    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
                }
                else {
                    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
                }
                CheckPointed(card1, skil, mousecords);
                CheckPointed(card2, skil1, mousecords);
                CheckPointed(card3, skil2, mousecords);
                break;

            case SDL_MOUSEBUTTONDOWN: {
                SDL_GetMouseState(&mousecords.x, &mousecords.y);
                SDL_Point mapcord = { mousecords.y / TILESIZE, mousecords.x / TILESIZE };
             
                typeoftile e = GetType(map,mapcord,EnemyArr);

                if (IsMouseNearPerson(TOLIK,  mousecords)) {
                    switch (e) {
                    case GRASS:
                        printf("GRASS\n");
                        TOLIK->soul->rect.x = map->map[mapcord.y][mapcord.x].soul->rect.x;
                        TOLIK->soul->rect.y = map->map[mapcord.y][mapcord.x].soul->rect.y;
                        Mix_PlayChannel(-1, footstepSound, 0);
                   
                        break;

                    case MOUNTAIN:
                        printf("MOUNTAIN\n");
                        break;

                    case ENEMY:
                        printf("ENEMY\n");
                        Person* enemy = FindEnemy(mapcord,EnemyArr);
                        PVP(TOLIK, enemy);
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
        if (SDL_GetTicks() - lastUpdateTime >= 500) {
            AIEnemy(EnemyArr, TOLIK);
            lastUpdateTime = SDL_GetTicks();
        }
        if (SDL_GetTicks() - lastUpdateTime >= 1000 && NOMERVRAGA < 6) {
            EnemyArr[NOMERVRAGA++]->alive = true;
            lastUpdateTime = SDL_GetTicks();
        }
        SDL_SetRenderTarget(renderer, bufferTexture);
        ShowMap(renderer, map);
        ShowPerson(renderer, TOLIK);
        ShowEntity(renderer, hood);
        ShowEnemyArr(renderer,EnemyArr);
        ShowCard(renderer, card1);
        ShowCard(renderer, card2);
        ShowCard(renderer, card3);
        ShowSkill(renderer,skil);
        ShowSkill(renderer,skil1);
        ShowSkill(renderer,skil2);
        
        ShowFontStats(renderer,TOLIK, color);
      
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
        SDL_RenderPresent(renderer);


        
      
        SDL_Delay(1000./fps);
    }

 
    SDL_DestroyTexture(bufferTexture);
    DestroyPerson(TOLIK);
    DestroyEntity(hood);
    DestroyMap(map);
    DestroyEnemyArr(EnemyArr);
    DestroyCard(card1);
    DestroyCard(card2);
    DestroyCard(card3);
    DestroySkill(skil);
    DestroySkill(skil1);
    DestroySkill(skil2);

}




void intro(SDL_Renderer* renderer) {
    Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "resource/images/intro.png");
    int alpha = 255;
    bool isexit = false;
    SDL_Event x;

    while (alpha > 0 && !isexit) {
        // Обработка событий
        while (SDL_PollEvent(&x)) {
            if (x.type == SDL_KEYDOWN) {
                isexit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        SDL_RenderClear(renderer);
        ShowEntity(renderer, background);
        SDL_RenderPresent(renderer);

        SDL_SetTextureBlendMode(background->text, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(background->text, alpha--);

   
        SDL_Delay(1000. / fps);
    }

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    DestroyEntity(background);
}

typeoftile GetType(Map *map, SDL_Point mouse, Person *EnemyArr[ENEMYCOUNT])
{
    
    for(int i = 0;i<ENEMYCOUNT;i++){
        int EnemyX = EnemyArr[i]->soul->rect.y / TILESIZE;
        int EnemyY = EnemyArr[i]->soul->rect.x / TILESIZE;
        if (mouse.x == EnemyX && mouse.y == EnemyY && EnemyArr[i]->alive == true) {
            return ENEMY;
        }
    }
    return GetTypeOFTile(&map->map[mouse.y][mouse.x]);
}









