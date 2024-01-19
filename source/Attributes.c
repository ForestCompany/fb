#include "Attributes.h"

Atribute* CreateAtribute(int kolik,int statperatr,  int income)
{
    Atribute* a = (Atribute*)malloc(sizeof(Atribute));
    a->kolik = kolik;
    a->statperatr = statperatr;
    a->cap = statperatr * kolik;
    a->income = income;
    return a;
}



void DestroyAtribute(Atribute* a) {
    free(a);
}