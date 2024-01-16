#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdbool.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>


#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080
#define fps 144
#define WIDTHTILE 96
#define HEIGHTTILE 96


SDL_Texture* CreateTextureFromImg(SDL_Renderer* renderer, const char* path);

SDL_Texture* CreateTextureFromFont(SDL_Renderer* renderer, char text[5], const char* font, int fontsize, SDL_Color color);

SDL_Rect CreateRect(int x, int y, int width, int height);

int getwidth(int hp, int cap, int width);



#endif // FUNCTIONS_H