#include"EManager.h"



Person** FillEnemyArr(SDL_Renderer* r) {
	Person** a ;
	for (int i = 0; i < ENEMYCOUNT; i++) {
		a[i] = CreateEnemy(r, (EnemyType)i);
		a[i]->stats.armor = 0;
	}
	return a;
}

Person* CreateEnemy(SDL_Renderer* r, EnemyType type) {
	Person* p;
	switch (type) {
		case EASY_ENEMY:     p = CreatePerson(r, TILESIZE * 2, TILESIZE, TILESIZE, TILESIZE, "../images/vrag.png"); break;
		case MEDIUM_ENEMY:   p = CreatePerson(r, TILESIZE * 3, TILESIZE, TILESIZE, TILESIZE, "../images/vrag.png"); break;
		case HARD_ENEMY:     p = CreatePerson(r, TILESIZE * 4, TILESIZE, TILESIZE, TILESIZE, "../images/vrag.png"); break;
		case VERY_HARD_ENEMY:p = CreatePerson(r, TILESIZE * 5, TILESIZE, TILESIZE, TILESIZE, "../images/vrag.png"); break;
		case EXTREME_ENEMY:  p = CreatePerson(r, TILESIZE * 6, TILESIZE, TILESIZE, TILESIZE, "../images/vrag.png"); break;
		case BOSS_ENEMY:     p = CreatePerson(r, TILESIZE * 7, TILESIZE, TILESIZE, TILESIZE, "../images/vrag.png"); break;
		default:             p = CreatePerson(r, TILESIZE * 1, TILESIZE, TILESIZE, TILESIZE, "../images/vrag.png"); break;
	}


	return p;
}

void DestroyEnemyArr(Person** a) {
	for (int i = 0; i < ENEMYCOUNT; i++) {
		DestroyPerson(a[i]);
	}
}

void ShowEnemyArr(SDL_Renderer* r,Person** a) {
	for (int i = 0; i < ENEMYCOUNT; i++) {
		ShowPerson(r, a[i]);
	}
}

Person* FindEnemy(int x, int y,Person** a)//��������
{
	for (int i = 0; i < ENEMYCOUNT; i++) {
		int EnemyX = a[i]->soul->rect.y / TILESIZE;
		int EnemyY = a[i]->soul->rect.x / TILESIZE;
		if (x == EnemyX && y == EnemyY && a[i]->alive == true) {
			return a[i];
		}
	}
	return 0;
}

bool IsWin(Person** a)
{
	for (int i = 0; i < ENEMYCOUNT; i++) {
		if (a[i]->alive == true) {
			return false;
		}
	}
	return true;
}
