#include "../inc/Skill.h"


Skill* CreateSkill(SDL_Renderer* r, SDL_Rect rect, const char* apath, const char* cpath,Uint32 delta,int manacost)
{
	Skill* s = (Skill*)malloc(sizeof(Skill));
	s->b = CreateButton(r,rect,apath,cpath);
	s->delta = delta;
	s->counter = s->delta/1000;
	s->manacost = manacost;
	char str[4];
	sprintf(str, "%d", s->counter);
	s->lastTimerUpdate = 0;
	s->timer = CreateEntityTTF(r, rect.x, rect.y, rect.w, rect.h, "resource/fonts/Minecraft.ttf", str, 20, (SDL_Color){255,255,255,0});
	return s;
}

void ShowSkill(SDL_Renderer* r, Skill* s) {
	ShowButton(r,s->b);
	if(s->b->state == STATE2){
		ShowEntity(r,s->timer);
	}
}

void DestroySkill(Skill* s) {
	DestroyButton(s->b);
	DestroyEntity(s->timer);
	free(s);
}

void SwitchSkillState(Skill* h)
{
	SwitchButtonState(h->b);
}

void UpdateSkill(SDL_Renderer* r, Skill* b)
{
	Uint32 currentTime = SDL_GetTicks();

	if (b->b->state == STATE2) {
		
		if (currentTime - b->lastTimerUpdate >= 1000) {
			char str[4];
			sprintf(str, "%d", b->counter);

			SDL_DestroyTexture(b->timer->text);
			b->timer->text = CreateTextureFromFont(r, str, "resource/fonts/Minecraft.ttf", 12, (SDL_Color) { 255, 255, 255 ,0});
			


			
			b->counter--;
			b->lastTimerUpdate = currentTime;
		}

		if (currentTime - b->StartCd >= b->delta) {
			SwitchSkillState(b);
			b->counter = 0;
		}
	}
}

void PressSkill(Skill* b)
{
	SwitchSkillState(b);
	b->StartCd = SDL_GetTicks();
	b->counter = b->delta / 1000;	
}
