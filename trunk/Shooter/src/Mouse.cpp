#include "Mouse.h"
#include "Camera.h"

bool	bLeftMouseDown,		// toggle left mouse button down
		bRightMouseDown ;	// toggle right mouse button down

int		iLastMouseX,	// last X position of mouse
		iLastMouseY ;	// last Y position of mouse

void InitMouse ()
{
	bLeftMouseDown = false ;
	bRightMouseDown = false ;

	iLastMouseX = CLEARED ;
	iLastMouseY = CLEARED ;

}


