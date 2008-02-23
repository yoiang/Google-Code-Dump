#include "GLStuff.h"

int iWinHeight,	// window height
	iWinWidth ;	// window width

bool	bLighting = false,			// toggle lighting
		bPerspective = false,		// toggle perspective and orthographic mode 
		bFilling = false ;			// toggle filling
/*
void EnableLights()
{
	for (int i = 0 ; i < iNumLights ; i ++)
	{
		glEnable(0x4000 + i) ;
	}
}

void DisableLights()
{
	for (int i = 0 ; i < iNumLights ; i ++)
	{
		glDisable(0x4000 + i) ;
	}
}

void SetLights()
{
	// set up lighting
	GLfloat light_diffused [4] ;
	GLfloat light_ambient [4] ;
	GLfloat light_specular [4] ;
	GLint iLightNumber = 0x4000 ;
	GLint iCount = 0 ;
	Body *pTrav = pBodyListHead ;
	while (pTrav != 0 && iCount < iNumLights)
	{
		light_diffused[0] = 0.8 * pTrav->fRed ;
		light_diffused[1] = 0.8 * pTrav->fGreen ;
		light_diffused[2] = 0.8 * pTrav->fBlue ;
		light_diffused[3] = 1.0 ;

		light_ambient[0] = 0.8 * pTrav->fRed ;
		light_ambient[1] = 0.8 * pTrav->fGreen ;
		light_ambient[2] = 0.8 * pTrav->fBlue ;
		light_ambient[3] = 1.0 ;

		light_specular[0] = 0.4 * pTrav->fRed ;
		light_specular[1] = 0.4 * pTrav->fGreen ;
		light_specular[2] = 0.4 * pTrav->fBlue ;
		light_specular[3] = 1.0 ;

		glEnable(iLightNumber) ;
		glLightfv(iLightNumber, GL_DIFFUSE, light_diffused) ;
		glLightfv(iLightNumber, GL_AMBIENT, light_ambient) ;
		glLightfv(iLightNumber, GL_SPECULAR, light_specular) ;

		glLightf(iLightNumber, GL_CONSTANT_ATTENUATION, 0) ;
		glLightf(iLightNumber, GL_LINEAR_ATTENUATION, 1) ;
		iLightNumber ++ ;
		iCount ++ ;
	}
}
*/
void ToggleLighting(bool bSetLighting)
{
	int iEnableLights = 0x4000 ;
	bLighting = bSetLighting ;
	if (bLighting)
	{
		glEnable(GL_LIGHTING) ;

//		EnableLights() ;

		glEnable(GL_COLOR_MATERIAL) ;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;

	}	else
	{
		glDisable(GL_LIGHTING) ;

//		DisableLights() ;

		glDisable(GL_COLOR_MATERIAL) ;
		glDisable(GL_BLEND) ;
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
		glOrtho(-5, 5, -5, 5, 1.0, 200.0) ;
	}
	glMatrixMode(GL_MODELVIEW) ;
}

void ReshapeHandler (int iWidth, int iHeight) // resizing window callback function
{
	iWinWidth = iWidth ;
	iWinHeight = iHeight ;

	glViewport(0, 0, (GLsizei) iWidth, (GLsizei) iHeight) ;

	TogglePerspective(bPerspective) ;
}

void InitDisplay(bool bSetFilling, bool bSetPerspective, bool bSetLighting) // initialize variables and display modes
{
	glLineWidth(1.0) ;

	GLfloat lmodel_ambient [] = { 0.2, 0.2, 0.2, 1.0 } ;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient) ;

	ToggleLighting(bSetLighting) ;
	
	ToggleFilling(bSetFilling) ;

	// set shading model
	glShadeModel(GL_SMOOTH) ;

	// enable depth testing, color materials and alpha blending (just used for eyes really..)
	glEnable(GL_DEPTH_TEST) ;

	// set clear information
	glClearColor(0.0, 0.0, 0.0, 0.0) ;
	glClearDepth(1.0) ;

	TogglePerspective(bSetPerspective) ;
}

void InitGLUT(int argc, char **argv, char *szWindowName, int iSetWinWidth, int iSetWinHeight)
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
