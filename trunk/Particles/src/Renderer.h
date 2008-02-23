#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "ModelPolygon.h"
#include <windows.h>
#include <gl/gl.h>
#include <list>

class PolygonInfo
{
public:
	ModelPolygon *m_pPolygon ;
	Point m_ptOffset ;
	bool m_bLighting, m_bBlending, m_bFilling ;

	PolygonInfo() ;
} ;

class Renderer
{
private:
	std::list<PolygonInfo*> m_llPolygons ;
	std::list<PolygonInfo*> m_llGarbage ;
	bool m_bLighting, m_bBlending, m_bFilling ;

	void DisplayPolygon(ModelPolygon *pPolygon) ;
public:
	Renderer() ;
	~Renderer() ;

	void AddPolygon(ModelPolygon *pPolygon, const bool &bLighting = false, const bool &bBlending = false, const bool &bFilling = true) ;
	void AddPolygon(ModelPolygon *pPolygon, const Point &ptLocation, const bool &bLighting = false, const bool &bBlending = false, const bool &bFilling = true, const Point &ptViewpoint = Point(0.0f, 0.0f, 0.0f)) ;

	void Display() ;
	void ClearList() ;
} ;

#endif