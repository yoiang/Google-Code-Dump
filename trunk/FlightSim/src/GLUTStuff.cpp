#include "GLUTStuff.h"

int iWinHeight,	// window height
	iWinWidth ;	// window width

bool	bLighting = false,			// toggle lighting
		bPerspective = false,		// toggle perspective and orthographic mode 
		bFilling = false,			// toggle filling
		bFullscreen = false ;		// toggle fullscreen

GLfloat fCameraX, fCameraY, fCameraZ, 
		fCameraAngle[3],
		fPlaneOrientation[3] ;

bool	bLeftMouseDown,		// toggle left mouse button down
		bRightMouseDown ;	// toggle right mouse button down

int	iLastMouseX,	// last X position of mouse
	iLastMouseY ;	// last Y position of mouse

int iNumLights ; // number of lights in scene

void MouseMotionHandler (int iX, int iY) // mouse movement handler
{
	if (bLeftMouseDown && bRightMouseDown)
	{
	} else if (bRightMouseDown)
	{
		fCameraAngle[0] += -1.0 * (iY - iLastMouseY) ;
		fCameraAngle[1] += -1.0 * (iX - iLastMouseX) ;
	} else if (bLeftMouseDown)
	{
		fPlaneOrientation[0] += ((iY - iLastMouseY) / (float)(iWinHeight)) * 90.0 ;
		fPlaneOrientation[1] += ((iX - iLastMouseX) / (float)(iWinHeight)) * -90.0 ;
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

void InitMouse () // initialize the mouse
{
	bLeftMouseDown = false ;
	bRightMouseDown = false ;

	iLastMouseX = CLEARED ;
	iLastMouseY = CLEARED ;

	glutMouseFunc(MouseButtonHandler) ;
 	glutMotionFunc(MouseMotionHandler) ;
}

void InitCamera() // initialize the camera
{
	fCameraX = 0 ;
	fCameraY = 30 ;
	fCameraZ = 0 ;
	fCameraAngle[0] = 0 ;
	fCameraAngle[1] = 0 ;
	fCameraAngle[2] = 0 ;
	fPlaneOrientation[0] = 0 ;
	fPlaneOrientation[1] = 0 ;
	fPlaneOrientation[2] = 0 ;
}

void SetCameraView() // set camera viewing position
{
	glLoadIdentity() ;

	glRotatef(-1.0*fCameraAngle[0], 1.0, 0.0, 0.0) ;
	glRotatef(-1.0*fCameraAngle[1], 0.0, 1.0, 0.0) ;
	glRotatef(fCameraAngle[2], 0.0, 0.0, 1.0) ;

	glTranslatef(-fCameraX, -fCameraY, -fCameraZ) ;
	gluLookAt(0, 0, 0, 0, 0.0, 1.0, 0, 1.0, 0) ;

	glTranslatef(0.0, -5.0, 0.0) ;
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

void ToggleLighting(bool bSetLighting) // toggle lighting
{
	bLighting = bSetLighting ;
	if (bLighting)
	{
		glEnable(GL_LIGHTING) ;
		for (int iLight = GL_LIGHT0 ; iLight < GL_LIGHT0 + iNumLights ; iLight ++)
			glEnable(iLight) ;
		glEnable(GL_COLOR_MATERIAL) ;
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;

	}	else
	{
		glDisable(GL_LIGHTING) ;
		for (int iLight = GL_LIGHT0 ; iLight < GL_LIGHT0 + iNumLights ; iLight ++)
			glEnable(iLight) ;

		glDisable(GL_COLOR_MATERIAL) ;
	}
}

void ToggleFilling(bool bSetFilling) // toggle filling
{
	bFilling = bSetFilling ;
	if (bFilling)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) ;
	}	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) ;
	}
}

void TogglePerspective(bool bSetPerspective) // toggle perspective
{
	bPerspective = bSetPerspective ;

	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;

	if (bPerspective)
	{
		gluPerspective(90.0, (GLfloat) iWinWidth/(GLfloat) iWinHeight, 1.0, 800.0) ;	
	}	else
	{
		glOrtho(-5, 5, -5, 5, 1.0, 700.0) ;
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

	iNumLights = 0 ;

	GLfloat lmodel_ambient [] = { 0.9, 0.9, 0.9, 1.0 } ;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient) ;
//	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE) ;

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) ;

	ToggleLighting(bSetLighting) ;
	
	ToggleFilling(bSetFilling) ;

	// set shading model
	glShadeModel(GL_SMOOTH) ;

	// enable depth testing, color materials and alpha blending (just used for eyes really..)
	glEnable(GL_DEPTH_TEST) ;

	// set clear information
	glClearColor(0.11, 0.13, 0.9, 0.0) ;
	glClearDepth(1.0) ;

	TogglePerspective(bSetPerspective) ;
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
