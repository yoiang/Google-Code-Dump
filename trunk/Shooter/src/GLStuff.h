#ifndef __GL_STUFF_H__
#define __GL_STUFF_H__

#include <GL\Glut.h>
//#include "Mouse.h"
//#include "Body.h"

extern
int iWinHeight,	// window height
	iWinWidth ;	// window width

extern
bool	bLighting,			// toggle lighting
		bPerspective,		// toggle perspective and orthographic mode 
		bFilling ;			// toggle filling

/*void EnableLights();
void DisableLights() ;
void SetLights() ;
*/
void ToggleLighting(bool bSetLighting) ;

void ToggleFilling(bool bSetFilling) ;
void TogglePerspective(bool bSetPerspective) ;
void ReshapeHandler (int iWidth, int iHeight) ; // resizing window callback function
void InitDisplay(bool bSetFilling, bool bSetPerspective, bool bSetLighting) ; // initialize variables and display modes
void InitGLUT(int argc, char **argv, char *szWindowName, int iSetWinWidth, int iSetWinHeight) ;

#endif
