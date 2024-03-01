#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_mouse.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>

#define ASPECT 100.
#define SCREENWIDTH (1600 / (ASPECT / 100))
#define SCREENHEIGHT (900 / (ASPECT / 100))
#define fps 60 
#define WIDTHAMOUNT 20
#define HEIGHTAMOUNT 9
#define TILESIZE (SCREENWIDTH/WIDTHAMOUNT)
#define HDXTAB 323
#define HDYHPTAB 33
#define HDYMANATAB 87
#define HDWIDTHBAR 350
#define HDHEIGHTBAR 35 
#define HEIGHTBAR (HDHEIGHTBAR * SCREENHEIGHT / 1080)
#define WIDTHBAR (HDWIDTHBAR * SCREENWIDTH / 1920)
#define XTABFORBAR  (HDXTAB*SCREENWIDTH/1920)
#define YTABFORHPBAR (HDYHPTAB*SCREENHEIGHT/1080)
#define YTABFORHPMANA (HDYMANATAB * SCREENHEIGHT/1080)
#define HDSKILLSIZE 73
#define HDXTABSKILL 792
#define XTABSKILL ( HDXTABSKILL * SCREENWIDTH / 1920) 
#define HDYTABSKILL 120
#define YTABSKILL (HDYTABSKILL * SCREENHEIGHT / 1080)
#define SKILLSIZE (HDSKILLSIZE * SCREENHEIGHT/1080)
#define HDYARMORTAB 158
#define YARMORTAB (HDYARMORTAB * SCREENHEIGHT / 1080)

#define HDXTABSKILL1 962
#define HDXTABSKILL2 1132
#define XTABSKILL1 ( HDXTABSKILL1 * SCREENWIDTH / 1920) 
#define XTABSKILL2 ( HDXTABSKILL2 * SCREENWIDTH / 1920) 

#define HDYTABSLOT 92
#define HDXTABSLOT1 1322
#define HDXTABSLOT2 1419
#define HDXTABSLOT3 1514
#define HDXTABSLOT4 1609
#define HDXTABSLOT5 1703
#define HDXTABSLOT6 1793

#define YTABSLOT  (HDYTABSLOT * SCREENHEIGHT / 1080)
#define XTABSLOT1 (HDXTABSLOT1 * SCREENWIDTH / 1920)
#define XTABSLOT2 (HDXTABSLOT2 * SCREENWIDTH / 1920)
#define XTABSLOT3 (HDXTABSLOT3 * SCREENWIDTH / 1920)
#define XTABSLOT4 (HDXTABSLOT4 * SCREENWIDTH / 1920)
#define XTABSLOT5 (HDXTABSLOT5 * SCREENWIDTH / 1920)
#define XTABSLOT6 (HDXTABSLOT6 * SCREENWIDTH / 1920)

#define HDWIDTHSLOT1 93
#define HDWIDTHSLOT2 90
#define HDWIDTHSLOT3 89
#define HDWIDTHSLOT4 89
#define HDWIDTHSLOT5 91
#define HDWIDTHSLOT6 92


#define WIDTHSLOT1 (HDWIDTHSLOT1 * SCREENWIDTH / 1920)
#define WIDTHSLOT2 (HDWIDTHSLOT2 * SCREENWIDTH / 1920)
#define WIDTHSLOT3 (HDWIDTHSLOT3 * SCREENWIDTH / 1920)
#define WIDTHSLOT4 (HDWIDTHSLOT4 * SCREENWIDTH / 1920)
#define WIDTHSLOT5 (HDWIDTHSLOT5 * SCREENWIDTH / 1920)
#define WIDTHSLOT6 (HDWIDTHSLOT6 * SCREENWIDTH / 1920)

#define HDHEIGHTSLOT 98
#define HEIGHTSLOT (HDHEIGHTSLOT * SCREENHEIGHT / 1080)
//123123123

//FOR INTRO
#define INTRO_WIDTH (SCREENWIDTH / 3)
#define INTRO_HEIGHT (SCREENHEIGHT / 3)
#define INTRO_X ((SCREENWIDTH - INTRO_WIDTH) / 2)
#define INTRO_Y ((SCREENHEIGHT - INTRO_HEIGHT) / 2)

//FOR BUTTONS IN MENU
#define BUTTON_WIDTH_RATIO 0.17  // Відсоток ширини екрану для кнопки
#define BUTTON_HEIGHT_RATIO 0.063 // Відсоток висоти екрану для кнопки
#define BUTTON_X_RATIO 0.78125  // Відсоток від лівого краю екрану для кнопки "start"
#define BUTTON_Y_START_RATIO 0.5222 // Відсоток від верхнього краю екрану для кнопки "start"
#define BUTTON_Y_QUIT_RATIO 0.6444 // Відсоток від верхнього краю екрану для кнопки "quit"

//FOR BUTTONS IN CHOOSEDIFFICULTY
#define buttonSpacing 25
#define BUTTONWIDTH (SCREENWIDTH * BUTTON_WIDTH_RATIO)
#define BUTTONHEIGHT (SCREENHEIGHT * BUTTON_HEIGHT_RATIO)
#define totalButtonHeight (3 * BUTTONHEIGHT + 2 * buttonSpacing)
#define STARTY ((SCREENHEIGHT - totalButtonHeight) / 2)
#define STARTX ((SCREENWIDTH - BUTTONWIDTH) / 2)


SDL_Texture* CreateTextureFromImg(SDL_Renderer* renderer, const char* path);

SDL_Texture* CreateTextureFromFont(SDL_Renderer* renderer, char text[5], const char* font, int fontsize, SDL_Color color);

SDL_Rect CreateRect(int x, int y, int width, int height);

int getwidth(int hp, int cap, int width);



#endif // FUNCTIONS_H






