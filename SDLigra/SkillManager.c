#include "SkillManager.h"

void FillSkillArr(SDL_Renderer* r)
{
    SDL_Rect rect = { 792,120 + 864,73,73 };
    SkillArray[0] = CreateButton(r, rect, "../images/sword.jpg", "../images/swordBLACK.jpg", 15000, 20);
    rect.x = 962;
    SkillArray[1] = CreateButton(r, rect, "../images/heal.jpg", "../images/healBLACK.jpg", 20000, 20);
    rect.x = 1132;
    SkillArray[2] = CreateButton(r, rect, "../images/ulta.jpg", "../images/ultaBLACK.jpg", 30000, 20);
    SkillArray[2]->manacost = 60;
}

void ShowSkillArr(SDL_Renderer* r)
{
    for (int i = 0; i < SKILLCOUNT; i++) {
        ShowButton(r, SkillArray[i]);
    }
}

void UpdateSkillArr(SDL_Renderer* r)
{
    for (int i = 0; i < SKILLCOUNT; i++) {
        UpdateButton(r, SkillArray[i]);
    }
}

void DetroySkillArr()
{
    for (int i = 0; i < SKILLCOUNT; i++) {
        DestroyButton(SkillArray[i]);
    }
}





