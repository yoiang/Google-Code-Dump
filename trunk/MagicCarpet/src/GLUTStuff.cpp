#include "GLUTStuff.h"

int iWinHeight,	// window height
	iWinWidth ;	// window width

bool	bLighting = false,			// toggle lighting
		bPerspective = false,		// toggle perspective and orthographic mode 
		bFilling = false,			// toggle filling
		bFullscreen = false,
		bFog = true ;

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
		if (fCameraAngle[0] - (iY - iLastMouseY) > -80.0 && 
			fCameraAngle[0] - (iY - iLastMouseY) < 80.0) fCameraAngle[0] -= (iY - iLastMouseY) ;
		fCameraAngle[1] -= (iX - iLastMouseX) ;
	} else if (bRightMouseDown)
	{
	}
	iLastMouseX = iX ;
	iLastMouseY = iY ;
}

void MouseButtonHandler (int iButton, int iState, int iX, int iY) // mouse button handler
{
	iLastMouseX = iX ;
	iLastMouseY = iY ;
	if (iButton == GLUT_RIGHT_BUTTON)
	{

		if (iState == GLUT_DOWN) 
		{
			bRightMouseDown = true ;
		}
		else 
		{
			bRightMouseDown = false ;
		}
	} else if (iButton == GLUT_LEFT_BUTTON)
	{
		if (iState == GLUT_DOWN) 
		{
			bLeftMouseDown = true ;
		}
		else 
		{
			bLeftMouseDown = false ;	
		}
	}
}

void InitMouse ()
{
	bLeftMouseDown = false ;
	bRightMouseDown = false ;

	iLastMouseX = CLEARED ;
	iLastMouseY = CLEARED ;

	glutMouseFunc(MouseButtonHandler) ;
 	glutMotionFunc(MouseMotionHandler) ;
}

void InitCamera()
{
	fCameraLocation[0] = 0 ;
	fCameraLocation[1] = 10 ;
	fCameraLocation[2] = 0 ;
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

void ToggleFog(bool bSetFog)
{
	bFog = bSetFog ;
	if (bFog)
	{
		glEnable(GL_FOG);									
	} else
	{
		glDisable(GL_FOG);									
	}
}

void ToggleFullscreen(bool bSetFullscreen) // toggle fullscreen
{
	bFullscreen = bSetFullscreen ;
	if (bFullscreen)
	{
		glutFullScreen() ;
	} else
	{
		glutPositionWindow(50, 50) ;
		glutReshapeWindow(iWinWidth, iWinHeight) ;
	}
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
		gluPerspective(90.0, (GLfloat) iWinWidth/(GLfloat) iWinHeight, 0.1, 500.0) ;	
	}	else
	{
		glOrtho(-5, 5, -5, 5, 1.0, 200.0) ;
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

	GLfloat lmodel_ambient [] = { 0.9, 0.9, 0.9, 1.0 } ;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient) ;

	ToggleLighting(bSetLighting) ;
	
	ToggleFilling(bSetFilling) ;

	// set shading model
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) ;
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);	 

	float fogColor[4] = {0.0f,1.0f,1.0f,1.0f};	
	
	glFogi(GL_FOG_MODE, GL_EXP2);						// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);					// Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.02f);				// How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);					// The Fog's calculation accuracy
	glFogf(GL_FOG_START, 24.0f);							// Fog Start Depth
	glFogf(GL_FOG_END, 28.0f);							// Fog End Depth

	glEnable(GL_CULL_FACE) ;
	glCullFace(GL_BACK) ;

	// enable depth testing, color materials and alpha blending (just used for eyes really..)
	glEnable(GL_DEPTH_TEST) ;

	// set clear information
	glClearColor(0.0, 1.0, 1.0, 0.0) ;
	glClearDepth(1.0) ;

	TogglePerspective(bSetPerspective) ;

	ToggleFog(true) ;
}

void InitGLUTWindow(int argc, char **argv, char *szWindowName, int iSetWinWidth, int iSetWinHeight)
{
	iWinWidth = iSetWinWidth ;
	iWinHeight = iSetWinHeight ;

	glutInit(&argc, argv) ;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;
 	
	glutInitWindowPosition(50, 50) ;
	glutInitWindowSize(iSetWinWidth, iSetWinHeight) ;
	glutCreateWindow(szWindowName) ;
 
	glutReshapeFunc(ReshapeHandler) ;
}
