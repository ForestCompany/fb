#include "Person.h"

Person* CreatePerson(SDL_Renderer* r,int x, int y, int width, int height, const char* path) {
	Person* p = (Person*)malloc(sizeof(Person));
	p->soul = CreateEntity(r, x, y, width, height, path);
	p->stats.power = CreateAtribute(10, 10, 1);
	p->stats.hp = p->stats.power->cap;
	p->stats.intellekt = CreateAtribute(10, 10, 1);
	p->stats.mana = p->stats.intellekt->cap;
	p->stats.damage = 100;
	p->stats.armor = 100;
	p->alive = true;
	for (int i = 0; i < 6; i++) {
		p->inventory[i] = 0;
	}
	return p;
}

void DestroyPerson(Person* p) {
	for (int i = 0; i < 6; i++) {
		if (p->inventory[i] != 0) {
			free(p->inventory[i]); 
		}
	}
	DestroyAtribute(p->stats.intellekt);
	DestroyAtribute(p->stats.power);
	DestroyEntity(p->soul);
	free(p);
}

void ShowPerson(SDL_Renderer* r, Person* p)
{
	if (p->alive == true)
	ShowEntity(r,p->soul);
	
}

void ShowFontStats(SDL_Renderer* r, Person* p, SDL_Color color)
{
	char str[20];
	SDL_Rect rect;


	SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
	rect.x = XTABFORBAR;
	rect.y = TILESIZE*HEIGHTAMOUNT + YTABFORHPBAR;
	rect.w = getwidth(p->stats.hp, p->stats.power->cap, WIDTHBAR);
	rect.h = HEIGHTBAR;
	SDL_RenderFillRect(r, &rect);
	SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
	rect.x = XTABFORBAR;
	rect.y = TILESIZE*HEIGHTAMOUNT + YTABFORHPMANA;
	rect.w = getwidth(p->stats.mana, p->stats.intellekt->cap, WIDTHBAR);
	rect.h = HEIGHTBAR;
	SDL_RenderFillRect(r, &rect);



	sprintf(str, "%d", p->stats.hp);
	Entity* hp = CreateEntityTTF(r, XTABFORBAR + WIDTHBAR/4, TILESIZE*HEIGHTAMOUNT + YTABFORHPBAR, 60, HEIGHTBAR, "fonts/Minecraft.ttf", str, 120, color);



	sprintf(str, "%d", p->stats.mana);
	Entity* mana = CreateEntityTTF(r, XTABFORBAR + WIDTHBAR/4, TILESIZE*HEIGHTAMOUNT + YTABFORHPMANA, 60, HEIGHTBAR, "fonts/Minecraft.ttf", str, 120, color);



	sprintf(str,  "%d", p->stats.armor);
	Entity* armor = CreateEntityTTF(r, XTABFORBAR , TILESIZE*HEIGHTAMOUNT + YARMORTAB, 60, HEIGHTBAR, "fonts/Minecraft.ttf", str, 120, color);



	sprintf(str,  "%d", p->stats.damage);
	Entity* damage = CreateEntityTTF(r, XTABFORBAR + 100, TILESIZE*HEIGHTAMOUNT + YARMORTAB, 60, HEIGHTBAR, "fonts/Minecraft.ttf", str, 120, color);


	ShowEntity(r, hp);
	ShowEntity(r, mana);
	ShowEntity(r, armor);
	ShowEntity(r, damage);


	DestroyEntity(hp);
	DestroyEntity(mana);
	DestroyEntity(armor);
	DestroyEntity(damage);
}


void ShowStats(Person* p)
{
	printf("hp:%d\nmana:%d\ndamage:%d\narmor:%d\n\n",p->stats.hp, p->stats.mana, p->stats.damage, p->stats.armor);
}

void PVP(Person* p1, Person* p2)
{
	/*p2->stats.hp -= p1->stats.damage - p2->stats.armor;
	p1->stats.hp -= p2->stats.damage - p1->stats.armor;*/
	
	DecrementHP(p2, p1->stats.damage - p2->stats.armor);
	DecrementHP(p1, p2->stats.damage - p1->stats.armor);

	if (p1->stats.hp <= 0) {
		p1->alive = false;
	}
	
	if (p2->stats.hp <= 0) {
		p2->alive = false;
	}
}

void IncrementHP(Person* p,int hp)
{
	if (p->stats.hp + hp >= p->stats.power->cap) {
		p->stats.hp = p->stats.power->cap;
	}
	else {
		p->stats.hp += hp;
	}
}

void DecrementHP(Person* p, int hp)
{
	if (p->stats.hp - hp <= 0) {
		p->stats.hp = 0;
		if (p->stats.hp <= 0)p->alive = false;
	}
	else {
		p->stats.hp -= hp;
	}
}

void IncrementMana(Person* p, int mana) {
	if (p->stats.mana + mana  >= p->stats.intellekt->cap) {
		p->stats.mana = 0;
	}
	else {
		p->stats.mana += mana;
	}
}

void DecrementMana(Person* p, int mana)
{
	if (p->stats.mana - mana <= 0) {
		p->stats.mana = 0;
	}
	else {
		p->stats.mana -= mana;
	}
}
