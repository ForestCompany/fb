#include "Vutton.h"

Vutton* CreateVutton(SDL_Renderer* r, SDL_Rect rect, const char* apath, const char* cpath)
{
	Vutton* v = (Vutton*)malloc(sizeof(Vutton));
	v->rect = rect;
	v->active = CreateTextureFromImg(r, apath);
	v->cooldown = CreateTextureFromImg(r, cpath);
	return v;
}

void ShowVutton(SDL_Renderer* r, Vutton* v, VuttonState state) {
	switch (state) {
		case ACTIVE: SDL_RenderCopy(r,v->active,0,&v->rect); break;
		case COOLDOWN: SDL_RenderCopy(r,v->cooldown,0,&v->rect); break;
	}
}



void DestroyVutton(Vutton* v) {
	SDL_DestroyTexture(v->active);
	SDL_DestroyTexture(v->cooldown);
	free(v);
}