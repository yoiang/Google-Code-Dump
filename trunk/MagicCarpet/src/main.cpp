#include "main.h"

bool bPause ;
Map CurrentMap ;
Point ptSpellLocation ;
int iSpellTime ;
int iCasting = 0 ;
int iViewingDistance = 100 ;

void DisplayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	glLoadIdentity() ;

	glRotatef(-1.0*fCameraAngle[0], 1.0, 0.0, 0.0) ;
	glRotatef(-1.0*fCameraAngle[1], 0.0, 1.0, 0.0) ;
	glRotatef(fCameraAngle[2], 0.0, 0.0, 1.0) ;

	glTranslatef(0, -fCameraLocation[1], 0) ;

	CurrentMap.Display(Point(fCameraLocation[0], fCameraLocation[1], fCameraLocation[2]), 
						Point(fCameraAngle[0], fCameraAngle[1], fCameraAngle[2]), iViewingDistance) ;
	glFinish() ;
	glutSwapBuffers() ;
	glutPostRedisplay() ;
}

void KeyboardHandler (unsigned char cKey, int iX, int iY) // keyboard input handling function
{
	switch (cKey)
	{
	case '1' :
		iSpellTime = 40 ;
		ptSpellLocation = Point(fCameraLocation[0], 0, fCameraLocation[2]) ;
		iCasting = 1 ;
	break ;
	case '2' :
		iSpellTime = 20 ;
		ptSpellLocation = Point(fCameraLocation[0], 0, fCameraLocation[2]) ;
		iCasting = 2 ;
	break ;
	case '-' :
	case '_' :
		iViewingDistance -= CurrentMap.dMapScale ;
		if (iViewingDistance < 0) iViewingDistance = 0 ;

	break ;
	case '=' :
	case '+' :
		iViewingDistance += CurrentMap.dMapScale ;
		if (iViewingDistance < 0) iViewingDistance = 0 ;

	break ;
	case 'f' :
	case 'F' :
		ToggleFog(!bFog) ;
// 		ToggleFullscreen(!bFullscreen) ;
	break ;

	case 'i' : 
	case 'I' :
		InitCamera() ;
	break ;

	case 'l' : // toggle lighting
	case 'L' :
		ToggleLighting(!bLighting) ;
	break ;

	case 'p' :
	case 'P' :
		bPause = !bPause ;
	break ;

	case 'q' : // quit program
	case 'Q' :
		CurrentMap.Clear() ;
		exit(0) ;
	break ;

	case 'w' : // toggle wireframe
	case 'W' :
		ToggleFilling(!bFilling) ;
	break ;
	}
}

void SpecialKeyHandler(int key, int x, int y) // handle special keys
{
	GLfloat fRadians ;
	switch(key)
	{
	case GLUT_KEY_UP : 
		fRadians = fCameraAngle[1] * 3.1415 / 180.0 ;
		fCameraLocation[0] -= sin(fRadians) ;
		fCameraLocation[2] -= cos(fRadians) ;

		fRadians = fCameraAngle[0] * 3.1415 / 180.0 ;
		fCameraLocation[1] += sin(fRadians) ;
		fCameraLocation[1] += CurrentMap.CheckCollision(Point(fCameraLocation[0], fCameraLocation[1], fCameraLocation[2])) ;
	break ;

	case GLUT_KEY_LEFT :
		fRadians = fCameraAngle[1] * 3.1415 / 180.0 - 90;
		fCameraLocation[0] += sin(fRadians) ;
		fCameraLocation[2] += cos(fRadians) ;
		fCameraLocation[1] += CurrentMap.CheckCollision(Point(fCameraLocation[0], fCameraLocation[1], fCameraLocation[2])) ;
	break ;

	case GLUT_KEY_DOWN :
		fRadians = fCameraAngle[1] * 3.1415 / 180.0 ;
		fCameraLocation[0] += sin(fRadians) ;
		fCameraLocation[2] += cos(fRadians) ;

		fRadians = fCameraAngle[0] * 3.1415 / 180.0 ;
		fCameraLocation[1] -= sin(fRadians) ;
		fCameraLocation[1] += CurrentMap.CheckCollision(Point(fCameraLocation[0], fCameraLocation[1], fCameraLocation[2])) ;
	break ;

	case GLUT_KEY_RIGHT :
		fRadians = fCameraAngle[1] * 3.1415 / 180.0 + 90 ;
		fCameraLocation[0] += sin(fRadians) ;
		fCameraLocation[2] += cos(fRadians) ;
		fCameraLocation[1] += CurrentMap.CheckCollision(Point(fCameraLocation[0], fCameraLocation[1], fCameraLocation[2])) ;
	break ;
	}
}

void Initialize()
{
	srand(time(0)) ;

	bPause = false ;

//	CurrentMap.GenerateFlatMap(5E0, 20, 7, 7) ;
	CurrentMap.ReadRaw("maps\\terrainsmall.raw", 100, 100, 5, 0.5) ;
	CurrentMap.bTexture = true ;
	CurrentMap.SetLowHeight(40, "textures\\water.bmp") ;
	CurrentMap.SetMidHeight(80, "textures\\dirt.bmp") ;
	CurrentMap.SetHighHeight(221, "textures\\grass.bmp") ;

//	CurrentMap.ReadMap("maps\\test.map") ;

}

double Mag(double dCheck)
{
	if (dCheck < 0) return -1.0 * dCheck ;
	return dCheck ;
}

void CastGravityWell()
{
	Point ptRelativePos ;
	ptRelativePos.dVal[0] = ptSpellLocation.dVal[0] ;
	while (ptRelativePos.dVal[0] >= CurrentMap.dHoriSize) ptRelativePos.dVal[0] -= CurrentMap.dHoriSize ;
	ptRelativePos.dVal[1] = ptSpellLocation.dVal[1] ;
	ptRelativePos.dVal[2] = ptSpellLocation.dVal[2] ;
	while (ptRelativePos.dVal[2] >= CurrentMap.dVertSize) ptRelativePos.dVal[2] -= CurrentMap.dVertSize ;
	
	long lHoriIndex, lVertIndex ;
	lHoriIndex = floor(ptRelativePos.dVal[0] / CurrentMap.dMapScale) ;
	lVertIndex = floor(ptRelativePos.dVal[2] / CurrentMap.dMapScale) ;
	
	long lRange = floor(10 / CurrentMap.dMapScale) ;
	
	for (long lTravHori = -1 * lRange ; lTravHori < lRange ; lTravHori ++)
	{
		for (long lTravVert = -1 * lRange ; lTravVert < lRange ; lTravVert ++)
		{
			
			if (sqrt((lTravHori * lTravHori) + (lTravVert * lTravVert)) <= lRange)
			{
				
				CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex + 1,CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex + 1) + ((Mag(lTravHori) - lRange) + (Mag(lTravVert) - lRange)) * 0.5) ;
				if (CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex + 1) < 0) 
					CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex + 1,0.0) ;
				CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex + 1,CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex + 1) + ((Mag(lTravHori) - lRange) + (Mag(lTravVert) - lRange)) * 0.5) ;
				if (CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex + 1) < 0) 
					CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex + 1,0.0) ;
				CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex,CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex) + ((Mag(lTravHori) - lRange) + (Mag(lTravVert) - lRange)) * 0.5) ;
				if (CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex) < 0) 
					CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex,0.0) ;
				CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex,CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex) + ((Mag(lTravHori) - lRange) + (Mag(lTravVert) - lRange)) * 0.5) ;
				if (CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex) < 0) 
					CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex,0.0) ;
				
			}
		}
	}
}

void CastMountain()
{
	Point ptRelativePos ;
	ptRelativePos.dVal[0] = ptSpellLocation.dVal[0] ;
	while (ptRelativePos.dVal[0] >= CurrentMap.dHoriSize) ptRelativePos.dVal[0] -= CurrentMap.dHoriSize ;
	ptRelativePos.dVal[1] = ptSpellLocation.dVal[1] ;
	ptRelativePos.dVal[2] = ptSpellLocation.dVal[2] ;
	while (ptRelativePos.dVal[2] >= CurrentMap.dVertSize) ptRelativePos.dVal[2] -= CurrentMap.dVertSize ;
	
	long lHoriIndex, lVertIndex ;
	lHoriIndex = floor(ptRelativePos.dVal[0] / CurrentMap.dMapScale) ;
	lVertIndex = floor(ptRelativePos.dVal[2] / CurrentMap.dMapScale) ;
	
	long lRange = floor(15 / CurrentMap.dMapScale) ;
	
	for (long lTravHori = -1 * lRange ; lTravHori < lRange ; lTravHori ++)
	{
		for (long lTravVert = -1 * lRange ; lTravVert < lRange ; lTravVert ++)
		{
			
			if (sqrt((lTravHori * lTravHori) + (lTravVert * lTravVert)) <= lRange)
			{
				
				CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex + 1,CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex + 1) + ((Mag(lTravHori) - lRange) + (Mag(lTravVert) - lRange)) * -0.1) ;
				if (CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex + 1) < 0) 
					CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex + 1,0.0) ;
				CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex + 1,CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex + 1) + ((Mag(lTravHori) - lRange) + (Mag(lTravVert) - lRange)) * -0.1) ;
				if (CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex + 1) < 0) 
					CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex + 1,0.0) ;
				CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex,CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex) + ((Mag(lTravHori) - lRange) + (Mag(lTravVert) - lRange)) * -0.1) ;
				if (CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex) < 0) 
					CurrentMap.Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex,0.0) ;
				CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex,CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex) + ((Mag(lTravHori) - lRange) + (Mag(lTravVert) - lRange)) * -0.1) ;
				if (CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex) < 0) 
					CurrentMap.Height(lTravHori + lHoriIndex, lTravVert + lVertIndex,0.0) ;
				
			}
		}
	}
	fCameraLocation[1] += CurrentMap.CheckCollision(Point(fCameraLocation[0], fCameraLocation[1], fCameraLocation[2])) ;
}

void UpdatePosition(int iParam)	
{
	if (!bPause)
	{
		if (iCasting)
		{
			iSpellTime -- ;
			if (iSpellTime == 0) iCasting = 0 ;
			switch(iCasting)
			{
			case 1 :
				CastGravityWell() ;
			break ;
			case 2 :
				CastMountain() ;
			break ;
			}
		}
	}
	glutTimerFunc(10, UpdatePosition, 0);
}

int main(int argc, char **argv)
{
	InitGLUTWindow(argc, argv, "Magic Carpet", 500, 500) ;
	InitDisplay(true, true, false) ; 
	InitCamera() ;
	InitMouse() ;

	glutDisplayFunc(DisplayHandler) ;
	glutKeyboardFunc(KeyboardHandler) ;
	glutSpecialFunc(SpecialKeyHandler) ;

	Initialize() ;

	glutTimerFunc(10, UpdatePosition, 0);

	glutMainLoop() ;

	return 0 ;
}