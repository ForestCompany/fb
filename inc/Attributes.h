#pragma once
#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H
#include"Functions.h"


typedef struct {
	int kolik;
	int statperatr;
	int cap;
	int income;
}Atribute;

//cap = value*statsperatr

Atribute* CreateAtribute(int kolik,  int statperatr,  int income);

void DestroyAtribute(Atribute* a);



#endif 




