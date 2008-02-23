#ifndef __GL_STUFF_H__
#define __GL_STUFF_H__

#include <GL\Glut.h>

extern
int iWinHeight,	// window height
	iWinWidth ;	// window width

extern
bool	bLighting,			// toggle lighting
		bPerspective,		// toggle perspective and orthographic mode 
		bFilling,			// toggle filling
		bFullscreen ;		// toggle fullscreen

extern
GLfloat fCameraX,	// camera location
		fCameraY, 
		fCameraZ, 
		fCameraAngle[3],	// camera angle
		fPlaneOrientation[3] ;	// plane orientation

extern
bool	bLeftMouseDown,		// toggle left mouse button down
		bRightMouseDown ;	// toggle right mouse button down

#define CLEARED -9876

extern
int		iLastMouseX,	// last X position of mouse
		iLastMouseY ;	// last Y position of mouse

extern
int iNumLights ;	// number of lights in scene

void InitMouse () ;	// initialize the mouse
void InitCamera() ;	// initialize the camera
void SetCameraView() ;	// set camera matrix
void ToggleFullscreen(bool bSetFullscreen) ;	// toggle fullscreen
void ToggleLighting(bool bSetLighting) ;	// toggle lighting
void ToggleFilling(bool bSetFilling) ;	// toggle filling
void TogglePerspective(bool bSetPerspective) ;	// toggle perspective
void InitDisplay(bool bSetFilling, bool bSetPerspective, bool bSetLighting) ; // initialize variables and display modes
void InitGLUTWindow(int argc, char **argv, char *szWindowName, int iSetWinWidth, int iSetWinHeight) ;

#endif
