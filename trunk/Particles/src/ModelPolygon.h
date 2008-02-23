#ifndef __MODELPOLYGON_H__
#define __MODELPOLYGON_H__

#include "ModelVertex.h"

class ModelPolygon	// polygon class
{
private:
	int m_iNumVertices ; // number of vertices
	ModelVertex *m_pVertices ; // array of vertices

	unsigned int m_uiTextureID ; // texture name

	Point m_ptAverageNormal ; // polygon normal
	Point m_ptBBNegative, m_ptBBPositive ; // bounding box

public:
	ModelPolygon() ; // contructor
	ModelPolygon(int iSetNumSides) ; // costructor
	~ModelPolygon() ; // destructor

	void SetNumVertices(const int &iSetNumVertices) ;
	void GetNumVertices(int &iGetNumVertices) ;

	bool SetVertex(const int &iVertexIndex, const ModelVertex &SetVertex) ;
	bool GetVertex(const int &iVertexIndex, ModelVertex &GetVertex) ;
	
	void SetTextureID(const unsigned int &uiSetTextureID) ;
	void GetTextureID(unsigned int &uiGetTextureID) ;
	
	void SetAverageNormal(const Point &ptSetAverageNormal) ;
	void GetAverageNormal(Point &ptGetAverageNormal) ;
	void SetBBNegative(const Point &ptSetBBNegative) ;
	void GetBBNegative(Point &ptGetBBNegative) ;
	void SetBBPositive(const Point &ptSetBBPositive) ;
	void GetBBPositive(Point &ptGetBBPositive) ;
} ;

#endif