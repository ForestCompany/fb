#include "../inc/Card.h"

card_t *CreateCard(SDL_Renderer *r, int x, int y, int width, int height, const char *path) {
    card_t *c = (card_t*)malloc(sizeof(card_t));
    c->soul = CreateEntity(r, x, y, width, height, path);
    c->pointed = false;
    return c;
}

void ShowCard(SDL_Renderer *r, card_t *card) {
    if (card->pointed) {
        ShowEntity(r, card->soul);
    }
}

void CheckPointed(card_t *cd, Skill* skl, SDL_Point p) {
    cd->pointed = SDL_PointInRect(&p, &skl->b->rect);
}

void DestroyCard(card_t * c) {
    DestroyEntity(c->soul);
    free(c);
}




