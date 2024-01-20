#include "Buttons.h"

Button* CreateButton(SDL_Renderer* r, SDL_Rect rect, const char* state1path, const char* state2path) {
	Button* button = (Button*)malloc(sizeof(Button));
	button->rect = rect;
	button->state1 = CreateTextureFromImg(r, state1path);
	button->state2 = CreateTextureFromImg(r, state2path);
	button->state = STATE1;
	return button;
}

bool CheckButton(SDL_Point* mousecords, SDL_Rect* rect) {
	return SDL_PointInRect(mousecords, rect);
}

void DestroyButton(Button* button) {
	SDL_DestroyTexture(button->state1);
	SDL_DestroyTexture(button->state2);
	free(button);
}

void SwitchButtonState(Button* h)
{
	switch (h->state) {
	case STATE1:
		h->state = STATE2; break;
	case STATE2:
		h->state = STATE1; break;
	}
}

void ShowButton(SDL_Renderer* r, Button* button){
	switch(button->state){
		case STATE1:
			SDL_RenderCopy(r, button->state1, NULL, &button->rect);
			break;
		case STATE2:
			SDL_RenderCopy(r, button->state2, NULL, &button->rect);
			break;
	}
}