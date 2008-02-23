#include "Camera.h"

GLfloat fCameraDistance,			// keep track of camera distance from 0, 0, 0
		fCameraAngle[3] ;			// keep track of camera angle
double dDistanceScale ;

void InitCamera(GLfloat fInitialDistance)
{
	fCameraDistance = fInitialDistance ;
	fCameraAngle[0] = 20 ;
	fCameraAngle[1] = 180 ;
	fCameraAngle[2] = 0 ;
}

void SetCamera() // set the camera and lighting angle and location relative to each scene
{
	gluLookAt(0, 0, fCameraDistance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0) ;

	glRotatef(fCameraAngle[0], 1.0, 0.0, 0.0) ;
	glRotatef(fCameraAngle[1], 0.0, 1.0, 0.0) ;
	glRotatef(fCameraAngle[2], 0.0, 0.0, 1.0) ;
/*
	GLfloat light_position [] = { -20, 5, 20, 1.0 } ;
	GLfloat light_direction [] = { 20, -5, -20, 0.0} ;
	glLightfv(GL_LIGHT0, GL_POSITION, light_position) ;
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction) ;
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20) ;
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0) ;
*/
}