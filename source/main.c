#include "SecondLayerFunctions.h"




SDL_Renderer* renderer;
SDL_Window* window;


int main(int argc, char* argv[]) 
{
	SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    window = SDL_CreateWindow("Forest", 0, 0, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    intro(renderer);
	Game(renderer);
    SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
	return 1;
}