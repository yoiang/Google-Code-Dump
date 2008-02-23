#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <windows.h>
#include <gl\Glut.h>
#include "GLStuff.h"

extern 
bool	bLeftMouseDown,		// toggle left mouse button down
		bRightMouseDown ;	// toggle right mouse button down

extern
int		iLastMouseX,	// last X position of mouse
		iLastMouseY ;	// last Y position of mouse

#define CLEARED -9876

void InitMouse () ;
void MouseMotionHandler (int iX, int iY) ; // mouse movement handler
void MouseButtonHandler (int iButton, int iState, int iX, int iY) ; // mouse button handler

#endif