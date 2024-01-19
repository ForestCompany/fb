#include "SecondLayerFunctions.h"




 SDL_Renderer* renderer;
 SDL_Window* window;

int main(int argc, char* argv[]) 
{
	SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();


    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));

    window = SDL_CreateWindow("Forest", 0, 0, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED  );//| SDL_RENDERER_PRESENTVSYNC

	Uint32 lastUpdateTime = 0;

    Map* map = CreateMap(renderer, SCREENHEIGHT / TILESIZE - 2, SCREENWIDTH / TILESIZE);

    Person* TOLIK = CreatePerson(renderer, TILESIZE, TILESIZE, TILESIZE, TILESIZE, "images/tolik.png");

    // Person** EnemyArr = FillEnemyArr(renderer);
    // FillSkillArr(renderer);
    Skill* skil = CreateSkill(renderer,(SDL_Rect){XTABSKILL,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE},"images/sword.jpg","images/swordBLACK.jpg",5000,35);
    Skill* skil1 = CreateSkill(renderer,(SDL_Rect){XTABSKILL+60,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE},"images/sword.jpg","images/swordBLACK.jpg",5000,35);
    Skill* skil2 = CreateSkill(renderer,(SDL_Rect){XTABSKILL+60*2,YTABSKILL+TILESIZE*HEIGHTAMOUNT,SKILLSIZE,SKILLSIZE},"images/sword.jpg","images/swordBLACK.jpg",5000,35);

  //1231231231231231213
    Entity* hood = CreateEntity(renderer, 0, TILESIZE*HEIGHTAMOUNT, SCREENWIDTH, SCREENHEIGHT - (TILESIZE*HEIGHTAMOUNT), "images/hood.png");

    SDL_Color color = { 0,0,0,255 };




    bool cursor = false;

    SDL_Point mousecords;
    // ������� �������� ��� ������� �����������
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
                    // if (SkillArray[0]->state == ACTIVE) {
                    //     PressSkill(SkillArray[0]);
                    // }

                        if(skil->state == ACTIVE && TOLIK->stats.mana>= skil->manacost){
                            PressSkill(skil);
                            DecrementHP(TOLIK,25);
                            DecrementMana(TOLIK,skil->manacost);
                        }
                    break;
                case SDLK_w:
                    if(skil1->state == ACTIVE && TOLIK->stats.mana>= skil1->manacost){
                            PressSkill(skil1);
                            DecrementHP(TOLIK,25);
                            DecrementMana(TOLIK,skil1->manacost);
                        }
                    break;
                case SDLK_e:
                    if(skil2->state == ACTIVE&& TOLIK->stats.mana>= skil2->manacost){
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
             
                typeoftile e = GetType(&(map->map[mapcord.y][mapcord.x]));

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
        // ������� � ��������� ����� �� ��������
        SDL_SetRenderTarget(renderer, bufferTexture);
        ShowMap(renderer, map);
        ShowPerson(renderer, TOLIK);
        // ShowEnemyArr(renderer,EnemyArr);
        ShowEntity(renderer, hood);
        // ShowSkillArr(renderer);
        ShowSkill(renderer,skil);
        ShowSkill(renderer,skil1);
        ShowSkill(renderer,skil2);
        ShowFontStats(renderer,TOLIK, color);
        // ���������� ������
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
            lastUpdateTime = currentTime; // ��������� ����� ���������� ����������
        }
        
      
        SDL_Delay(1000./fps);
    }

    // ����������� �������
    SDL_DestroyTexture(bufferTexture);
    // DestroyEnemyArr(EnemyArr);
    DestroyPerson(TOLIK);
    DestroyEntity(hood);
    DestroyMap(map);
    // DetroySkillArr();
    DestroySkill(skil);
    DestroySkill(skil1);
    DestroySkill(skil2
    );
	SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();

	return 1;
}