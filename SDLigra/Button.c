#include "Button.h"


Button* CreateButton(SDL_Renderer* r, SDL_Rect rect, const char* apath, const char* cpath,Uint32 delta,int manacost)
{
	Button* v = (Button*)malloc(sizeof(Button));
	v->rect = rect;
	v->active = CreateTextureFromImg(r, apath);
	v->cooldown = CreateTextureFromImg(r, cpath);
	v->delta = delta;
	v->state = ACTIVE;
	v->counter = v->delta/1000;
	v->manacost = manacost;
	char str[4];
	sprintf_s(str, sizeof(str), "%d", v->counter);
	v->lastTimerUpdate = 0;
	v->timer = CreateEntityTTF(r, rect.x, rect.y, rect.w, rect.h, "../fonts/Minecraft.ttf", str, 20, (SDL_Color){255,255,255});
	return v;
}

void ShowButton(SDL_Renderer* r, Button* v) {
	switch (v->state) {
		case ACTIVE: SDL_RenderCopy(r,v->active,0,&v->rect); break;
		case COOLDOWN: SDL_RenderCopy(r,v->cooldown,0,&v->rect); ShowEntity(r, v->timer); break;
	}
}

void DestroyButton(Button* v) {
	SDL_DestroyTexture(v->active);
	SDL_DestroyTexture(v->cooldown);
	DestroyEntity(v->timer);
	free(v);
}

void SwitchState(Button* h)
{
	switch (h->state) {
		case ACTIVE:h->state = COOLDOWN; break;
		case COOLDOWN:h->state = ACTIVE; break;
	}
}

void UpdateButton(SDL_Renderer* r, Button* b)
{
	Uint32 currentTime = SDL_GetTicks();

	if (b->state == COOLDOWN) {
		// Проверяем, прошла ли секунда с последнего обновления таймера
		if (currentTime - b->lastTimerUpdate >= 1000) {
			char str[4];
			sprintf_s(str, sizeof(str), "%d", b->counter);

			SDL_DestroyTexture(b->timer->text);
			b->timer->text = CreateTextureFromFont(r, str, "../fonts/Minecraft.ttf", 12, (SDL_Color) { 255, 255, 255 });
			


			// Уменьшаем счетчик после его использования
			b->counter--;
			b->lastTimerUpdate = currentTime;
		}

		if (currentTime - b->StartCd >= b->delta) {
			SwitchState(b);
			b->counter = 0;
		}
	}
}

void PressButton(Button* b)
{
	
		SwitchState(b);
		b->StartCd = SDL_GetTicks();
		b->counter = b->delta / 1000;

	
}
