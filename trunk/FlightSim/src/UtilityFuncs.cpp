#include "UtilityFuncs.h"

AUX_RGBImageRec *CreateImageRec(int iSetSizeX, int iSetSizeY, bool bAlpha)
{
	AUX_RGBImageRec *pNewImage = (AUX_RGBImageRec *)malloc(sizeof(AUX_RGBImageRec)) ;
	pNewImage->sizeX = iSetSizeX ;
	pNewImage->sizeY = iSetSizeY ;
	if (bAlpha)	pNewImage->data = (unsigned char*)malloc(4 * iSetSizeX * iSetSizeY) ;
	else pNewImage->data = (unsigned char*)malloc(3 * iSetSizeX * iSetSizeY) ;
	return pNewImage ;
}

void DeleteImageRec(AUX_RGBImageRec *pDeleteImage)
{
	free(pDeleteImage->data) ;
	free(pDeleteImage) ;
}

AUX_RGBImageRec *LoadBMP(char *szFilename)			
{
	if (!szFilename) return 0;									

	FILE *pFile = 0;								
	pFile = fopen(szFilename,"r");
	if (pFile)											
	{
		fclose(pFile);									
		return auxDIBImageLoad(szFilename);				
	}
	return 0;										
}

void CropImage(AUX_RGBImageRec *pReadImage, AUX_RGBImageRec *pDestination, int iX, int iY, int iWidth, int iHeight)
{
	int iTravX, iTravY ;
	int iRead, iTestX, iTestY, iPlace ;
	for (iTravY = 0 ; iTravY < pDestination->sizeY ; ++iTravY)
	{
		for (iTravX = 0 ; iTravX < pDestination->sizeX ; ++iTravX)
		{
			iTestX = iX + iTravX ;
			iTestY = iY + iTravY ;
			iPlace = (iTravX + iTravY * pDestination->sizeX) * 3 ;
			if (iTestX > 0 && iTestX < pReadImage->sizeX && iTestY > 0 && iTestY < pReadImage->sizeY)
			{
				iRead = ((iTestX) + (iTestY) * pReadImage->sizeX) * 3 ;
				pDestination->data[iPlace] = pReadImage->data[iRead] ;
				pDestination->data[iPlace + 1] = pReadImage->data[iRead + 1] ;
				pDestination->data[iPlace + 2] = pReadImage->data[iRead + 2] ;
			} else
			{
				pDestination->data[iPlace] = 0 ;
				pDestination->data[iPlace + 1] = 0 ;
				pDestination->data[iPlace + 2] = 0 ;
			}
		}
	}
}

// crop an image record into a smaller image record
void CropImageAlpha(AUX_RGBImageRec *pReadImage, // image record to crop
					AUX_RGBImageRec *pMaskImage, // alpha mask image record
					AUX_RGBImageRec *pDestination, // image to write to
					int iX,			// x location to crop
					int iY,			// y location to crop
					int iWidth,		// cropping width
					int iHeight)	// cropping height
{
	int iTravX, iTravY ;
	int iRead, iTestX, iTestY, iPlace ;
	for (iTravY = 0 ; iTravY < pDestination->sizeY ; ++iTravY)
	{
		for (iTravX = 0 ; iTravX < pDestination->sizeX ; ++iTravX)
		{
			iTestX = iX + iTravX ;
			iTestY = iY + iTravY ;
			iPlace = (iTravX + iTravY * pDestination->sizeX) * 4 ;
			if (iTestX > 0 && iTestX < pReadImage->sizeX && iTestY > 0 && iTestY < pReadImage->sizeY)
			{
				iRead = ((iTestX) + (iTestY) * pReadImage->sizeX) * 3 ;
				pDestination->data[iPlace] = pReadImage->data[iRead] ;
				pDestination->data[iPlace + 1] = pReadImage->data[iRead + 1] ;
				pDestination->data[iPlace + 2] = pReadImage->data[iRead + 2] ;
				pDestination->data[iPlace + 3] = pMaskImage->data[iRead] ;
			} else
			{
				pDestination->data[iPlace] = 0 ;
				pDestination->data[iPlace + 1] = 0 ;
				pDestination->data[iPlace + 2] = 0 ;
				pDestination->data[iPlace + 3] = 0 ;
			}
		}
	}
}

int CheckContained(int iX, int iY, int iBottom, int iLeft, int iTop, int iRight)
{
	if (iX >= iLeft && iX <= iRight && iY >= iBottom && iY <= iTop) return 1 ;
	return 0 ;
}

bool CheckCollision(int iBottom1, int iLeft1, int iTop1, int iRight1, int iX1, int iY1, 
					int iBottom2, int iLeft2, int iTop2, int iRight2, int iX2, int iY2)
{
	iLeft1 += iX1 ;
	iLeft2 += iX2 ;
	iRight1 += iX1 ;
	iRight2 += iX2 ;
	iBottom1 += iY1 ;
	iBottom2 += iY2 ;
	iTop1 += iY1 ;
	iTop2 += iY2 ;

	int iContained ;

	iContained = CheckContained(iLeft1, iBottom1, iBottom2, iLeft2, iTop2, iRight2) ;
	iContained += CheckContained(iLeft1, iTop1, iBottom2, iLeft2, iTop2, iRight2) ;
	if (iContained >= 2) return true ;
	iContained += CheckContained(iRight1, iTop1, iBottom2, iLeft2, iTop2, iRight2) ;
	if (iContained >= 2) return true ;
	iContained += CheckContained(iRight1, iBottom1, iBottom2, iLeft2, iTop2, iRight2) ;
	if (iContained >= 2) return true ;

	iContained += CheckContained(iLeft2, iBottom2, iBottom1, iLeft1, iTop1, iRight1) ;
	if (iContained >= 2) return true ;
	iContained += CheckContained(iLeft2, iTop2, iBottom1, iLeft1, iTop1, iRight1) ;
	if (iContained >= 2) return true ;
	iContained += CheckContained(iRight2, iTop2, iBottom1, iLeft1, iTop1, iRight1) ;
	if (iContained >= 2) return true ;
	iContained += CheckContained(iRight2, iBottom2, iBottom1, iLeft1, iTop1, iRight1) ;
	if (iContained >= 2) return true ;

	return false ;
}

void SkipComments(FILE *&pFile) // skip over commenting if present
{/*
	char cCheck = ' ', cCheck2 ;
	long lCurrentPos ;
//	fpos_t position ;
	lCurrentPos = ftell(pFile) ;
	while (cCheck == ' ') 
	{
//		fgetpos(pFile, &position);
		fscanf(pFile, "%c", &cCheck) ;
	}
	if (cCheck == ';')
	{
		while (cCheck != '\n') cCheck = fscanf(pFile, "%c", &cCheck) ;
//		SkipComments(pFile) ;
	} else 
	{
//		fsetpos(pFile, &position) ;
		fseek(pFile, 0, SEEK_SET);
		for (long lRead = 0 ; lRead < lCurrentPos ; ++lRead) fscanf(pFile, "%c", &cCheck2) ;
		if (cCheck == cCheck2 || cCheck2 != ' ')
		{
			fseek(pFile, 0, SEEK_SET);
			for (long lRead = 0 ; lRead < lCurrentPos-1 ; ++lRead) fscanf(pFile, "%c", &cCheck2) ;
		}
//		fseek(pFile, lCurrentPos, SEEK_SET);
	}*/
}

void ReadTexture(char *szFilename, unsigned int &uiID) // read in and name a textures
{
	AUX_RGBImageRec *pImage = LoadBMP(szFilename) ;
	if (pImage == 0) return ;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &uiID);
    glBindTexture(GL_TEXTURE_2D, uiID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, pImage->sizeX, pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);

	DeleteImageRec(pImage) ;
}
