#include "../inc/Entity.h"


Entity* CreateEntity(SDL_Renderer* renderer,int x, int y, int width, int height, const char* path)
{
	Entity* b = (Entity*)malloc(sizeof(Entity));
	b->text = CreateTextureFromImg(renderer,path);
	b->rect = CreateRect(x, y, width, height);
	return b;
}

Entity* CreateEntityTTF(SDL_Renderer* renderer, int x, int y, int width, int height, const char* font, char text[20], int fontsize, SDL_Color color)
{
	Entity* b = (Entity*)malloc(sizeof(Entity));
	b->text = CreateTextureFromFont(renderer, text, font, fontsize, color);
	b->rect = CreateRect(x, y, width, height);
	return b;
}

bool CheckEntity(SDL_Point* mousecords, SDL_Rect* rect) {
	return SDL_PointInRect(mousecords, rect);
}


void DestroyEntity(Entity* b)
{
	SDL_DestroyTexture(b->text);
	free(b);
}



void ShowEntity(SDL_Renderer* renderer, Entity* but) {
	SDL_RenderCopy(renderer, but->text, 0, &but->rect);
}