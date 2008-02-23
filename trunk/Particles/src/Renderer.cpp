#include "Renderer.h"

PolygonInfo::PolygonInfo(): m_pPolygon(0), m_ptOffset(0.0f, 0.0f, 0.0f), m_bLighting(false), m_bBlending(false), m_bFilling(true)
{
}

Renderer::Renderer() : m_bLighting(false), m_bBlending(false), m_bFilling(true)
{
}

Renderer::~Renderer()
{
}

void Renderer::DisplayPolygon(ModelPolygon *pPolygon)
{
	int iNumVertices, iTrav ;
	unsigned uiTextureID ;
	float dAlpha, dTextureX, dTextureY ;
	Point ptBuffer ;
	ModelVertex VertexBuffer ;

	pPolygon->GetNumVertices(iNumVertices) ;
	if (iNumVertices <= 0) return ;

	pPolygon->GetTextureID(uiTextureID) ;

	if (uiTextureID != 0)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, uiTextureID); 
	}
	
	switch(iNumVertices)
	{
	case 1:
		glBegin(GL_POINT) ;
		break ;
	case 2:
		glBegin(GL_LINE) ;
		break ;
	case 3:
		glBegin(GL_TRIANGLES) ;
		break ;
	default:
		glBegin(GL_POLYGON) ;
		break ;
	}
	
	if (uiTextureID == 0)
	{
		for (iTrav = 0 ; iTrav < iNumVertices ; ++iTrav)
		{
			pPolygon->GetVertex(iTrav, VertexBuffer) ;

			VertexBuffer.GetColor(ptBuffer) ;
			VertexBuffer.GetAlpha(dAlpha) ;
			glColor4f(ptBuffer.dVal[0], ptBuffer.dVal[1], ptBuffer.dVal[2], dAlpha) ;

			VertexBuffer.GetLocation(ptBuffer) ;
			glVertex3fv(ptBuffer.dVal) ;
		}
	} else
	{
		for (iTrav = 0 ; iTrav < iNumVertices ; ++iTrav)
		{
			pPolygon->GetVertex(iTrav, VertexBuffer) ;

			VertexBuffer.GetColor(ptBuffer) ;
			VertexBuffer.GetAlpha(dAlpha) ;
			glColor4f(ptBuffer.dVal[0], ptBuffer.dVal[1], ptBuffer.dVal[2], dAlpha) ;

			VertexBuffer.GetTextureCoord(dTextureX, dTextureY) ;
			glTexCoord2f(dTextureX, dTextureY) ;						
			VertexBuffer.GetLocation(ptBuffer) ;
			glVertex3fv(ptBuffer.dVal) ;
		}
	}

/*
	if (pPolygon->dAlpha != 1.0) glEnable(GL_BLEND);
	if (pPolygon->dAlpha != 1.0 || bBlackOut) glDisable(GL_BLEND);
*/	
	glEnd() ;

	if (uiTextureID != 0) glDisable(GL_TEXTURE_2D) ;	
}

void Renderer::AddPolygon(ModelPolygon *pPolygon, const bool &bLighting, const bool &bBlending, const bool &bFilling)
{
	//glGet(GL_MODELVIEW_MATRIX 

//	LinkedListNode<ModelPolygon> *pTravPolygons = Polygons.pHead ;
	DisplayPolygon(pPolygon) ;
}

void Renderer::AddPolygon(ModelPolygon *pPolygon, const Point &ptLocation, const bool &bLighting, const bool &bBlending, const bool &bFilling, const Point &ptViewpoint) 
{

}

void Renderer::Display()
{
}

void Renderer::ClearList() 
{
//	m_llPolygons.clear() ;
}
/*
class PolygonInfo
{
public:
	ModelPolygon *pPolygon ;
	bool m_bLighting, m_bBlending, m_bFilling ;
} ;
*/