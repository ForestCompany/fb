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

//123123123


SDL_Texture* CreateTextureFromImg(SDL_Renderer* renderer, const char* path);

SDL_Texture* CreateTextureFromFont(SDL_Renderer* renderer, char text[5], const char* font, int fontsize, SDL_Color color);

SDL_Rect CreateRect(int x, int y, int width, int height);

int getwidth(int hp, int cap, int width);



#endif // FUNCTIONS_H