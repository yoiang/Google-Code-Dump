#include "GLStuff.h"

int iWinHeight,	// window height
	iWinWidth ;	// window width

bool	bLighting = false,			// toggle lighting
		bPerspective = false,		// toggle perspective and orthographic mode 
		bFilling = false,			// toggle filling
		bFullscreen = false ;

GLfloat fCameraLocation[3], 
		fCameraAngle[3] ;

bool	bLeftMouseDown,		// toggle left mouse button down
		bRightMouseDown ;	// toggle right mouse button down

int	iLastMouseX,	// last X position of mouse
	iLastMouseY ;	// last Y position of mouse

int iNumLights ; // number of lights in scene

void MouseMotionHandler (int iX, int iY) // mouse movement handler
{
	if (bLeftMouseDown && bRightMouseDown)
	{
	} else if (bLeftMouseDown)
	{
		fCameraAngle[0] += -1.0 * (iY - iLastMouseY) ;
		fCameraAngle[1] += -1.0 * (iX - iLastMouseX) ;
	} else if (bRightMouseDown)
	{
	}
	iLastMouseX = iX ;
	iLastMouseY = iY ;
}

void InitMouse ()
{
	bLeftMouseDown = false ;
	bRightMouseDown = false ;

	iLastMouseX = CLEARED ;
	iLastMouseY = CLEARED ;
}

void InitCamera()
{
	fCameraLocation[0] = 4 ;
	fCameraLocation[1] = 2 ;
	fCameraLocation[2] = 5 ;

	fCameraAngle[0] = 0 ;
	fCameraAngle[1] = 0 ;
	fCameraAngle[2] = 0 ;
}

void SetCameraView()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	glLoadIdentity() ;

	glRotatef(-1.0*fCameraAngle[0], 1.0, 0.0, 0.0) ;
	glRotatef(-1.0*fCameraAngle[1], 0.0, 1.0, 0.0) ;
	glRotatef(fCameraAngle[2], 0.0, 0.0, 1.0) ;

	glTranslatef(-fCameraLocation[0], -fCameraLocation[1], -fCameraLocation[2]) ;
}

void ToggleFullscreen(bool bSetFullscreen) // toggle fullscreen
{
	bFullscreen = bSetFullscreen ;
}

void ToggleLighting(bool bSetLighting)
{
	bLighting = bSetLighting ;
	if (bLighting)
	{
		glEnable(GL_LIGHTING) ;
		glEnable(GL_COLOR_MATERIAL) ;
	}	else
	{
		glDisable(GL_LIGHTING) ;
		glDisable(GL_COLOR_MATERIAL) ;
	}
}

void ToggleFilling(bool bSetFilling)
{
	bFilling = bSetFilling ;
	if (bFilling)
	{
		glPolygonMode(GL_FRONT, GL_FILL) ;
	}	else
	{
		glPolygonMode(GL_FRONT, GL_LINE) ;
	}
}

void TogglePerspective(bool bSetPerspective) 
{
	bPerspective = bSetPerspective ;

	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;

	if (bPerspective)
	{
		gluPerspective(90.0, (GLfloat) iWinWidth/(GLfloat) iWinHeight, 1.0, 200.0) ;	
	}	else
	{
		glOrtho(-10, 30, -3, 3, 1.0, 200.0) ;
	}
	glMatrixMode(GL_MODELVIEW) ;
}

void ReshapeHandler (int iWidth, int iHeight) // resizing window callback function
{
	if (!bFullscreen)
	{
		iWinWidth = iWidth ;
		iWinHeight = iHeight ;
	}

	glViewport(0, 0, (GLsizei) iWidth, (GLsizei) iHeight) ;

	TogglePerspective(bPerspective) ;
}

void InitDisplay(bool bSetFilling, bool bSetPerspective, bool bSetLighting) // initialize variables and display modes
{
	glLineWidth(1.0) ;

	InitCamera() ;
	GLfloat lmodel_ambient [] = { 0.2, 0.2, 0.2, 1.0 } ;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient) ;

	ToggleLighting(bSetLighting) ;
	
	ToggleFilling(bSetFilling) ;

	// set shading model
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) ;
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);	 

	// enable depth testing, color materials and alpha blending (just used for eyes really..)
	glEnable(GL_DEPTH_TEST) ;

	// set clear information
	glClearColor(0.2, 0.0, 0.0, 0.0) ;
	glClearDepth(1.0) ;

	TogglePerspective(bSetPerspective) ;
}

