#include "Skill.h"
#ifndef CARD_H
#define CARD_H
#define HDXTABCARD 730
#define HDYTABCARD 575
#define HDWIDTHCARD 180
#define HDHEIGTHCARD 360
#define XTABCARD (HDXTABCARD * SCREENWIDTH / 1920)
#define YTABCARD (HDYTABCARD * SCREENHEIGHT / 1080)
#define WIDTHCARD (HDWIDTHCARD * SCREENWIDTH / 1920)
#define HEIGHTCARD (HDHEIGTHCARD * SCREENHEIGHT / 1080)
typedef struct card_s {
    Entity *soul;
    bool pointed;
}              card_t;

card_t *CreateCard(SDL_Renderer *r, int x, int y, int width, int height, const char *path);

void ShowCard(SDL_Renderer *r, card_t *card);

void CheckPointed(card_t *cd, Skill* skl, SDL_Point p);

void DestroyCard(card_t *c); 

#endif



