#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <GL\Glut.h>

#include "Entity.h"
#include "GLStuff.h"
#include "Main.h"

extern
Entity *pPlanets, *pStars ;

void AddStar() ;
void DisplayStars() ;

void AddPlanet() ;
void DisplayPlanets() ;

#endif