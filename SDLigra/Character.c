#include "Character.h"

Character* CreateCharacter(SDL_Renderer* r, const char* title, int x, int y, int width, int height, const char* path, int hp, int mana, int armor, int damage)
{
    Character* ch = (Character*)malloc(sizeof(Character));
    ch->soul = CreateItem(r, title, x, y, width, height, path, hp, mana, armor, damage);
    return ch;
}


void DestroyCharacter(Character* c) {
    DestroyItem(c->soul);
    free(c);
}

void ShowCharacter(SDL_Renderer* r, Character* c)
{
    ShowButton(r, c->soul->soul);
}

int GetX(Character* ch)
{
    return ch->soul->soul->rect.x;
}

int GetY(Character* ch)
{
    return ch->soul->soul->rect.y;
}