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

int Game(SDL_Renderer *renderer, int N_Voln)
{
    Mix_Chunk* footstepSound = Mix_LoadWAV("resource/sounds/movement.wav");
    Mix_Chunk* Healskill = Mix_LoadWAV("resource/sounds/healSkill.wav");
    Mix_Chunk* Hit = Mix_LoadWAV("resource/sounds/hit.wav");
    Mix_Chunk* Swordskill = Mix_LoadWAV("resource/sounds/swordSkill.wav");
    Mix_Chunk* Ultimateskill = Mix_LoadWAV("resource/sounds/ultimateSkill.wav");
    Mix_Chunk* Nomana = Mix_LoadWAV("resource/sounds/nomana.wav");
    Mix_Music* music = Mix_LoadMUS("resource/sounds/fightMusic.wav");
    Uint32 income = 0;
    Mix_VolumeMusic(5);
    Mix_VolumeChunk(footstepSound, 5);
    Mix_VolumeChunk(Healskill, 5);
    Mix_VolumeChunk(Hit, 5);
    Mix_VolumeChunk(Swordskill, 5);
    Mix_VolumeChunk(Ultimateskill, 5);
    Mix_VolumeChunk(Nomana, 5);
    Uint32 lasttimerAI = 0;
    Uint32 skillaction = 0;
    bool pressed = false;
    wave_t wave = {0,6,0,false,N_Voln};

    int res = -1;
    Uint32 lastUpdateTime = 0;

    Map* map = CreateMap(renderer, SCREENHEIGHT / TILESIZE - 2, SCREENWIDTH / TILESIZE);

    Person* TOLIK = CreatePerson(renderer, TILESIZE, TILESIZE, TILESIZE, TILESIZE, "resource/images/tolik.png");
    SetFullStats(TOLIK, 7,7,15,50);

    Person* EnemyArr[ENEMYCOUNT];
    FillEnemyArr(renderer,EnemyArr);

    Skill* skil  = CreateSkill(renderer,(SDL_Rect){XTABSKILL,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE}, "resource/images/sword.jpg","resource/images/swordBLACK.jpg", 5000, 35);
    Skill* skil1 = CreateSkill(renderer,(SDL_Rect){XTABSKILL1,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE}, "resource/images/heal.jpg", "resource/images/healBLACK.jpg", 10000, 35);
    Skill* skil2 = CreateSkill(renderer,(SDL_Rect){XTABSKILL2,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE}, "resource/images/ulta.jpg", "resource/images/ultaBLACK.jpg", 20000, 30);

    
    card_t *card1 = CreateCard(renderer, XTABCARD, YTABCARD, WIDTHCARD, HEIGHTCARD, "resource/images/swordKARTA.png");
    card_t *card2 = CreateCard(renderer, XTABCARD + WIDTHCARD, YTABCARD, WIDTHCARD, HEIGHTCARD, "resource/images/healKARTA.png");
    card_t *card3 = CreateCard(renderer, XTABCARD + WIDTHCARD * 2, YTABCARD, WIDTHCARD, HEIGHTCARD, "resource/images/ultaKARTA.png");

    //Item *item1 = CreateItem(renderer, "item1", TILESIZE * 5, TILESIZE * 5, TILESIZE, TILESIZE, "images/Victoryscreen.png", 1, 1, 1, 1);
    Entity* hood = CreateEntity(renderer, 0, TILESIZE*HEIGHTAMOUNT, SCREENWIDTH, SCREENHEIGHT - (TILESIZE*HEIGHTAMOUNT), "resource/images/hood.png");

    SDL_Color color = { 0,0,0,255 };


    Mix_PlayMusic(music, -1);


    bool cursor = false;
    SDL_Point mousecords;

    SDL_Texture* bufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREENWIDTH, SCREENHEIGHT);
    SDL_SetRenderTarget(renderer, bufferTexture);
    SDL_Event e;

    bool isexit = false;

    while (!isexit) {
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                case SDLK_q:
                        if(skil->b->state == STATE1 && TOLIK->stats.mana>= skil->manacost) {
                            PressSkill(skil);
                            DecrementMana(TOLIK,skil->manacost);
                            skillaction = SDL_GetTicks();
                            TOLIK->stats.damage += 40;
                            pressed = true;
                            Mix_PlayChannel(-1, Swordskill, 0);
                        }
                    else {
                        Mix_PlayChannel(-1, Nomana, 0);
                    }
                    break;
                case SDLK_w:
                    if(skil1->b->state == STATE1 && TOLIK->stats.mana>= skil1->manacost) {
                            PressSkill(skil1);
                            IncrementHP(TOLIK,25);
                            DecrementMana(TOLIK,skil1->manacost);
                            Mix_PlayChannel(-1, Healskill, 0);
                        }
                    else {
                        Mix_PlayChannel(-1, Nomana, 0);
                    }
                    break;
                case SDLK_e:
                    if(skil2->b->state == STATE1 && TOLIK->stats.mana>= skil2->manacost) {
                            PressSkill(skil2);
                            DecrementMana(TOLIK,skil2->manacost);
                            for(int i = 0; i<ENEMYCOUNT;i++) {
                                DecrementHP(EnemyArr[i],0.6*EnemyArr[i]->stats.power->cap);
                            }
                            Mix_PlayChannel(-1, Ultimateskill, 0);
                        }
                    else {
                        Mix_PlayChannel(-1, Nomana, 0);
                    }
                    break;
                case SDLK_9:
                      DecrementHP(TOLIK, TOLIK->stats.hp);
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
                        Mix_PlayChannel(-1, Hit, 0);
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

        UpdateGame(&wave, EnemyArr, TOLIK, &lastUpdateTime, &lasttimerAI);
        if (SDL_GetTicks() - income >= 1000) {
            IncrementMana(TOLIK, 5);
            IncrementHP(TOLIK, 5);
            income = SDL_GetTicks();
        }
        if (SDL_GetTicks() - skillaction >= 5000 && pressed) {
                    TOLIK->stats.damage -= 40;
                    pressed = false;
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

        if (TOLIK->stats.hp < 1) {
            res = 0;
            isexit = true;
        }
        else if (IsDead(EnemyArr) && wave.waveCounter == N_Voln) {
            res = 1;
            isexit = true;
        }
      
        SDL_Delay(1000./fps);
    }
    Mix_FreeChunk(Healskill);
    Mix_FreeMusic(music);
    Mix_FreeChunk(footstepSound);
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
    return res;
}

void intro(SDL_Renderer* renderer) {
    Button* intro = CreateButton(renderer, (SDL_Rect){INTRO_X, INTRO_Y, INTRO_WIDTH, INTRO_HEIGHT}, 
                    "resource/images/intro1.png", "resource/images/intro2.png");
                    
    int alpha = 0;
    bool isexit = false;
    SDL_Event event;
    Uint32 startTime = SDL_GetTicks();
    while (!isexit) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                isexit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        SDL_SetTextureBlendMode(intro->state1, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(intro->state1, alpha++);

        if (alpha == 255) {
            intro->state = STATE2;
        }
        
        if (SDL_GetTicks() - startTime >= 6200) {
            isexit = true;
        }
        ShowButton(renderer, intro);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000. / fps);
    }

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    DestroyButton(intro);
}


int menu(SDL_Renderer* renderer) {

    Mix_Music* music = Mix_LoadMUS("resource/sounds/menu.wav");
    Mix_Chunk* buttonSound = Mix_LoadWAV("resource/sounds/buttonSound.wav");
    Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "resource/images/backgroundMenu.png");

    Button* startButton = CreateButton(renderer, (SDL_Rect){
                                SCREENWIDTH * BUTTON_X_RATIO,
                                SCREENHEIGHT * BUTTON_Y_START_RATIO,
                                SCREENWIDTH * BUTTON_WIDTH_RATIO,
                                SCREENHEIGHT * BUTTON_HEIGHT_RATIO},
                            "resource/images/startButton.png","resource/images/startButton2.png");

    Button* quitButton = CreateButton(renderer, (SDL_Rect){
                                SCREENWIDTH * BUTTON_X_RATIO,
                                SCREENHEIGHT * BUTTON_Y_QUIT_RATIO,
                                SCREENWIDTH * BUTTON_WIDTH_RATIO,
                                SCREENHEIGHT * BUTTON_HEIGHT_RATIO},
                            "resource/images/quitButton.png","resource/images/quitButton2.png");

    Mix_VolumeMusic(10);
    Mix_VolumeChunk(buttonSound, 100);
    Mix_PlayMusic(music, -1);

    Button* buttonArray[] = {
        startButton,
        quitButton
    };

    int index = -1;
    int numButtons = sizeof(buttonArray) / sizeof(buttonArray[0]);
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
                            if (!buttonArray[i]->playedSound) { 
                                Mix_PlayChannel(-1, buttonSound, 0);
                                buttonArray[i]->playedSound = true;
                            }
                            buttonArray[i]->state = STATE2;
                            
                        } else {
                            buttonArray[i]->state = STATE1;
                            buttonArray[i]->playedSound = false;
                        }
                    }
                    break;
            }
        }

        ShowEntity(renderer, background);
        for (int i = 0; i < numButtons; i++) {
            ShowButton(renderer, buttonArray[i]);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000. / fps);
    }

    for (int i = 0; i < numButtons; i++) {
        DestroyButton(buttonArray[i]);
    }

    Mix_PauseMusic();
    Mix_FreeMusic(music);
    Mix_FreeChunk(buttonSound);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    DestroyEntity(background);
    return index;
}

int ChooseDifficulty(SDL_Renderer* renderer) {

    Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "resource/images/defaultScreen.png");
    
    Mix_Chunk* buttonSound = Mix_LoadWAV("resource/sounds/buttonSound.wav");

    SDL_Texture* textureArray[] = {
        CreateTextureFromImg(renderer,"resource/images/babyScreen.png"),
        CreateTextureFromImg(renderer, "resource/images/mediumScreen.png"),
        CreateTextureFromImg(renderer,"resource/images/hardScreen.png"),
        CreateTextureFromImg(renderer, "resource/images/defaultScreen.png")
    };

    Button* hardButton = CreateButton(renderer, (SDL_Rect){
                                STARTX,
                                STARTY,
                                BUTTONWIDTH,
                                BUTTONHEIGHT},
                                "resource/images/hardButton1.png", "resource/images/hardButton2.png");

    Button* mediumButton = CreateButton(renderer, (SDL_Rect){
                                STARTX,
                                STARTY + BUTTONHEIGHT + buttonSpacing,
                                BUTTONWIDTH,
                                BUTTONHEIGHT},
                                "resource/images/mediumButton1.png", "resource/images/mediumButton2.png");

    Button* babyButton = CreateButton(renderer, (SDL_Rect){
                                STARTX,
                                STARTY + 2 * (BUTTONHEIGHT + buttonSpacing),
                                BUTTONWIDTH,
                                BUTTONHEIGHT},
                                "resource/images/babyButton1.png", "resource/images/babyButton2.png");

    Button* buttonArray[] = {
        babyButton,
        mediumButton,
        hardButton
    };
    Mix_VolumeChunk(buttonSound, 100);
    int index = -1;
    int numButtons = sizeof(buttonArray) / sizeof(buttonArray[0]);
    int mouseX = 0;
    int mouseY = 0;
    SDL_Event event;
    bool exitLoop = false;

    while (!exitLoop) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    for (int i = 0; i < numButtons; ++i) {
                        if (CheckButton(&(SDL_Point){mouseX, mouseY}, &buttonArray[i]->rect)) {
                            index = i;
                            exitLoop = true;
                            break;
                        }
                    }
                    break;

                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    bool buttonHovered = false;
                    for (int i = 0; i < numButtons; ++i) {
                        if (CheckButton(&(SDL_Point){mouseX, mouseY}, &buttonArray[i]->rect)) {
                            if (!buttonArray[i]->playedSound) { 
                                Mix_PlayChannel(-1, buttonSound, 0);
                                buttonArray[i]->playedSound = true;
                            }
                            background->text = textureArray[i];
                            buttonArray[i]->state = STATE2;
                            buttonHovered = true;
                        } else {
                            buttonArray[i]->state = STATE1;
                            buttonArray[i]->playedSound = false;
                        }
                    }
                    if (!buttonHovered)
                        background->text = textureArray[3];
                        
                    break;
            }
        }
        ShowEntity(renderer, background);
        for (int i = 0; i < numButtons; i++) {
            ShowButton(renderer, buttonArray[i]);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000.0 / fps);
    }

    DestroyEntity(background);
    for (int i = 0; i < 4; i++) {
        SDL_DestroyTexture(textureArray[i]);
    }

    for (int i = 0; i < numButtons; i++) {
        DestroyButton(buttonArray[i]);
    }

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    printf("%d\n", (index + 1) *3 );
    return (index + 1) * 3;
}


void outroWin(SDL_Renderer* renderer) {
    Mix_Music* music = Mix_LoadMUS("resource/sounds/outrowin.wav");
    Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "resource/images/winscreen.png");
    bool isexit = false;
    SDL_Event event;
    Uint32 startTime = SDL_GetTicks();

    Mix_VolumeMusic(10);
    Mix_PlayMusic(music, 1);

    while (!isexit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                isexit = true;
            }
        }
        if (SDL_GetTicks() - startTime >= 10000) {
            isexit = true;
        }
        ShowEntity(renderer, background);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000. / fps);
    }
    Mix_FreeMusic(music);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    DestroyEntity(background);
}

int outroLoose(SDL_Renderer* renderer) {

    Mix_Music* music = Mix_LoadMUS("resource/sounds/outroloose.wav");
    Entity* background = CreateEntity (renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "resource/images/deathscreen.png");
    Uint32 startTime = SDL_GetTicks();
    Mix_VolumeMusic(10);
    Mix_PlayMusic(music, 1);

    bool isexit = false;
    int index = -1;
    SDL_Event event;

    while (!isexit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                isexit = true;
            }
        }
        if (SDL_GetTicks() - startTime >= 8000) {
            isexit = true;
        }
        ShowEntity(renderer, background);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000. / fps);
    }
    Mix_FreeMusic(music);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    DestroyEntity(background);

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









