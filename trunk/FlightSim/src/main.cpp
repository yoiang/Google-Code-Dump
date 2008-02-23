// Ian Grossberg
// 3D Computer Graphics
// Project 04
// Fall 2002

#include "GLUTStuff.h"
#include "Terrain.h"
#include "DisplayObjects.h"

#include <math.h>
Model CockpitModel ;	// cockpit model
bool bCockpit, bPause ;	// toggles
Point ptVelocity ;	// plane's velocity

void InitVars() // initialize and setup all variables
{
	bCockpit = true ;
	bPause = false ;
	CockpitModel.ReadFile("models\\cockpit.ml") ;

	ptVelocity = 0.0 ;

	iNumLights = 1 ;

	InitGround() ;

	glEnable(GL_CULL_FACE) ;
	glCullFace(GL_BACK) ;
}

void DisplayHandler () // display callback function
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	glLoadIdentity() ;

	// set up camera angle
	glRotatef(-1.0*fCameraAngle[0], 1.0, 0.0, 0.0) ;
	glRotatef(-1.0*fCameraAngle[1], 0.0, 1.0, 0.0) ;
	glRotatef(fCameraAngle[2], 0.0, 0.0, 1.0) ;

	// set up plane orientation
	glRotatef(-1.0*fPlaneOrientation[0], 1.0, 0.0, 0.0) ;
	glRotatef(-1.0*fPlaneOrientation[1], 0.0, 1.0, 0.0) ;
	glRotatef(fPlaneOrientation[2], 0.0, 0.0, 1.0) ;

	gluLookAt(0, 0, 0, 0, 0.0, 1.0, 0, 1.0, 0) ;
	DisplayGround() ; // display ground

	// display cockpit
	if (bCockpit)
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		
		glLoadIdentity() ;
		
		glPushMatrix() ;
		glRotatef(-1.0*fCameraAngle[0], 1.0, 0.0, 0.0) ;
		glRotatef(-1.0*fCameraAngle[1], 0.0, 1.0, 0.0) ;
		glRotatef(fCameraAngle[2], 0.0, 0.0, 1.0) ;
		
		CockpitModel.Display(false) ;
		
		glRotatef(-1.0*fPlaneOrientation[0], 1.0, 0.0, 0.0) ;
		glRotatef(-1.0*fPlaneOrientation[1], 0.0, 1.0, 0.0) ;
		glRotatef(fPlaneOrientation[2], 0.0, 0.0, 1.0) ;
		
		glPopMatrix() ;
		
	}
	gluLookAt(0, 0, 0, 0, 0.0, 1.0, 0, 1.0, 0) ;

	glFinish() ;
	glutSwapBuffers() ;
	glutPostRedisplay() ;
}

void KeyboardHandler (unsigned char cKey, int iX, int iY) // keyboard input handling function
{
	GLfloat fRadians ;
	switch (cKey)
	{
	case 'p' : // toggle pause
	case 'P' : 
		bPause = !bPause ;
	break ;

	case '/' : // toggle filling
	case '?' :
		ToggleFilling(!bFilling) ;
	break ;

	case '.' : // toggle lighting
	case '>' :
		ToggleLighting(!bLighting) ;
	break ;

	case 'g' :	// toggle fullscreen
	case 'G' :
		ToggleFullscreen(!bFullscreen) ;
	break ;

	case 'i' :  // set initial position and velocity
	case 'I' :
		InitCamera() ;
		ptVelocity = 0.0 ;
	break ;

	case 'f' : // move forward
	case 'F' : 
		ptVelocity = 0.0 ;
		fRadians = fPlaneOrientation[1] * 3.1415 / 180.0 ;
		fCameraX += sin(fRadians) ;
		fCameraZ += cos(fRadians) ;

		fRadians = fPlaneOrientation[0] * 3.1415 / 180.0 ;
		if (fCameraY + sin(fRadians) > 3) fCameraY += sin(fRadians) ;
	break ;

	case 'a' :	// decrease velocity
	case 'A' :
		fPlaneOrientation[2] -= 10.0 ;
	break ;

	case 'd' :	// increase velocity
	case 'D' :
		fPlaneOrientation[2] += 10.0 ;
	break ;

	case 'o' :  // toggle time of day
	case 'O' :
		bTime = !bTime ;
	break ;

	case 'w' :	// increase velocity
	case 'W' :
		ptVelocity.dVal[2] += 2 ;
	break ;

	case 's' :	// decrease velocity
	case 'S' :
		ptVelocity.dVal[2] -= 2 ;
	break ;

	case 'c' :	// toggle cockpit
	case 'C' :
		bCockpit = !bCockpit ;
	break ;

	case 'q' : // quit program
	case 'Q' :
		CleanObjects() ;
		exit(0) ;
	break ;
	}
}

void SpecialKeyHandler(int key, int x, int y) // handle special keys
{
	switch(key)
	{
	case GLUT_KEY_UP : // rotate pitch down
		fPlaneOrientation[0] -= 10.0 ;
	break ;
	case GLUT_KEY_LEFT : // rotate yaw left
		fPlaneOrientation[1] += 10.0 ;
	break ;
	case GLUT_KEY_DOWN : // rotate pitch up
		fPlaneOrientation[0] += 10.0 ;
	break ;
	case GLUT_KEY_RIGHT : // rotate yaw right
		fPlaneOrientation[1] -= 10.0 ;
	break ;
	}
}

void UpdatePosition(int iParam)	// update position of the plane
{
	if (!bPause)
	{
		GLfloat fRadians = fPlaneOrientation[1] * 3.1415 / 180.0 ;
		fCameraX += ptVelocity.dVal[2] * sin(fRadians) ;
		fCameraZ += ptVelocity.dVal[2] * cos(fRadians) ;

		fRadians = fPlaneOrientation[0] * 3.1415 / 180.0 ;
		if (fCameraY + sin(fRadians) > 3) fCameraY += ptVelocity.dVal[2] * sin(fRadians) ;

//		fCameraY -= 0.1 ;
//		fPlaneOrientation[0] += ptVelocity.dVal[2] * 0.1 ;

//		printf("%f %f %f\n", fCameraX, fCameraY, fCameraZ) ;

		if (bTime) fSunAngle += 0.05 ;
	}
	glutTimerFunc(20, UpdatePosition, 0);
}

int main(int argc, char **argv)
{
	InitGLUTWindow(argc, argv, "Scene", 400, 400) ;
	InitDisplay(true, true, true) ; // initialize variables and display modes
	InitMouse () ;
	InitCamera() ;
	glEnable(GL_AUTO_NORMAL) ;
	glEnable(GL_NORMALIZE) ;

	InitVars() ;
	ToggleLighting(true) ;

	glutDisplayFunc(DisplayHandler) ;

 	glutKeyboardFunc(KeyboardHandler) ;
	glutSpecialFunc(SpecialKeyHandler) ;

	glutTimerFunc(20, UpdatePosition, 0);

 	glutMainLoop() ;

	return 0 ;
 }