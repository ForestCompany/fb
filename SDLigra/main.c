#include "SecondLayerFunctions.h"
#include"EManager.h"
#include"SkillManager.h"




SDL_Renderer* renderer;
SDL_Window* window;

Uint32 lastUpdateTime = 0;



int main(int argc, char* arhs[]) {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();

    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    
    window = SDL_CreateWindow("Forest", 0, 0, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Map* map = CreateMap(renderer, SCREENHEIGHT / WIDTHTILE - 2, SCREENWIDTH / HEIGHTTILE);

    Person* TOLIK = CreatePerson(renderer, WIDTHTILE, HEIGHTTILE, WIDTHTILE, HEIGHTTILE, "../images/tolik.png");

    FillEnemyArr(renderer);
    FillSkillArr(renderer);

    
  
    Entity* hood = CreateEntity(renderer, 0, 864, 1920, 1080 - 864, "../images/hood.png");

    SDL_Color color = { 0,0,0,255 };

    bool iswin;


    bool cursor = false;

    SDL_Point mousecords;
    // Создаем текстуру для двойной буферизации
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
                    if (SkillArray[0]->state == ACTIVE) {
                        PressButton(SkillArray[0]);
                    }
                    break;
                case SDLK_w:
                    if (SkillArray[1]->state == ACTIVE && SkillArray[1]->manacost<=TOLIK->stats.mana) {
                        PressButton(SkillArray[1]);
                        DecrementMana(TOLIK, SkillArray[1]->manacost);
                        IncrementHP(TOLIK, 20);
                    }
                    break;
                case SDLK_e:
                    if (SkillArray[2]->state == ACTIVE) {
                        PressButton(SkillArray[2]);
                        DecrementMana(TOLIK, SkillArray[2]->manacost);
                        for (int i = 0; i < ENEMYCOUNT; i++) {
                            DecrementHP(EnemyArr[i], 1200);
                        }
                    }
                    break;
                
                }
                break;

            case SDL_MOUSEMOTION:
                cursor = false;
                SDL_GetMouseState(&mousecords.x, &mousecords.y);

                cursor = isnearperson(TOLIK, map, mousecords);
                if (cursor) {
                    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
                }
                else {
                    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
                }
                break;

            case SDL_MOUSEBUTTONDOWN: {
                SDL_GetMouseState(&mousecords.x, &mousecords.y);
                SDL_Point mapcord = { mousecords.y / WIDTHTILE, mousecords.x / HEIGHTTILE };

                typeoftile e = gettype(map, mapcord.x, mapcord.y,EnemyArr);

                if (isnearperson(TOLIK, map, mousecords)) {
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
                        Person* enemy = FindEnemy(mapcord.x, mapcord.y);
                        PVP(TOLIK, enemy);
                        break;
                    }
                }
                break;
            }
            }
        }
        UpdateSkillArr(renderer);
        // Очистка и отрисовка кадра на текстуре
        SDL_SetRenderTarget(renderer, bufferTexture);
        ShowMap(renderer, map);
        ShowPerson(renderer, TOLIK);
        ShowEnemyArr(renderer);
        ShowEntity(renderer, hood);
        ShowSkillArr(renderer);
        ShowFontStats(renderer,TOLIK, color);
        // Обновление экрана
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
            lastUpdateTime = currentTime; // Обновляем время последнего обновления
        }
        
        switch (IsWin()) {
            case true: {

            }
            case false: {

            }
        }
        /*
        if (IsWin() == true) {
            iswin = true;
            isexit = true;
        }*/
        SDL_Delay(1000./fps);
    }

    // Освобождаем ресурсы
    SDL_DestroyTexture(bufferTexture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    DestroyEnemyArr(EnemyArr);
    DestroyPerson(TOLIK);
    DestroyEntity(hood);
    DestroyMap(map);
    DetroySkillArr();
    SDL_Quit();
    IMG_Quit();
}