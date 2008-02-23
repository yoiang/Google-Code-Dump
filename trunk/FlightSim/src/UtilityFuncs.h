// Mental Tortoise Games
// Utility Functions header file

#ifndef __UTILITYFUNCS_H__
#define __UTILITYFUNCS_H__

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <stdio.h>

AUX_RGBImageRec *CreateImageRec(int iSetSizeX, int iSetSizeY, bool bAlpha) ; // create an image record
void DeleteImageRec(AUX_RGBImageRec *pDeleteImage) ;			// delete an image record

AUX_RGBImageRec *LoadBMP(char *szFilename) ;	// load a bitmap file, return an image record

// crop an image record into a smaller image record
void CropImage(AUX_RGBImageRec *pReadImage, // image record to crop
			   AUX_RGBImageRec *pDestination, // image to write to
			   int iX,			// x location to crop
			   int iY,			// y location to crop
			   int iWidth,		// cropping width
			   int iHeight) ;	// cropping height

// crop an image record into a smaller image record
void CropImageAlpha(AUX_RGBImageRec *pReadImage, // image record to crop
					AUX_RGBImageRec *pMaskImage, // alpha mask image record
					AUX_RGBImageRec *pDestination, // image to write to
					int iX,			// x location to crop
					int iY,			// y location to crop
					int iWidth,		// cropping width
					int iHeight) ;	// cropping height

int CheckContained(int iX, int iY, int iBottom, int iLeft, int iTop, int iRight) ; // check if point is inside of box

bool CheckCollision(int iBottom1, int iLeft1, int iTop1, int iRight1, int iX1, int iY1, 
					int iBottom2, int iLeft2, int iTop2, int iRight2, int iX2, int iY2) ; // check if two boxes collide


void SkipComments(FILE *&pFile) ; // skip over commenting if present

void ReadTexture(char *szFilename, unsigned int &uiID) ; // read in and name a textures

#endif