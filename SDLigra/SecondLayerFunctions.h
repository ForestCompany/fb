#pragma once
#ifndef	SECONDLFINCTIONS_H
#define SECONDLFINCTIONS_H
#include "Attributes.h"
#include "Stats.h"
#include "Entity.h"
#include "Item.h"
#include "Person.h"
#include "Button.h"
#include "Map.h"



bool isnearperson(Person* p, Map* m, SDL_Point mousecords);

typeoftile gettype(Map* map, int x, int y, Person* enemy);



#endif 


