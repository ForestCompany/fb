#include "../inc/Person.h"

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
	Entity* hp = CreateEntityTTF(r, XTABFORBAR + WIDTHBAR/4, TILESIZE*HEIGHTAMOUNT + YTABFORHPBAR, 60, HEIGHTBAR, "resource/fonts/Minecraft.ttf", str, 120, color);



	sprintf(str, "%d", p->stats.mana);
	Entity* mana = CreateEntityTTF(r, XTABFORBAR + WIDTHBAR/4, TILESIZE*HEIGHTAMOUNT + YTABFORHPMANA, 60, HEIGHTBAR, "resource/fonts/Minecraft.ttf", str, 120, color);



	sprintf(str,  "%d", p->stats.armor);
	Entity* armor = CreateEntityTTF(r, XTABFORBAR , TILESIZE*HEIGHTAMOUNT + YARMORTAB, 60, HEIGHTBAR, "resource/fonts/Minecraft.ttf", str, 120, color);



	sprintf(str,  "%d", p->stats.damage);
	Entity* damage = CreateEntityTTF(r, XTABFORBAR + 100, TILESIZE*HEIGHTAMOUNT + YARMORTAB, 60, HEIGHTBAR, "resource/fonts/Minecraft.ttf", str, 120, color);


	ShowEntity(r, hp);
	ShowEntity(r, mana);
	ShowEntity(r, armor);
	ShowEntity(r, damage);

	for (int i = 0; i < 6; i++) {
		Item *it = p->inventory[i];
		if (it != NULL) {
			ShowItem(r, it);
		}
	}

	DestroyEntity(hp);
	DestroyEntity(mana);
	DestroyEntity(armor);
	DestroyEntity(damage);
}

void SetFullStats(Person *p, int npower, int nintellekt, int armor, int damage)
{
	p->stats.armor = armor;
	p->stats.damage = damage;

	p->stats.power->kolik = npower;
	p->stats.power->cap = npower * p->stats.power->statperatr;
	p->stats.hp = p->stats.power->cap;

	p->stats.intellekt->kolik = nintellekt;
	p->stats.intellekt->cap = nintellekt * p->stats.intellekt->statperatr;
	p->stats.mana = p->stats.intellekt->cap;
}

void UpdateStats(Person *p, int index) {
    if (p == NULL || p->inventory[index] == NULL || p->stats.power == NULL || p->stats.intellekt == NULL) {
        // Добавьте обработку нулевых указателей
        return;
    }
	int percenthp = (p->stats.hp ) / p->stats.power->cap;
	int percentmana = (p->stats.mana) / p->stats.intellekt->cap;
    // Обновление damage и armor
    p->stats.damage += p->inventory[index]->stats.damage;
    p->stats.armor += p->inventory[index]->stats.armor;

    // Обновление power
    p->stats.power->kolik += p->inventory[index]->stats.hp;
    p->stats.power->cap = p->stats.power->kolik * p->stats.power->statperatr;
    p->stats.hp = percenthp * p->stats.power->cap; // Обновление hp на основе процентного соотношения

    // Обновление intellekt
    p->stats.intellekt->kolik += p->inventory[index]->stats.mana;
    p->stats.intellekt->cap = p->stats.intellekt->kolik * p->stats.intellekt->statperatr;
    p->stats.mana = percentmana * p->stats.intellekt->cap; // Обновление mana на основе процентного соотношения
}



void ShowStats(Person* p)
{
	printf("hp:%d\nmana:%d\ndamage:%d\narmor:%d\nhp cap:%d\nmana cap:%d\n\n",p->stats.hp, p->stats.mana, p->stats.damage, p->stats.armor, p->stats.power->cap, p->stats.intellekt->cap 		);
	// for(int i = 0; i < 6; i++){
	// 	if(p->inventory[i]!=0){
	// 		printf("%s\n", p->inventory[i]->title);
	// 	}
	// 	else {
	// 		printf("NULL\n");
	// 	}
	// }
}

void PVP(Person* p1, Person* p2)
{
	/*p2->stats.hp -= p1->stats.damage - p2->stats.armor;
	p1->stats.hp -= p2->stats.damage - p1->stats.armor;*/
	
	DecrementHP(p2, p1->stats.damage - p2->stats.armor);
	DecrementHP(p1, p2->stats.damage - p1->stats.armor);

	if (p1->stats.hp <= 0) {
		p1->alive = false;
		GrabItem(p2, p1->inventory[0]);
		p1->inventory[0] = 0;
	}
	
	if (p2->stats.hp <= 0) {
		p2->alive = false;
		GrabItem(p1, p2->inventory[0]);
		p2->inventory[0] = 0;
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

int GetX(Person *p) {
	return p->soul->rect.x;
}
int GetY(Person *p) {
	return p->soul->rect.y;
}

void IncX(Person *p, int x) {
	p->soul->rect.x += x;
}

void IncY(Person *p, int y) {
	p->soul->rect.y += y;
}

void GrabItem(Person *p, Item *it) {
    if (p == NULL) {
        // Дополнительная проверка на корректность указателей
        printf("Ошибка: Некорректные указатели на персонажа \n");
        return;
    }
	if (it == NULL) {
		printf("ошибка указатель на предмет\n");
		return;
	}

    int volnyindex;
    for (volnyindex = 0; volnyindex < 6; volnyindex++) {
        if (p->inventory[volnyindex] == NULL) {
            // Проверяем, что элемент инвентаря пустой
            int x,width;
            int y	 = TILESIZE * HEIGHTAMOUNT + YTABSLOT;
            switch (volnyindex) {
                case 0: width = WIDTHSLOT1; x = XTABSLOT1; break;
                case 1: width = WIDTHSLOT2; x = XTABSLOT2; break;
                case 2: width = WIDTHSLOT3; x = XTABSLOT3; break;
                case 3: width = WIDTHSLOT4; x = XTABSLOT4; break;
                case 4: width = WIDTHSLOT5; x = XTABSLOT5; break;
                case 5: width = WIDTHSLOT6; x = XTABSLOT6; break;
            }
            p->inventory[volnyindex] = it;
            p->inventory[volnyindex]->soul->rect.x = x;
            p->inventory[volnyindex]->soul->rect.y = y;
			p->inventory[volnyindex]->soul->rect.w = width;
			p->inventory[volnyindex]->soul->rect.h = HEIGHTSLOT;
            UpdateStats(p, volnyindex);
            break;
        }
    }
    ShowStats(p);
}


