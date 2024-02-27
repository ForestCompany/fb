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
    Uint32 lasttimerAI = 0;
    int NOMERVRAGA = 0;

    Uint32 lastUpdateTime = 0;

    Map* map = CreateMap(renderer, SCREENHEIGHT / TILESIZE - 2, SCREENWIDTH / TILESIZE);

    Person* TOLIK = CreatePerson(renderer, TILESIZE, TILESIZE, TILESIZE, TILESIZE, "resource/images/tolik.png");
    Person* EnemyArr[ENEMYCOUNT];
    FillEnemyArr(renderer,EnemyArr);

    Skill* skil  = CreateSkill(renderer,(SDL_Rect){XTABSKILL,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE}, "resource/images/sword.jpg","resource/images/swordBLACK.jpg", 5000, 35);
    Skill* skil1 = CreateSkill(renderer,(SDL_Rect){XTABSKILL1,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE}, "resource/images/heal.jpg", "resource/images/healBLACK.jpg", 10000, 35);
    Skill* skil2 = CreateSkill(renderer,(SDL_Rect){XTABSKILL2,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE}, "resource/images/ulta.jpg", "resource/images/ultaBLACK.jpg", 1500000, 30);

    
    card_t *card1 = CreateCard(renderer, XTABCARD, YTABCARD, WIDTHCARD, HEIGHTCARD, "resource/images/Exit.png");
    card_t *card2 = CreateCard(renderer, XTABCARD + WIDTHCARD, YTABCARD, WIDTHCARD, HEIGHTCARD, "resource/images/Exit.png");
    card_t *card3 = CreateCard(renderer, XTABCARD + WIDTHCARD * 2, YTABCARD, WIDTHCARD, HEIGHTCARD, "resource/images/Exit.png");
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
        if (SDL_GetTicks() - lasttimerAI >= 1000) {
            AIEnemy(EnemyArr, TOLIK);
            lasttimerAI = SDL_GetTicks();
        }
        if (SDL_GetTicks() - lastUpdateTime >= 5000 && NOMERVRAGA < 6) {
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

int menu(SDL_Renderer* renderer) {

    Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "resource/images/backgroundMenu.png");
    Button* startButton = CreateButton(renderer, (SDL_Rect){BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT}, "resource/images/startButton.png","resource/images/startButton2.png");
    Button* settingsButton = CreateButton(renderer, (SDL_Rect){BUTTON_X, BUTTON_Y + BUTTON_HEIGHT + BUTTON_Y_PADDING_PERCENTAGE, BUTTON_WIDTH, BUTTON_HEIGHT}, "resource/images/settingsButton.png","resource/images/settingsButton2.png");
    Button* quitButton = CreateButton(renderer, (SDL_Rect){BUTTON_X, BUTTON_Y + 2 * (BUTTON_HEIGHT + BUTTON_Y_PADDING_PERCENTAGE), BUTTON_WIDTH, BUTTON_HEIGHT}, "resource/images/quitButton.png","resource/images/quitButton2.png");
    Button* buttonArray[] = {
        startButton,
        settingsButton,
        quitButton
    };
    int index = -1;
    int numButtons = 3;
    int mouseCordsX = 0;
    int mouseCordsY = 0;
    SDL_Event event;
    bool isexit = false;
    while(!isexit){
        while(SDL_PollEvent(&event)){
            switch(event.type) {
                case SDL_QUIT:
                    isexit = true;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseCordsX, &mouseCordsY);
                    for (int i = 0; i < numButtons; ++i) {
                        if (CheckButton(&(SDL_Point){mouseCordsX, mouseCordsY}, &buttonArray[i]->rect)) {
                            isexit = true;
                            index = i;
                            break;
                        }
                    }
                    break;

                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouseCordsX, &mouseCordsY);
                    for (int i = 0; i < numButtons; ++i) {
                        if (CheckButton(&(SDL_Point){mouseCordsX, mouseCordsY}, &buttonArray[i]->rect)) {
                            buttonArray[i]->state = STATE2;
                        } else {
                            buttonArray[i]->state = STATE1;
                        }
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

    for (int i = 0; i < numButtons; i++) {
        DestroyButton(buttonArray[i]);
    }
    
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    DestroyEntity(background);
    return index;
}

void outroWin(SDL_Renderer* renderer) {
    Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "resource/images/Victoryscreen.png");
    bool isexit = false;
    SDL_Event event;
    Uint32 startTime = SDL_GetTicks();

    while (!isexit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                isexit = true;
            }
        }
        if (SDL_GetTicks() - startTime >= 5000) {
            isexit = true;
        }
        ShowEntity(renderer, background);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000. / fps);
    }
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    DestroyEntity(background);
}   

int outroLoose(SDL_Renderer* renderer) {
    Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "resource/images/deathscreen.png");
    Button* menuButton = CreateButton(renderer, (SDL_Rect){550, 750, BUTTON_WIDTH, BUTTON_HEIGHT}, "resource/images/menuButton.png", "resource/images/menuButton2.png");
    Button* retryButton = CreateButton(renderer, (SDL_Rect){1200, 750, BUTTON_WIDTH, BUTTON_HEIGHT}, "resource/images/retryButton.png", "resource/images/retryButton2.png");
    Button* buttonArray[] = {
        menuButton,
        retryButton
    };

    bool isexit = false;
    int index = -1;
    int numButtons = sizeof(buttonArray) / sizeof(buttonArray[0]);
    SDL_Event event;

    int mouseCordsX = 0;
    int mouseCordsY = 0;

    while (!isexit) {
        while(SDL_PollEvent(&event)){
            switch(event.type) {
                case SDL_QUIT:
                    isexit = true;
                    break;
        
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseCordsX, &mouseCordsY);
                    for (int i = 0; i < numButtons; ++i) {
                        if (CheckButton(&(SDL_Point){mouseCordsX, mouseCordsY}, &buttonArray[i]->rect)) {
                            isexit = true;
                            index = i;
                            break;
                        }
                    }
                    break;

                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouseCordsX, &mouseCordsY);
                    for (int i = 0; i < numButtons; ++i) {
                        if (CheckButton(&(SDL_Point){mouseCordsX, mouseCordsY}, &buttonArray[i]->rect)) {
                            buttonArray[i]->state = STATE2;
                        } else {
                            buttonArray[i]->state = STATE1;
                        }
                    }
                    break;
            }
        }
        ShowEntity(renderer, background);
        ShowButton(renderer, menuButton);
        ShowButton(renderer, retryButton);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000. / fps);
    }
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    DestroyEntity(background);
    DestroyButton(menuButton);
    DestroyButton(retryButton);
    return index;
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









