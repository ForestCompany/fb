#include"Person.h"
#include<random>

typedef enum {
	WARRIOR,
	ILIA
}ENEMYTYPE;

void FillEnemy(SDL_Renderer* r, Person** em) {
	for (int i = 0; i < 6; i++) {
		ENEMYTYPE enemy = rand() % 2;
		em[i] = CreatePerson(r, 0,0, 96, 96, "../images/vrag.png");
		switch (enemy) {
		case ILIA:
			em[i]->stats.armor = 10;
			em[i]->stats.damage = 10;
			em[i]->stats.hp = 10;
			em[i]->stats.mana = 10;
			break;
		case WARRIOR:
			em[i]->stats.armor = 20;
			em[i]->stats.damage = 20;
			em[i]->stats.hp = 20;
			em[i]->stats.mana = 20;
			em[i]->soul->path = "../images/OIG (13).jpg";
			break;
		}
	}
}


void DestroyEnemy(Person** em) {
	for (int i = 0; i < 6; i++) {
		DestroyPerson(em[i]);
	}
}



