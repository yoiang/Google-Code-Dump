#include "ModelVertex.h"

ModelVertex::ModelVertex()
{
}

ModelVertex::ModelVertex(ModelVertex &Copy)
{
	m_ptLocation = Copy.m_ptLocation ;
	m_dTextureX = Copy.m_dTextureX ;
	m_dTextureY = Copy.m_dTextureY ;
	m_ptColor = Copy.m_ptColor ;
	m_dAlpha = Copy.m_dAlpha ;
	m_ptNormal = Copy.m_ptNormal ;
}

ModelVertex::~ModelVertex()
{
}

void ModelVertex::SetLocation(const Point &ptSetLocation)
{
	m_ptLocation = ptSetLocation ;
}

void ModelVertex::GetLocation(Point &ptGetLocation)
{
	ptGetLocation = m_ptLocation ;
}

void ModelVertex::SetTextureCoord(const PointType &dSetTextureX, const PointType &dSetTextureY)
{
	m_dTextureX = dSetTextureX ;
	m_dTextureY = dSetTextureY ;
}

void ModelVertex::GetTextureCoord(PointType &dGetTextureX, PointType &dGetTextureY)
{
	dGetTextureX = m_dTextureX ;
	dGetTextureY = m_dTextureY ;
}

void ModelVertex::SetColor(const Point &ptSetColor)
{
	m_ptColor = ptSetColor ;
}

void ModelVertex::GetColor(Point &ptGetColor)
{
	ptGetColor = m_ptColor ;
}

void ModelVertex::SetAlpha(const PointType &dSetAlpha)
{
	m_dAlpha = dSetAlpha ;
}

void ModelVertex::GetAlpha(PointType &dGetAlpha)
{
	dGetAlpha = m_dAlpha ;
}

void ModelVertex::SetNormal(const Point &ptSetNormal) 
{
	m_ptNormal = ptSetNormal ;
}

void ModelVertex::GetNormal(Point &ptGetNormal)
{
	ptGetNormal = m_ptNormal ;
}

const ModelVertex ModelVertex::operator =(const ModelVertex &Assign)
{
	ModelVertex TempVertex ;
	if (&Assign == this)
	{
		TempVertex.m_ptLocation = m_ptLocation ;
		TempVertex.m_dTextureX = m_dTextureX ;
		TempVertex.m_dTextureY = m_dTextureY ;
		TempVertex.m_ptColor = m_ptColor ;
		TempVertex.m_dAlpha = m_dAlpha ;
		TempVertex.m_ptNormal = m_ptNormal ;
	} else
	{
		TempVertex.m_ptLocation = m_ptLocation = Assign.m_ptLocation ;
		TempVertex.m_dTextureX = m_dTextureX = Assign.m_dTextureX ;
		TempVertex.m_dTextureY = m_dTextureY = Assign.m_dTextureY ;
		TempVertex.m_ptColor = m_ptColor = Assign.m_ptColor ;
		TempVertex.m_dAlpha = m_dAlpha = Assign.m_dAlpha ;
		TempVertex.m_ptNormal = m_ptNormal = Assign.m_ptNormal ;
	}
	return TempVertex ;
}
