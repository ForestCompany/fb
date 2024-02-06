#include "Item.h"

Item* CreateItem(SDL_Renderer* r,const char* title, int x, int y, int width, int height, const char* path, int hp, int mana, int armor, int damage)
{
    Item* i = (Item*)malloc(sizeof(Item));
    i->soul = CreateEntity(r, x, y, width, height, path);
    i->stats.armor = armor;
    i->stats.hp = hp;
    i->stats.mana = mana;
    i->stats.damage= damage;
    i->title = title;
    return i;
}


void DestroyItem(Item* i) {
    DestroyEntity(i->soul);
    free(i);
}

void ShowItem(SDL_Renderer *r, Item *i) {
    ShowEntity(r, i->soul);
}