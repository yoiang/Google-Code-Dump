#include "Map.h"

Map::Map()
{
	pHeightMap = 0 ;

	bTexture = false ;
	bEdging = false ;

	lHoriLen = 0 ;
	lVertLen = 0 ;
	dHoriSize = 0 ;
	dVertSize = 0 ;
	dMapScale = 0 ;

	iLowTexName = 0 ;
	iMidTexName = 0 ;
	iHighTexName = 0 ;
	dLowHeight = 0 ;
	dMidHeight = 0 ; 
	dHighHeight = 0 ;
}

Map::~Map()
{
	Clear() ;
}

void Map::CreateMap(long lHori, long lVert)
{
	if (pHeightMap != 0) Clear() ;

	lHoriLen = lHori ;
	lVertLen = lVert ;

//	pHeightMap = new double* [lHori] ;
//	for (long lTrav = 0 ; lTrav < lHori ; lTrav ++)
//		pHeightMap[lTrav] = new double [lVert] ;

	pHeightMap = new double [lHori * lVert] ;
}

void Map::Clear()
{
	if (pHeightMap != 0) 
	{
//		for (long lTrav = 0 ; lTrav < lHoriLen ; lTrav ++)
//			delete [] (pHeightMap[lTrav]) ;
//		delete [] pHeightMap ;

		delete [] pHeightMap ;
	}


	pHeightMap = 0 ;

	bTexture = false ;

	lHoriLen = 0 ;
	lVertLen = 0 ;
	dHoriSize = 0 ;
	dVertSize = 0 ;
	dMapScale = 0 ;

	// clear textures here
	iLowTexName = 0 ;
	iMidTexName = 0 ;
	iHighTexName = 0 ;
	dLowHeight = 0 ;
	dMidHeight = 0 ; 
	dHighHeight = 0 ;
}

void Map::GenerateFlatMap(double dScale, double dHeight, long lHori, long lVert)
{
	if (lHori < 1 || lVert < 1 || dScale <= 0) return ;

	dMapScale = dScale ;
	dHoriSize = lHori * dScale ;
	dVertSize = lVert * dScale ;

	CreateMap(lHori, lVert) ;

	for (long lTravHori = 0 ; lTravHori < lHori ; lTravHori ++)
	{
		for (long lTravVert = 0 ; lTravVert < lVert ; lTravVert ++)
		{
			Height(lTravHori, lTravVert, dHeight) ;
		}
	}
}

int Map::ReadRaw(char *szFilename, long lHori, long lVert, double dScale, double dScaleHeight)
{
	dMapScale = dScale ;

	if (lHori < 1 || lVert < 1 || dMapScale <= 0) return 2 ;

	CreateMap(lHori, lVert) ;

	FILE *pMapFile = fopen(szFilename, "rb") ;
	if (pMapFile == 0) return 1 ;

	dHoriSize = lHoriLen * dMapScale ;
	dVertSize = lVertLen * dMapScale ;

	long lTravHori, lTravVert ;
	unsigned char cTemp ;
	for (lTravHori = 0 ; lTravHori < lHoriLen ; lTravHori ++)
	{
		for (lTravVert = 0 ; lTravVert < lVertLen ; lTravVert ++)
		{
			fscanf(pMapFile, "%c", &cTemp) ;
			Height(lTravHori, lTravVert, float(int(cTemp)) * dScaleHeight) ;
		}
	}

	fclose(pMapFile) ;

	return 0 ;
}

int Map::ReadMap(char *szFilename)
{
	char szTexFilename[256] ;
	FILE *pMapFile = fopen(szFilename, "r") ;
	if (pMapFile == 0) return 1 ;

	double dHeightScale ;

	fscanf(pMapFile, "%lf %lf %i %i %i", &dMapScale, &dHeightScale, &lVertLen, &lHoriLen, &bTexture) ;
	if (lHoriLen < 1 || lVertLen < 1 || dHeightScale <= 0 || dMapScale <= 0) 
	{
		fclose(pMapFile) ;
		return 2 ;
	}

	if (bTexture)
	{
		fscanf(pMapFile, "%lf %s", &dLowHeight, szTexFilename) ;
		ReadTexture(szTexFilename, iLowTexName) ;
		fscanf(pMapFile, "%lf %s", &dMidHeight, szTexFilename) ;
		ReadTexture(szTexFilename, iMidTexName) ;
		fscanf(pMapFile, "%lf %s", &dHighHeight, szTexFilename) ;
		ReadTexture(szTexFilename, iHighTexName) ;
	}

	dLowHeight *= dHeightScale ;
	dMidHeight *= dHeightScale ;
	dHighHeight *= dHeightScale ;

	CreateMap(lHoriLen, lVertLen) ;

	dHoriSize = lHoriLen * dMapScale ;
	dVertSize = lVertLen * dMapScale ;

	long lTravHori, lTravVert ;
	double dRead ;
	for (lTravHori = 0 ; lTravHori < lHoriLen ; lTravHori ++)
	{
		for (lTravVert = 0 ; lTravVert < lVertLen ; lTravVert ++)
		{
			fscanf(pMapFile, "%lf", &dRead) ;
			Height(lTravHori, lTravVert, dRead * dHeightScale) ;
		}
	}

	fclose(pMapFile) ;

	return 0 ;
}

int Map::SetLowHeight(double dHeight, char *szTexFilename)
{
	dLowHeight = dHeight ;
	ReadTexture(szTexFilename, iLowTexName) ;
	return 0 ;
}

int Map::SetMidHeight(double dHeight, char *szTexFilename)
{
	dMidHeight = dHeight ;
	ReadTexture(szTexFilename, iMidTexName) ;
	return 0 ;
}

int Map::SetHighHeight(double dHeight, char *szTexFilename)
{
	dHighHeight = dHeight ;
	ReadTexture(szTexFilename, iHighTexName) ;
	return 0 ;
}


double Map::CheckCollision(Point ptCameraPosition)
{
	Point ptRelativePos ;
	ptRelativePos.dVal[0] = ptCameraPosition.dVal[0] ;
	while (ptRelativePos.dVal[0] >= dHoriSize) ptRelativePos.dVal[0] -= dHoriSize ;
	ptRelativePos.dVal[1] = ptCameraPosition.dVal[1] ;
	ptRelativePos.dVal[2] = ptCameraPosition.dVal[2] ;
	while (ptRelativePos.dVal[2] >= dVertSize) ptRelativePos.dVal[2] -= dVertSize ;

	long lHoriIndex, lVertIndex ;
	lHoriIndex = floor(ptRelativePos.dVal[0] / dMapScale) ;
	lVertIndex = floor(ptRelativePos.dVal[2] / dMapScale) ;

	if (ptRelativePos.dVal[1] <= Height(lHoriIndex, lVertIndex) + 1)
		ptRelativePos.dVal[1] = Height(lHoriIndex, lVertIndex) + 2 ;
	if (ptRelativePos.dVal[1] <= Height(lHoriIndex + 1, lVertIndex) + 1)
		ptRelativePos.dVal[1] = Height(lHoriIndex + 1, lVertIndex) + 2 ;
	if (ptRelativePos.dVal[1] <= Height(lHoriIndex + 1, lVertIndex + 1) + 1)
		ptRelativePos.dVal[1] = Height(lHoriIndex + 1, lVertIndex + 1) + 2 ;
	if (ptRelativePos.dVal[1] <= Height(lHoriIndex, lVertIndex + 1) + 1)
		ptRelativePos.dVal[1] = Height(lHoriIndex, lVertIndex + 1) + 2 ;

	return ptRelativePos.dVal[1] - ptCameraPosition.dVal[1] ;
}

double Map::Height(long lHori, long lVert)
{
	while (lHori < 0) lHori += lHoriLen ;
	while (lHori >= lHoriLen) lHori -= lHoriLen ;
	while (lVert < 0) lVert += lVertLen ;
	while (lVert >= lVertLen) lVert -= lVertLen ;	
	return pHeightMap[lHori + lVert * lHoriLen] ;
}

double Map::Height(long lHori, long lVert, double dHeight)
{
	while (lHori < 0) lHori += lHoriLen ;
	while (lHori >= lHoriLen) lHori -= lHoriLen ;
	while (lVert < 0) lVert += lVertLen ;
	while (lVert >= lVertLen) lVert -= lVertLen ;	
	return (pHeightMap[lHori + lVert * lHoriLen] = dHeight) ;
}

void Map::Display(Point ptCameraPosition, Point ptCameraOrientation, double dRange)
{
	Point ptRelativePos ;
	ptRelativePos.dVal[0] = ptCameraPosition.dVal[0] ;
	while (ptRelativePos.dVal[0] >= dHoriSize) ptRelativePos.dVal[0] -= dHoriSize ;
	ptRelativePos.dVal[1] = ptCameraPosition.dVal[1] ;
	ptRelativePos.dVal[2] = ptCameraPosition.dVal[2] ;
	while (ptRelativePos.dVal[2] >= dVertSize) ptRelativePos.dVal[2] -= dVertSize ;

	long lHoriIndex, lVertIndex ;
	lHoriIndex = floor(ptRelativePos.dVal[0] / dMapScale) ;
	lVertIndex = floor(ptRelativePos.dVal[2] / dMapScale) ;
	double dHoriRemainder, dVertRemainder ;
	dHoriRemainder = ptRelativePos.dVal[0] - double(lHoriIndex) * dMapScale ;//floor(ptRelativePos.dVal[0]) ;
	dVertRemainder = ptRelativePos.dVal[2] - double(lVertIndex) * dMapScale ;//floor(ptRelativePos.dVal[2]) ;

	long lRange = floor(dRange / dMapScale) ;

	double dHeights[4], dMaxHeight ;
	for (long lTravHori = -1 * lRange ; lTravHori < lRange ; lTravHori ++)
	{
		for (long lTravVert = -1 * lRange ; lTravVert < lRange ; lTravVert ++)
		{

			if (sqrt((lTravHori * lTravHori) + (lTravVert * lTravVert)) <= lRange)
			{

				dHeights[0] = Height(lTravHori + lHoriIndex, lTravVert + lVertIndex + 1) ;
				dHeights[1] = Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex + 1) ;
				dHeights[2] = Height(lTravHori + lHoriIndex + 1, lTravVert + lVertIndex) ;
				dHeights[3] = Height(lTravHori + lHoriIndex, lTravVert + lVertIndex) ;

				if (bTexture)
				{
					glColor3f(1, 1, 1) ;
					dMaxHeight = dHeights[0] ;
					for (int iTrav = 1 ; iTrav < 4 ; iTrav ++)
						if (dHeights[iTrav] > dMaxHeight) dMaxHeight = dHeights[iTrav] ;

					glEnable(GL_TEXTURE_2D);
					if (dMaxHeight <= dLowHeight) 
					{
						glBindTexture(GL_TEXTURE_2D, iLowTexName);

						if (bFilling) glBegin(GL_QUADS);
						else glBegin(GL_LINE_STRIP) ;
						
						if (bEdging && dHeights[0] == dLowHeight)	glTexCoord2f(0,0); 
						else glTexCoord2f(0.3,0.3);
						if (dHeights[0] < dLowHeight) glVertex3f(lTravHori * dMapScale - dHoriRemainder, dLowHeight, (lTravVert + 1) * dMapScale - dVertRemainder) ;
						else glVertex3f(lTravHori * dMapScale - dHoriRemainder, dHeights[0], (lTravVert + 1) * dMapScale - dVertRemainder) ;

						if (bEdging && dHeights[1] == dLowHeight)	glTexCoord2f(0,1); 
						else glTexCoord2f(0.3,0.7); 
						if (dHeights[1] < dLowHeight) glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dLowHeight, (lTravVert + 1) * dMapScale - dVertRemainder) ;
						else glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dHeights[1], (lTravVert + 1) * dMapScale - dVertRemainder) ;

						if (bEdging && dHeights[2] == dLowHeight)	glTexCoord2f(1,1); 
						else glTexCoord2f(0.7,0.7); 
						if (dHeights[2] < dLowHeight) glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dLowHeight, lTravVert * dMapScale - dVertRemainder) ; 
						else glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dHeights[2], lTravVert * dMapScale - dVertRemainder) ;

						if (bEdging && dHeights[3] == dLowHeight)	glTexCoord2f(1,0); 
						else glTexCoord2f(0.7,0.3); 
						if (dHeights[3] < dLowHeight) glVertex3f(lTravHori * dMapScale - dHoriRemainder, dLowHeight, lTravVert * dMapScale - dVertRemainder) ;
						else glVertex3f(lTravHori * dMapScale - dHoriRemainder, dHeights[3], lTravVert * dMapScale - dVertRemainder) ;

						glDisable(GL_TEXTURE_2D) ;
					} else if (dMaxHeight <= dMidHeight) 
					{
						glBindTexture(GL_TEXTURE_2D, iMidTexName) ;

						if (bFilling) glBegin(GL_QUADS);
						else glBegin(GL_LINE_STRIP) ;
						
						if (bEdging && dHeights[0] == dMidHeight)	glTexCoord2f(0,0); 
						else glTexCoord2f(0.3,0.3); 
						if (dHeights[0] < dLowHeight) glVertex3f(lTravHori * dMapScale - dHoriRemainder, dLowHeight, (lTravVert + 1) * dMapScale - dVertRemainder) ;
						else glVertex3f(lTravHori * dMapScale - dHoriRemainder, dHeights[0], (lTravVert + 1) * dMapScale - dVertRemainder) ;
						if (bEdging && dHeights[1] == dMidHeight)	glTexCoord2f(0,1); 
						else glTexCoord2f(0.3,0.7); 
						if (dHeights[1] < dLowHeight) glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dLowHeight, (lTravVert + 1) * dMapScale - dVertRemainder) ;
						else glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dHeights[1], (lTravVert + 1) * dMapScale - dVertRemainder) ;
						if (bEdging && dHeights[2] == dMidHeight)	glTexCoord2f(1,1); 
						else glTexCoord2f(0.7,0.7); 
						if (dHeights[2] < dLowHeight) glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dLowHeight, lTravVert * dMapScale - dVertRemainder) ; 
						else glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dHeights[2], lTravVert * dMapScale - dVertRemainder) ;
						if (bEdging && dHeights[3] == dMidHeight)	glTexCoord2f(1,0); 
						else glTexCoord2f(0.7,0.3); 
						if (dHeights[3] < dLowHeight) glVertex3f(lTravHori * dMapScale - dHoriRemainder, dLowHeight, lTravVert * dMapScale - dVertRemainder) ;
						else glVertex3f(lTravHori * dMapScale - dHoriRemainder, dHeights[3], lTravVert * dMapScale - dVertRemainder) ;
						glDisable(GL_TEXTURE_2D) ;
					} else 
					{
						glBindTexture(GL_TEXTURE_2D, iHighTexName) ;

						if (bFilling) glBegin(GL_QUADS);
						else glBegin(GL_LINE_STRIP) ;
						
						if (bEdging && dHeights[0] == dHighHeight)	glTexCoord2f(0,0); 
						else glTexCoord2f(0.3,0.3); 
						glVertex3f(lTravHori * dMapScale - dHoriRemainder, dHeights[0], (lTravVert + 1) * dMapScale - dVertRemainder) ;
						if (bEdging && dHeights[1] == dHighHeight)	glTexCoord2f(0,1); 
						else glTexCoord2f(0.3,0.7); 
						glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dHeights[1], (lTravVert + 1) * dMapScale - dVertRemainder) ;
						if (bEdging && dHeights[2] == dHighHeight)	glTexCoord2f(1,1); 
						else glTexCoord2f(0.7,0.7); 
						glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dHeights[2], lTravVert * dMapScale - dVertRemainder) ;
						if (bEdging && dHeights[3] == dHighHeight)	glTexCoord2f(1,0); 
						else glTexCoord2f(0.7,0.3); 
						glVertex3f(lTravHori * dMapScale - dHoriRemainder, dHeights[3], lTravVert * dMapScale - dVertRemainder) ;
						glDisable(GL_TEXTURE_2D) ;
					}

				} else
				{
					if (bFilling) glBegin(GL_QUADS);
					else glBegin(GL_LINE_STRIP) ;

					glColor3f(RandomPercent() * 1, RandomPercent() * 1, RandomPercent() * 1) ;
					glVertex3f(lTravHori * dMapScale - dHoriRemainder, dHeights[0], (lTravVert + 1) * dMapScale - dVertRemainder) ;
					glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dHeights[1], (lTravVert + 1) * dMapScale - dVertRemainder) ;
					glVertex3f((lTravHori + 1) * dMapScale - dHoriRemainder, dHeights[2], lTravVert * dMapScale - dVertRemainder) ;
					glVertex3f(lTravHori * dMapScale - dHoriRemainder, dHeights[3], lTravVert * dMapScale - dVertRemainder) ;
				}
				glEnd();
			}
		}
	}
	glEnd() ;
}
