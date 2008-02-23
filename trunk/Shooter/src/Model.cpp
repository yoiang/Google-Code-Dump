#include "Model.h"

ModelPolygon::ModelPolygon()
{
	iNumSides = 0 ;
	pPoints = 0 ;
}

ModelPolygon::ModelPolygon(int iSetNumSides)
{
	pPoints = 0 ;
	SetSides(iSetNumSides) ;
}

ModelPolygon::~ModelPolygon()
{
	if (pPoints != 0) delete [] pPoints ;
}

void ModelPolygon::SetSides(int iSetNumSides)
{
	if (pPoints != 0) delete [] pPoints ;
	iNumSides = iSetNumSides ;
	pPoints = new Point[iNumSides] ;
}

Model::Model()
{
	pPolysHead = 0 ;
	pPolysTail = 0 ;

	ptBBUpperFrontLeft = 0.0 ; 
	ptBBLowerBackRight = 0.0 ;
}

Model::~Model()
{
	ClearPolygons() ;
}

void Model::AddPolygon(ModelPolygon *pAdd)
{
	if (pPolysHead == 0)
	{
		pPolysHead = pAdd ;
		pPolysTail = pPolysHead ;
		pPolysHead->pLast = 0 ;
		pPolysHead->pNext = 0 ;
	} else
	{
		pPolysTail->pNext = pAdd ;
		pAdd->pLast = pPolysTail ;
		pAdd->pNext = 0 ;
		pPolysTail = pAdd ;
	}
}

void Model::ClearPolygons()
{
	if (pPolysHead == 0) return ;

	ModelPolygon *pTemp ;
	while (pPolysHead != 0)
	{
		pTemp = pPolysHead ;
		pPolysHead = pPolysHead->pNext ;
		delete pTemp ;
	}
	pPolysTail = 0 ;
}

void Model::Display()
{
	ModelPolygon *pTemp = pPolysHead ;
	int iTrav ;
	while (pTemp != 0)
	{
		glColor4f(pTemp->ptColor.dX, pTemp->ptColor.dY, pTemp->ptColor.dZ, pTemp->dAlpha) ;

		if (pTemp->iNumSides == 1)
		{
			glBegin(GL_POINT) ;
			glVertex3f(pTemp->pPoints[0].dX, pTemp->pPoints[0].dY, pTemp->pPoints[0].dZ) ;
			glEnd() ;
		} else if (pTemp->iNumSides == 2)
		{
			glBegin(GL_LINE) ;
			glVertex3f(pTemp->pPoints[0].dX, pTemp->pPoints[0].dY, pTemp->pPoints[0].dZ) ;
			glVertex3f(pTemp->pPoints[1].dX, pTemp->pPoints[1].dY, pTemp->pPoints[1].dZ) ;
			glEnd() ;
		} else if (pTemp->iNumSides == 3)
		{
			glBegin(GL_TRIANGLES) ;
			glVertex3f(pTemp->pPoints[0].dX, pTemp->pPoints[0].dY, pTemp->pPoints[0].dZ) ;
			glVertex3f(pTemp->pPoints[1].dX, pTemp->pPoints[1].dY, pTemp->pPoints[1].dZ) ;
			glVertex3f(pTemp->pPoints[2].dX, pTemp->pPoints[2].dY, pTemp->pPoints[2].dZ) ;
			glEnd() ;
		} else if (pTemp->iNumSides > 3)
		{
			glBegin(GL_POLYGON) ;
			for (iTrav = 0 ; iTrav < pTemp->iNumSides ; iTrav ++)
				glVertex3f(pTemp->pPoints[iTrav].dX, pTemp->pPoints[iTrav].dY, pTemp->pPoints[iTrav].dZ) ;
			glEnd() ;
		}
		
		pTemp = pTemp->pNext ;
	}
}

void Model::ReadFile(char *szFilename) 
{
	FILE *pFile = fopen(szFilename, "r") ;

	if (pFile == 0) 
	{
		return ;
	}

	ModelPolygon *pTemp ;
	int iSetNumSides, iCount ;
	
	fscanf(pFile, 
			"%f %f %f", 
			&(ptBBUpperFrontLeft.dX), 
			&(ptBBUpperFrontLeft.dY), 
			&(ptBBUpperFrontLeft.dZ)) ;
	if (feof(pFile)) 
	{
		fclose(pFile) ;
		return ;
	}
	fscanf(pFile, 
			"%f %f %f", 
			&(ptBBLowerBackRight.dX), 
			&(ptBBLowerBackRight.dY), 
			&(ptBBLowerBackRight.dZ)) ;

	while (!feof(pFile))
	{
		fscanf(pFile, "%i", &iSetNumSides) ;
		if (feof(pFile)) break ;

		pTemp = new ModelPolygon(iSetNumSides) ;
		fscanf(pFile, 
				"%f %f %f %f", 
				&(pTemp->ptColor.dX), 
				&(pTemp->ptColor.dY), 
				&(pTemp->ptColor.dZ), 
				&(pTemp->dAlpha)) ;
		for (iCount = 0 ; iCount < iSetNumSides ; iCount ++)
		{
			fscanf(pFile, 
					"%f %f %f", 
					&(pTemp->pPoints[iCount].dX), 
					&(pTemp->pPoints[iCount].dY), 
					&(pTemp->pPoints[iCount].dZ)) ;
		}
		AddPolygon(pTemp) ;
	}
	fclose(pFile) ;
}