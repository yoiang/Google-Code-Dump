#include "Terrain.h"

Terrain::Terrain()
{
	fLength = 1 ;
	fWidth = 1 ;
	fHeight = 1 ;
}

Terrain::~Terrain()
{
	TerrainModel.Polygons.Clear(true) ;
}

void Terrain::AddPolygon(ModelPolygon *pAdd)
{
	int iLevel = 0 ;
	int iCount[3] ;
	iCount[0] = 0 ;
	iCount[1] = 0 ;
	iCount[2] = 0 ;
	for (int iTrav = 0 ; iTrav < pAdd->iNumSides ; iTrav ++)
	{
		if (pAdd->pPoints[iTrav].dVal[1] > fHeight / 3 * 2) iCount[2] ++ ;
		else if (pAdd->pPoints[iTrav].dVal[1] > fHeight / 3) iCount[1] ++ ;
		else iCount[0] ++ ;
	}
	if (iCount[2] >= 2)
	{
		pAdd->ptColor = Point(1, 1, 1) ;
	} else if (iCount[1] >= 1)
	{
		pAdd->ptColor = Point(0.3, 0.3, 0.3) ;
	} else
	{
		pAdd->ptColor = ptColor ;
	}
	pAdd->dAlpha = dAlpha ;
	TerrainModel.Polygons.AddBack(pAdd) ;
}

int Terrain::Midpoint(ModelPolygon *pSplit, int iDepth)
{
	if (iDepth == 0)
	{
		AddPolygon(pSplit) ;
		return 0 ;
	}
	if ((pSplit->pPoints[0].dVal[0] == pSplit->pPoints[1].dVal[0] && pSplit->pPoints[0].dVal[2] == pSplit->pPoints[1].dVal[2]) ||
		(pSplit->pPoints[0].dVal[0] == pSplit->pPoints[2].dVal[0] && pSplit->pPoints[0].dVal[2] == pSplit->pPoints[2].dVal[2]) ||
		(pSplit->pPoints[1].dVal[0] == pSplit->pPoints[2].dVal[0] && pSplit->pPoints[1].dVal[2] == pSplit->pPoints[2].dVal[2]))
		return 1 ;

	Point ptNew1, ptNew2, ptNew3 ;
	ptNew1.dVal[0] = (pSplit->pPoints[0].dVal[0] + pSplit->pPoints[1].dVal[0]) / 2.0 ;
	ptNew1.dVal[1] = (pSplit->pPoints[0].dVal[1] + pSplit->pPoints[1].dVal[1]) / 2.0 + rand() * 0.0001 ;
	ptNew1.dVal[2] = (pSplit->pPoints[0].dVal[2] + pSplit->pPoints[1].dVal[2]) / 2.0 ;
	ptNew2.dVal[0] = (pSplit->pPoints[1].dVal[0] + pSplit->pPoints[2].dVal[0]) / 2.0 ;
	ptNew2.dVal[1] = (pSplit->pPoints[1].dVal[1] + pSplit->pPoints[2].dVal[1]) / 2.0 + rand() * 0.0001 ;
	ptNew2.dVal[2] = (pSplit->pPoints[1].dVal[2] + pSplit->pPoints[2].dVal[2]) / 2.0 ;
	ptNew3.dVal[0] = (pSplit->pPoints[2].dVal[0] + pSplit->pPoints[0].dVal[0]) / 2.0 ;
	ptNew3.dVal[1] = (pSplit->pPoints[2].dVal[1] + pSplit->pPoints[0].dVal[1]) / 2.0 + rand() * 0.0001 ;
	ptNew3.dVal[2] = (pSplit->pPoints[2].dVal[2] + pSplit->pPoints[0].dVal[2]) / 2.0 ;

	ModelPolygon *pTriangle = new ModelPolygon(3) ;
	if (pTriangle == 0) exit(-1) ;
	pTriangle->pPoints[0] = pSplit->pPoints[0] ;
	pTriangle->pPoints[1] = pSplit->pPoints[1] ;
	pTriangle->pPoints[2] = ptNew1 ;
	AddPolygon(pTriangle) ;

	pTriangle = new ModelPolygon(3) ;
	if (pTriangle == 0) exit(-1) ;
	pTriangle->pPoints[0] = pSplit->pPoints[1] ;
	pTriangle->pPoints[1] = pSplit->pPoints[2] ;
	pTriangle->pPoints[2] = ptNew2 ;
	AddPolygon(pTriangle) ;
	
	pTriangle = new ModelPolygon(3) ;
	if (pTriangle == 0) exit(-1) ;
	pTriangle->pPoints[0] = pSplit->pPoints[2] ;
	pTriangle->pPoints[1] = pSplit->pPoints[0] ;
	pTriangle->pPoints[2] = ptNew3 ;
	AddPolygon(pTriangle) ;

	pTriangle = new ModelPolygon(3) ;
	if (pTriangle == 0) exit(-1) ;
	pTriangle->pPoints[0] = ptNew1 ;
	pTriangle->pPoints[1] = ptNew2 ;
	pTriangle->pPoints[2] = ptNew3 ;
	if (Midpoint(pTriangle, iDepth - 1))
	{
		AddPolygon(pSplit) ;
		delete pTriangle ;
		return 0 ;
	}
//	TerrainModel.Polygons.AddBack(pTriangle) ;

	pTriangle = new ModelPolygon(3) ;
	if (pTriangle == 0) exit(-1) ;
	pTriangle->pPoints[0] = pSplit->pPoints[0] ;
	pTriangle->pPoints[1] = ptNew1 ;
	pTriangle->pPoints[2] = ptNew3 ;
	if (Midpoint(pTriangle, iDepth - 1))
	{
		AddPolygon(pSplit) ;
		delete pTriangle ;
		return 0 ;
	}
//	TerrainModel.Polygons.AddBack(pTriangle) ;

	pTriangle = new ModelPolygon(3) ;
	if (pTriangle == 0) exit(-1) ;
	pTriangle->pPoints[0] = ptNew1 ;
	pTriangle->pPoints[1] = pSplit->pPoints[1] ;
	pTriangle->pPoints[2] = ptNew2 ;
	if (Midpoint(pTriangle, iDepth - 1))
	{
		AddPolygon(pSplit) ;
		delete pTriangle ;
		return 0 ;
	}
//	TerrainModel.Polygons.AddBack(pTriangle) ;

	pTriangle = new ModelPolygon(3) ;
	if (pTriangle == 0) exit(-1) ;
	pTriangle->pPoints[0] = ptNew3 ;
	pTriangle->pPoints[1] = ptNew2 ;
	pTriangle->pPoints[2] = pSplit->pPoints[2] ;
	if (Midpoint(pTriangle, iDepth - 1))
	{
		AddPolygon(pSplit) ;
		delete pTriangle ;
		return 0 ;
	}

//	TerrainModel.Polygons.AddBack(pSplit) ;

	return 0 ;
}

void Terrain::GenMidpoint()
{
#ifdef WIN32
	SYSTEMTIME SystemTime ;
	GetSystemTime(&SystemTime) ;
	srand(SystemTime.wMilliseconds) ;
#else
	srand(time(NULL)) ;
#endif
	TerrainModel.Polygons.Clear(true) ;

	ModelPolygon *pMainTriangles = new ModelPolygon(3) ;
	if (pMainTriangles == 0) exit(-1);
	pMainTriangles->ptColor = ptColor ;
	pMainTriangles->dAlpha = dAlpha ;
	pMainTriangles->pPoints[0] = Point(0, 0, 0) ;
	pMainTriangles->pPoints[1] = Point(fWidth / 2, fHeight, fLength / 2) ;
	pMainTriangles->pPoints[2] = Point(fWidth, 0, 0) ;
	Midpoint(pMainTriangles, iMaxDepth) ;
//	TerrainModel.Polygons.AddBack(pMainTriangles) ;

	pMainTriangles = new ModelPolygon(3) ;
	if (pMainTriangles == 0) exit(-1);
	pMainTriangles->ptColor = ptColor ;
	pMainTriangles->dAlpha = dAlpha ;
	pMainTriangles->pPoints[0] = Point(0, 0, fLength) ;
	pMainTriangles->pPoints[1] = Point(fWidth / 2, fHeight, fLength / 2) ;
	pMainTriangles->pPoints[2] = Point(0, 0, 0) ;
	Midpoint(pMainTriangles, iMaxDepth) ;
//	TerrainModel.Polygons.AddBack(pMainTriangles) ;

	pMainTriangles = new ModelPolygon(3) ;
	if (pMainTriangles == 0) exit(-1);
	pMainTriangles->ptColor = ptColor ;
	pMainTriangles->dAlpha = dAlpha ;
	pMainTriangles->pPoints[0] = Point(fWidth, 0, fLength) ;
	pMainTriangles->pPoints[1] = Point(fWidth / 2, fHeight, fLength / 2) ;
	pMainTriangles->pPoints[2] = Point(0, 0, fLength) ;
	Midpoint(pMainTriangles, iMaxDepth) ;
//	TerrainModel.Polygons.AddBack(pMainTriangles) ;

	pMainTriangles = new ModelPolygon(3) ;
	if (pMainTriangles == 0) exit(-1);
	pMainTriangles->ptColor = ptColor ;
	pMainTriangles->dAlpha = dAlpha ;
	pMainTriangles->pPoints[0] = Point(fWidth, 0, 0) ;
	pMainTriangles->pPoints[1] = Point(fWidth / 2, fHeight, fLength / 2) ;
	pMainTriangles->pPoints[2] = Point(fWidth, 0, fLength) ;
	Midpoint(pMainTriangles, iMaxDepth) ;
//	TerrainModel.Polygons.AddBack(pMainTriangles) ;
}

void Terrain::Display()
{
	TerrainModel.Display(false) ;
}
