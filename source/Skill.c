#include "Skill.h"


Skill* CreateSkill(SDL_Renderer* r, SDL_Rect rect, const char* apath, const char* cpath,Uint32 delta,int manacost)
{
	Skill* s = (Skill*)malloc(sizeof(Skill));
	s->rect = rect;
	s->active = CreateTextureFromImg(r, apath);
	s->cooldown = CreateTextureFromImg(r, cpath);
	s->delta = delta;
	s->state = ACTIVE;
	s->counter = s->delta/1000;
	s->manacost = manacost;
	char str[4];
	sprintf(str, "%d", s->counter);
	s->lastTimerUpdate = 0;
	s->timer = CreateEntityTTF(r, rect.x, rect.y, rect.w, rect.h, "fonts/Minecraft.ttf", str, 20, (SDL_Color){255,255,255,0});
	return s;
}

void ShowSkill(SDL_Renderer* r, Skill* s) {
	switch (s->state) {
		case ACTIVE: SDL_RenderCopy(r,s->active,0,&s->rect); break;
		case COOLDOWN: SDL_RenderCopy(r,s->cooldown,0,&s->rect); ShowEntity(r, s->timer); break;
	}
}

void DestroySkill(Skill* s) {
	SDL_DestroyTexture(s->active);
	SDL_DestroyTexture(s->cooldown);
	DestroyEntity(s->timer);
	free(s);
}

void SwitchState(Skill* h)
{
	switch (h->state) {
		case ACTIVE:h->state = COOLDOWN; break;
		case COOLDOWN:h->state = ACTIVE; break;
	}
}

void UpdateSkill(SDL_Renderer* r, Skill* b)
{
	Uint32 currentTime = SDL_GetTicks();

	if (b->state == COOLDOWN) {
		
		if (currentTime - b->lastTimerUpdate >= 1000) {
			char str[4];
			sprintf(str, "%d", b->counter);

			SDL_DestroyTexture(b->timer->text);
			b->timer->text = CreateTextureFromFont(r, str, "fonts/Minecraft.ttf", 12, (SDL_Color) { 255, 255, 255 ,0});
			


			
			b->counter--;
			b->lastTimerUpdate = currentTime;
		}

		if (currentTime - b->StartCd >= b->delta) {
			SwitchState(b);
			b->counter = 0;
		}
	}
}

void PressSkill(Skill* b)
{
	
		SwitchState(b);
		b->StartCd = SDL_GetTicks();
		b->counter = b->delta / 1000;

	
}
