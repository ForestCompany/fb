#include"EManager.h"



void FillEnemyArr(SDL_Renderer* r) {
	for (int i = 0; i < ENEMYCOUNT; i++) {
		EnemyArr[i] = CreateEnemy(r, (EnemyType)i);
		EnemyArr[i]->stats.armor = 0;
	}
}

Person* CreateEnemy(SDL_Renderer* r, EnemyType type) {
	Person* p;
	switch (type) {
		case EASY_ENEMY:     p = CreatePerson(r, WIDTHTILE * 2, WIDTHTILE, WIDTHTILE, WIDTHTILE, "../images/vrag.png"); break;
		case MEDIUM_ENEMY:   p = CreatePerson(r, WIDTHTILE * 3, WIDTHTILE, WIDTHTILE, WIDTHTILE, "../images/vrag.png"); break;
		case HARD_ENEMY:     p = CreatePerson(r, WIDTHTILE * 4, WIDTHTILE, WIDTHTILE, WIDTHTILE, "../images/vrag.png"); break;
		case VERY_HARD_ENEMY:p = CreatePerson(r, WIDTHTILE * 5, WIDTHTILE, WIDTHTILE, WIDTHTILE, "../images/vrag.png"); break;
		case EXTREME_ENEMY:  p = CreatePerson(r, WIDTHTILE * 6, WIDTHTILE, WIDTHTILE, WIDTHTILE, "../images/vrag.png"); break;
		case BOSS_ENEMY:     p = CreatePerson(r, WIDTHTILE * 7, WIDTHTILE, WIDTHTILE, WIDTHTILE, "../images/vrag.png"); break;
		default:             p = CreatePerson(r, WIDTHTILE, WIDTHTILE, WIDTHTILE, WIDTHTILE, "../images/vrag.png"); break;
	}


	return p;
}

void DestroyEnemyArr() {
	for (int i = 0; i < ENEMYCOUNT; i++) {
		DestroyPerson(EnemyArr[i]);
	}
}

void ShowEnemyArr(SDL_Renderer* r) {
	for (int i = 0; i < ENEMYCOUNT; i++) {
		ShowPerson(r, EnemyArr[i]);
	}
}

Person* FindEnemy(int x, int y)//êàðòàààà
{
	for (int i = 0; i < ENEMYCOUNT; i++) {
		int EnemyX = EnemyArr[i]->soul->rect.y / WIDTHTILE;
		int EnemyY = EnemyArr[i]->soul->rect.x / WIDTHTILE;
		if (x == EnemyX && y == EnemyY && EnemyArr[i]->alive == true) {
			return EnemyArr[i];
		}
	}
	return 0;
}

bool IsWin()
{
	for (int i = 0; i < ENEMYCOUNT; i++) {
		if (EnemyArr[i]->alive == true) {
			return false;
		}
	}
	return true;
}
