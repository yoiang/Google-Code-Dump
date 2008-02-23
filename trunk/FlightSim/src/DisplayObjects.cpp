#include "DisplayObjects.h"

Model AirportModel, CityModel ;	// ground models
GLuint iGrassName ;
Terrain BGTerrain[8] ;	// background mountains
GLUquadricObj *pSun = 0 ;	// sun and moon sphere
bool bTime ;	// proceed with time
GLfloat fSunAngle ;	// sun and moon's angle
int iMountMaxDepth = 2 ;	// maximum depth

#define TERRAIN_GRID_W 15	// terrain grid width
#define TERRAIN_GRID_H 15	// terrain grid height
int iGrid[TERRAIN_GRID_W][TERRAIN_GRID_H] ; // ground grid
Terrain *pTerrain = 0 ; // ground terrain

void SetSun(GLfloat fFactor)	// set lighting brightness
{
	GLfloat array_zero [] = { 0.0, 0.0, 0.0, 1.0 } ;

	GLfloat light_diffused [] = { 0.7 * fFactor, 0.7 * fFactor, 0.7 * fFactor, 1.0 } ;
	GLfloat light_specular [] = { 0.95 * fFactor, 0.95 * fFactor, 0.95 * fFactor, 1.0 } ;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffused) ;
	glLightfv(GL_LIGHT0, GL_AMBIENT, array_zero) ;
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular) ;

	GLfloat lmodel_ambient [] = { fFactor, fFactor, fFactor, 1.0 } ;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient) ;


	glClearColor(0.11 * fFactor, 0.13 * fFactor, 1.0 * fFactor, 0.0) ;
}

void InitGround()	// initialize the ground
{
	bTime = true ;

	ReadTexture("textures\\grass.bmp", iGrassName) ;

	fSunAngle = 0 ;

	for (int iTrav = 0 ; iTrav < 8 ; iTrav ++)
	{
		BGTerrain[iTrav].ptColor = Point(0, 1, 0) ;
		BGTerrain[iTrav].dAlpha = 1.0 ;
		BGTerrain[iTrav].fHeight = 20 ;
		BGTerrain[iTrav].fLength = 100 ;
		BGTerrain[iTrav].fWidth = 100 ;
		BGTerrain[iTrav].iMaxDepth = iMountMaxDepth ;
		BGTerrain[iTrav].GenMidpoint() ;
	}
	if (pSun != 0) gluDeleteQuadric(pSun) ;
	pSun = gluNewQuadric() ;
	gluQuadricDrawStyle(pSun, GLU_FILL) ;
	gluQuadricNormals(pSun, GLU_SMOOTH) ;

	SetSun(0.8) ;


	AirportModel.ReadFile("models\\airport.ml") ;
	CityModel.ReadFile("models\\city01.ml");

	float fChance ;
	int iX, iZ ;
	int iNumTerrain = 0 ;
	for (iX = 0 ; iX < TERRAIN_GRID_W ; iX ++)
	{
		for (iZ = 0 ; iZ < TERRAIN_GRID_H ; iZ ++)
		{
			if (iX < TERRAIN_GRID_W / 4 || iX > TERRAIN_GRID_W / 4 * 3 ||
				iZ < TERRAIN_GRID_H / 4 || iZ > TERRAIN_GRID_H / 4 * 3)
			{
				iGrid[iX][iZ] = iNumTerrain ;
				iNumTerrain ++ ;
			} else
			{
				fChance = float(rand()) / float(RAND_MAX) ;
				if (fChance > 0.95) iGrid[iX][iZ] = -2 ;
				else iGrid[iX][iZ] = -1 ;
			}
		}
	}
	if (pTerrain != 0) delete [] pTerrain ;

	pTerrain = new Terrain[iNumTerrain] ;
	if (pTerrain == 0) exit(-1) ;
	for (iTrav = 0 ; iTrav < iNumTerrain ; iTrav ++)
	{
		pTerrain[iTrav].ptColor = Point(0, 1, 0) ;
		pTerrain[iTrav].dAlpha = 1.0 ;
		pTerrain[iTrav].fHeight = 100 ;
		pTerrain[iTrav].fLength = 100 ;
		pTerrain[iTrav].fWidth = 100 ;
		pTerrain[iTrav].iMaxDepth = 3 ;
		pTerrain[iTrav].GenMidpoint() ;
	}

	iGrid[TERRAIN_GRID_W / 2][TERRAIN_GRID_H / 2] = -2 ;
}

void DisplayGround() // display the ground
{
	GLfloat array_zero [] = { 0.0, 0.0, 0.0, 1.0 } ;
	GLint iLightAngle = int(fSunAngle) % 360 ;

	if (bTime) // set lighting accordingly to time
	{

		if (iLightAngle > 270)
		{
			SetSun((GLfloat(iLightAngle % 90) / 90) * 0.6 + 0.2) ;			
		} else if (iLightAngle < 90)
		{
			SetSun((1 - GLfloat(iLightAngle) / 90) * 0.6 + 0.2) ;
		}
	}

	glPushMatrix() ;

//	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 50) ;
//	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50) ;

	GLfloat mat_ambient [] = { 0.9, 0.9, 0.9, 1.0 } ;
	GLfloat mat_emission [] = { 1.0, 1.0, 0.0, 1.0 } ;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient) ;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, array_zero) ;
	glMaterialfv(GL_FRONT, GL_SPECULAR, array_zero) ;
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission) ;

	// display sun
	glPushMatrix() ;
	glLoadIdentity() ;
	glRotatef(fSunAngle, 1.0, 0.0, 0.0) ;
	GLfloat light_position [] = { 0, 200.0, 0, 0.0 } ;
	GLfloat light_direction [] = { 0, -200, 0, 0.0} ;
	glLightfv(GL_LIGHT0, GL_POSITION, light_position) ;
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction) ;
	glPopMatrix() ;

	glColor3f(1.0, 1.0, 0.0) ;
	glPushMatrix() ;
	glRotatef(fSunAngle, 1.0, 0.0, 0.0) ;
	glTranslatef(light_position[0], light_position[1], light_position[2]) ;
	gluSphere(pSun, 5, 10, 10) ;
	
	// display moon
	glTranslatef(-2 * light_position[0], -2 * light_position[1], -2 * light_position[2]) ;
	GLfloat moon_mat_emission [] = { 0.7, 0.7, 0.7, 1.0 } ;
	glMaterialfv(GL_FRONT, GL_EMISSION, moon_mat_emission) ;
	glColor3fv(moon_mat_emission) ;
	glScalef(3, 3, 3) ;
	gluSphere(pSun, 5, 10, 10) ;

	glPopMatrix() ;

	// display background
	glMaterialfv(GL_FRONT, GL_EMISSION, array_zero) ;
	glPushMatrix() ;
	GLfloat fFacing = int(fCameraAngle[1] + fPlaneOrientation[1]) % 360 ;
	if (fFacing < 0) fFacing += 360 ;
	glTranslatef(200, -4, 200) ;
	if (fFacing < 104 || fFacing > 346) BGTerrain[0].Display() ;
	glTranslatef(0, 0, -200) ;
	if (fFacing > 13 && fFacing < 138) BGTerrain[1].Display() ;
	glTranslatef(0, 0, -200) ;
	if (fFacing > 55 && fFacing < 180) BGTerrain[2].Display() ;
	glTranslatef(-200, 0, 0) ;
	if (fFacing > 70 && fFacing < 226) BGTerrain[3].Display() ;
	glTranslatef(-200, 0, 0) ;
	if (fFacing > 150 && fFacing < 300) BGTerrain[4].Display() ;
	glTranslatef(0, 0, 200) ;
	if (fFacing > 220 || fFacing < 20) BGTerrain[5].Display() ;
	glTranslatef(0, 0, 200) ;
	if (fFacing > 275 || fFacing < 40) BGTerrain[6].Display() ;
	glTranslatef(200, 0, 0) ;
	if (fFacing > 311 || fFacing < 80) BGTerrain[7].Display() ;
	glPopMatrix() ;
	glColor3f(0, 1, 0) ;

	glClear(GL_DEPTH_BUFFER_BIT);

	// display grass
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, iGrassName); 
	glBegin(GL_POLYGON) ;
	glTexCoord2f(50.0 + fCameraX / 90, 50.0 + fCameraZ / 90); glVertex3f(200, -2, 200) ;
	glTexCoord2f(50.0 + fCameraX / 90, -50.0 + fCameraZ / 90); glVertex3f(200, -2, -200) ;
	glTexCoord2f(-50.0 + fCameraX / 90, -50.0 + fCameraZ / 90); glVertex3f(-200, -2, -200) ;
	glTexCoord2f(-50.0 + fCameraX / 90, 50.0 + fCameraZ / 90); glVertex3f(-200, -2, 200) ;
	glEnd() ;
	glDisable(GL_TEXTURE_2D);
	glClear(GL_DEPTH_BUFFER_BIT);

	glTranslatef(-fCameraX, -fCameraY, -fCameraZ) ;

	GLfloat model_mat_ambient [] = { 0.3, 0.3, 0.3, 1.0 } ;
	GLfloat model_mat_diffused [] = { 0.7, 0.7, 0.7, 1.0 } ;
	GLfloat model_mat_specular [] = { 0.3, 0.3, 0.3, 1.0 } ;
	glMaterialfv(GL_FRONT, GL_AMBIENT, model_mat_ambient) ;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, model_mat_diffused) ;
	glMaterialfv(GL_FRONT, GL_SPECULAR, model_mat_specular) ;
	int iX, iZ ;
	// display ground objects
	glTranslatef((TERRAIN_GRID_W / 2 +1) * -100, 0, (TERRAIN_GRID_H / 2) * 100) ;
	for (iX = 0 ; iX < TERRAIN_GRID_W ; iX ++)
	{
		glTranslatef(100, 0, 0) ;
		glTranslatef(0, 0, TERRAIN_GRID_H * -100) ;
		for (iZ = 0 ; iZ < TERRAIN_GRID_H ; iZ ++)
		{
			glTranslatef(0, 0, 100) ;
			if (iGrid[iX][iZ] == -2) AirportModel.Display(false) ;
			else if (iGrid[iX][iZ] == -1) CityModel.Display(false) ;
			else 
			{
				glPushMatrix() ;
				glTranslatef(-50, 0, -50) ;
				pTerrain[iGrid[iX][iZ]].Display() ;
				glPopMatrix() ;
			}
		}
	}

	glPopMatrix() ;
}

void CleanObjects()	// clean up the object information
{
	gluDeleteQuadric(pSun) ;
	if (pTerrain != 0) delete [] pTerrain ;
}