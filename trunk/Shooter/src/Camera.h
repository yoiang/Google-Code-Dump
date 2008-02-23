#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <windows.h>
#include <gl\Glu.h>

extern	
GLfloat fCameraDistance,			// keep track of camera distance from 0, 0, 0
		fCameraAngle[3] ;			// keep track of camera angle

extern
double dDistanceScale ;

void InitCamera(GLfloat fInitialDistance) ;
void SetCamera() ; // set the camera and lighting angle and location relative to each scene

#endif