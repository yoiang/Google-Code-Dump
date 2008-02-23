#include "Model.h"

ModelPolygon::ModelPolygon()	// polygon contructor
{
	iNumSides = 0 ;
	iTextureName = 0 ;
	pPoints = 0 ;
}

ModelPolygon::ModelPolygon(int iSetNumSides)	// polygon contructor
{
	pPoints = 0 ;
	iTextureName = 0 ;
	SetSides(iSetNumSides) ;
}

ModelPolygon::~ModelPolygon()	// model destructor
{
	if (pPoints != 0) delete [] pPoints ;
}

void ModelPolygon::SetSides(int iSetNumSides)	// set number of sides of polygon
{
	if (pPoints != 0) delete [] pPoints ;
	iNumSides = iSetNumSides ;
	pPoints = new Point[iNumSides] ;
	if (pPoints == 0) exit(-1) ;
}

Model::Model()	// model constructor
{
}

Model::~Model()	// model destructor
{
}

void Model::Display(bool bBlackOut)	// display model
{
	LinkedListNode<ModelPolygon> *pTravPolygons = Polygons.pHead ;
	int iTrav ;
	while (pTravPolygons != 0)
	{
		if (bBlackOut)	// black out for shadowing
		{
			if (pTravPolygons->pValue->dAlpha != 1.0) glEnable(GL_BLEND);
			glColor4f(0, 0, 0, 0.5) ;
		} else
		{
			if (pTravPolygons->pValue->dAlpha != 1.0) glEnable(GL_BLEND);
			glColor4f(pTravPolygons->pValue->ptColor.dVal[0],
						pTravPolygons->pValue->ptColor.dVal[1],
						pTravPolygons->pValue->ptColor.dVal[2],
						pTravPolygons->pValue->dAlpha) ;
		}

		if (pTravPolygons->pValue->iTextureName != 0)
		{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, pTravPolygons->pValue->iTextureName); 
		}

		if (pTravPolygons->pValue->iNumSides == 1) glBegin(GL_POINT) ;
		else if (pTravPolygons->pValue->iNumSides == 2) glBegin(GL_LINE) ;
		else if (pTravPolygons->pValue->iNumSides == 3) glBegin(GL_TRIANGLES) ;
		else if (pTravPolygons->pValue->iNumSides > 3) glBegin(GL_POLYGON) ;

		if (pTravPolygons->pValue->iTextureName == 0)
		{
			for (iTrav = 0 ; iTrav < pTravPolygons->pValue->iNumSides ; iTrav ++)
				glVertex3fv(pTravPolygons->pValue->pPoints[iTrav].dVal) ;
		} else
		{
			if (pTravPolygons->pValue->iNumSides == 3)
			{

				glTexCoord2f(0, 1) ;				
				glVertex3fv(pTravPolygons->pValue->pPoints[0].dVal) ;
				glTexCoord2f(1, 1) ;				
				glVertex3fv(pTravPolygons->pValue->pPoints[1].dVal) ;
				glTexCoord2f(1, 0) ;				
				glVertex3fv(pTravPolygons->pValue->pPoints[2].dVal) ;
			} else if (pTravPolygons->pValue->iNumSides == 4)
			{
				glTexCoord2f(0, 1) ;				
				glVertex3fv(pTravPolygons->pValue->pPoints[0].dVal) ;
				glTexCoord2f(1, 1) ;				
				glVertex3fv(pTravPolygons->pValue->pPoints[1].dVal) ;
				glTexCoord2f(1, 0) ;				
				glVertex3fv(pTravPolygons->pValue->pPoints[2].dVal) ;
				glTexCoord2f(0, 0) ;				
				glVertex3fv(pTravPolygons->pValue->pPoints[3].dVal) ;
			} else
			{
				for (iTrav = 0 ; iTrav < pTravPolygons->pValue->iNumSides ; iTrav ++)
					glVertex3fv(pTravPolygons->pValue->pPoints[iTrav].dVal) ;
			}

		}

		glEnd() ;
		glDisable(GL_TEXTURE_2D) ;

		if (pTravPolygons->pValue->dAlpha != 1.0 || bBlackOut) glDisable(GL_BLEND);
		
		pTravPolygons = pTravPolygons->pNext ;
	}
}

void Model::ReadFile(char *szFilename)	// read in model
{
	char cReadChar ;
	char szTextureFilename[256] ;
	FILE *pFile = fopen(szFilename, "r") ;

	if (pFile == 0) 
	{
		return ;
	}

	ModelPolygon *pTemp ;
	int iSetNumSides, iCount, iReadBB, iReadNormal ;
	
	while (!feof(pFile))	// for each polygon
	{
		// read in number of sides
		fscanf(pFile, "%i", &iSetNumSides) ;
		if (feof(pFile)) break ;

		pTemp = new ModelPolygon(iSetNumSides) ;
		if (pTemp == 0) exit(-1) ;
		// read in color, alpha, whether file contains bounding box and whether file contains normals
		fscanf(pFile, 
				"%f %f %f %f %i %i", 
				&(pTemp->ptColor.dVal[0]), 
				&(pTemp->ptColor.dVal[1]), 
				&(pTemp->ptColor.dVal[2]), 
				&(pTemp->dAlpha),
				&iReadBB,
				&iReadNormal) ;

		while ((cReadChar = fgetc(pFile)) != '\n') // read in texture file name if specified
		{
			if (cReadChar != ' ') 
			{
				szTextureFilename[0] = cReadChar ;
				fscanf(pFile, "%s", (szTextureFilename + 1)) ;
				ReadTexture(szTextureFilename, pTemp->iTextureName) ;
				break ;
			}
		}

		if (iReadBB)	// read in bounding box
			fscanf(pFile, 
					"%f %f %f %f %f %f", 
					&(pTemp->ptBBNegatives.dVal[0]), 
					&(pTemp->ptBBNegatives.dVal[1]), 
					&(pTemp->ptBBNegatives.dVal[2]), 
					&(pTemp->ptBBPositives.dVal[0]),
					&(pTemp->ptBBPositives.dVal[1]),
					&(pTemp->ptBBPositives.dVal[2])) ;
		if (iReadNormal)	// read in normal
			fscanf(pFile, 
					"%f %f %f", 
					&(pTemp->ptNormal.dVal[0]), 
					&(pTemp->ptNormal.dVal[1]), 
					&(pTemp->ptNormal.dVal[2])) ; 

		for (iCount = 0 ; iCount < iSetNumSides ; iCount ++)	// read in vertices
		{
			fscanf(pFile, 
					"%f %f %f", 
					&(pTemp->pPoints[iCount].dVal[0]), 
					&(pTemp->pPoints[iCount].dVal[1]), 
					&(pTemp->pPoints[iCount].dVal[2])) ;
			if (!iReadBB)	// calculate bounding box
			{
				if (iCount == 0)
				{
					pTemp->ptBBNegatives = pTemp->pPoints[iCount] ;
					pTemp->ptBBPositives = pTemp->pPoints[iCount] ;
				} else
				{
					if (pTemp->pPoints[iCount].dVal[0] < pTemp->ptBBNegatives.dVal[0]) pTemp->ptBBNegatives.dVal[0] = pTemp->pPoints[iCount].dVal[0] ;
					if (pTemp->pPoints[iCount].dVal[1] < pTemp->ptBBNegatives.dVal[1]) pTemp->ptBBNegatives.dVal[1] = pTemp->pPoints[iCount].dVal[1] ;
					if (pTemp->pPoints[iCount].dVal[2] < pTemp->ptBBNegatives.dVal[2]) pTemp->ptBBNegatives.dVal[2] = pTemp->pPoints[iCount].dVal[2] ;

					if (pTemp->pPoints[iCount].dVal[0] > pTemp->ptBBPositives.dVal[0]) pTemp->ptBBPositives.dVal[0] = pTemp->pPoints[iCount].dVal[0] ;
					if (pTemp->pPoints[iCount].dVal[1] > pTemp->ptBBPositives.dVal[1]) pTemp->ptBBPositives.dVal[1] = pTemp->pPoints[iCount].dVal[1] ;
					if (pTemp->pPoints[iCount].dVal[2] > pTemp->ptBBPositives.dVal[2]) pTemp->ptBBPositives.dVal[2] = pTemp->pPoints[iCount].dVal[2] ;
				}

			}
		}
		if (iSetNumSides > 2 && !iReadNormal) // calculate normal
		{
			CrossProduct(pTemp->pPoints[0] - pTemp->pPoints[1], pTemp->pPoints[2] - pTemp->pPoints[1], pTemp->ptNormal) ;
			Normalize(pTemp->ptNormal) ;
		}

		Polygons.AddBack(pTemp) ;
	}
	fclose(pFile) ;
}