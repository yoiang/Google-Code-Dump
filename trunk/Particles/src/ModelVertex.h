#ifndef __MODELVERTEX_H__
#define __MODELVERTEX_H__

#include "Point.h"

class ModelVertex
{
private:
	Point m_ptLocation ; // location of vertex

	PointType m_dTextureX, m_dTextureY ; // texture coordinates of vertex

	Point m_ptColor ; // color of vertex
	PointType m_dAlpha ; // alpha of vertex

	Point m_ptNormal ; // normal of vertex 

public:
	ModelVertex() ;
	ModelVertex(ModelVertex &Copy) ;
	~ModelVertex() ;

	void SetLocation(const Point &ptSetLocation) ;
	void GetLocation(Point &ptGetLocation) ;

	void SetTextureCoord(const PointType &dSetTextureX, const PointType &dSetTextureY) ;
	void GetTextureCoord(PointType &dGetTextureX, PointType &dGetTextureY) ;

	void SetColor(const Point &ptSetColor) ;
	void GetColor(Point &ptGetColor) ;
	void SetAlpha(const PointType &dSetAlpha) ;
	void GetAlpha(PointType &dGetAlpha) ;

	void SetNormal(const Point &ptSetNormal) ;
	void GetNormal(Point &ptGetNormal) ;

	const ModelVertex operator =(const ModelVertex &Assign) ;
} ;

#endif