
#include "Functions.h"

SDL_Texture* CreateTextureFromImg(SDL_Renderer* renderer, const char* path) {
	SDL_Surface* srf = IMG_Load(path);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, srf);
	SDL_FreeSurface(srf);
	return text;
}

SDL_Texture* CreateTextureFromFont(SDL_Renderer* renderer, char text[5], const char* fontpath, int fontsize, SDL_Color color)
{
    TTF_Font* font = TTF_OpenFont(fontpath, fontsize);

    SDL_Surface* surfaceA = TTF_RenderText_Solid(font, text, color);

    SDL_Texture* fonttext = SDL_CreateTextureFromSurface(renderer, surfaceA);
	SDL_FreeSurface(surfaceA);
	TTF_CloseFont(font);
	return fonttext;
}


SDL_Rect CreateRect(int x, int y, int width, int height) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	return rect;
}




int getwidth(int hp, int cap, int width) {
	int percent = hp * 100 / cap;
	return percent * width / 100;
}











