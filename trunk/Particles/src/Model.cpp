#include "Model.h"


Model::Model()	// model constructor
{
}

Model::~Model()	// model destructor
{
}

void Model::Display()	// display model
{
	std::list<ModelPolygon*>::iterator iterPolygons = m_pPolygons.begin() ;

	int iNumVertices, iTrav ;
	unsigned int uiTextureID ;
	float dAlpha, dTextureX, dTextureY ;
	Point ptBuffer ;
	ModelVertex VertexBuffer ;

	while (iterPolygons != m_pPolygons.end())
	{
		(*iterPolygons)->GetNumVertices(iNumVertices) ;
		if (iNumVertices >= 0)
		{
//			(*iterPolygons)->GetAlpha(dAlpha) ;
			//			if (pTravPolygons->pValue->dAlpha != 1.0) glEnable(GL_BLEND);
			//			glColor4f(pTravPolygons->pValue->ptColor.dVal[0],
			//						pTravPolygons->pValue->ptColor.dVal[1],
			//						pTravPolygons->pValue->ptColor.dVal[2],
			//						pTravPolygons->pValue->dAlpha) ;
			
			(*iterPolygons)->GetTextureID(uiTextureID) ;
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
					(*iterPolygons)->GetVertex(iTrav, VertexBuffer) ;
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
					(*iterPolygons)->GetVertex(iTrav, VertexBuffer) ;
					
					VertexBuffer.GetColor(ptBuffer) ;
					VertexBuffer.GetAlpha(dAlpha) ;
					glColor4f(ptBuffer.dVal[0], ptBuffer.dVal[1], ptBuffer.dVal[2], dAlpha) ;
					
					VertexBuffer.GetTextureCoord(dTextureX, dTextureY) ;
					glTexCoord2f(dTextureX, dTextureY) ;						
					VertexBuffer.GetLocation(ptBuffer) ;
					glVertex3fv(ptBuffer.dVal) ;
				}
				
			}
			
			glEnd() ;
			if (uiTextureID != 0) glDisable(GL_TEXTURE_2D) ;
			
//			if (pTravPolygons->pValue->dAlpha != 1.0 || bBlackOut) glDisable(GL_BLEND);
		}
		
		++iterPolygons ;
	}
}

void Model::AddPolygon(ModelPolygon *pAddPolygon)
{
	m_pPolygons.push_back(pAddPolygon) ;
}

void Model::ReadMLFile(char *szFilename)	// read in model
{
	int iNumVertices, iTextureID ;
	float dAlpha, dTextureX, dTextureY ;
	Point ptColor, ptBBNegative, ptBBPositive, ptNormal, ptLocation ;
	ModelVertex VertexBuffer ;

	char cReadChar ;
	char szTextureFilename[256] ;
	FILE *pFile = fopen(szFilename, "r") ;

	if (pFile == 0) 
	{
		return ;
	}

	ModelPolygon *pTemp ;
	int iCount, iReadBB, iReadNormal ;
	
	ptModelBBNegatives = 9E9f ;
	ptModelBBPositives = -9E9f ;
	while (!feof(pFile))	// for each polygon
	{
		// read in number of sides
		fscanf(pFile, "%i", &iNumVertices) ;
		if (feof(pFile)) break ;

		pTemp = new ModelPolygon(iNumVertices) ;
		if (pTemp == 0) exit(-1) ;
		// read in color, alpha, whether file contains bounding box and whether file contains normals
		fscanf(pFile, 
				"%f %f %f %f %i %i", 
				&(ptColor.dVal[0]), 
				&(ptColor.dVal[1]), 
				&(ptColor.dVal[2]), 
				&(dAlpha),
				&iReadBB,
				&iReadNormal) ;

		while ((cReadChar = fgetc(pFile)) != '\n') // read in texture file name if specified
		{
			if (cReadChar != ' ') 
			{
				szTextureFilename[0] = cReadChar ;
				fscanf(pFile, "%s", (szTextureFilename + 1)) ;
				unsigned int uiTemp ;
				ReadTexture(szTextureFilename, uiTemp) ;
				iTextureID = uiTemp ;
				break ;
			}
		}

		if (iReadBB)	// read in bounding box
		{
			fscanf(pFile, 
					"%f %f %f %f %f %f", 
					&(ptBBNegative.dVal[0]), 
					&(ptBBNegative.dVal[1]), 
					&(ptBBNegative.dVal[2]), 
					&(ptBBPositive.dVal[0]),
					&(ptBBPositive.dVal[1]),
					&(ptBBPositive.dVal[2])) ;

			if (ptBBNegative.dVal[0] < ptModelBBNegatives.dVal[0]) ptModelBBNegatives.dVal[0] = ptBBNegative.dVal[0] ;
			if (ptBBNegative.dVal[1] < ptModelBBNegatives.dVal[1]) ptModelBBNegatives.dVal[1] = ptBBNegative.dVal[1] ;
			if (ptBBNegative.dVal[2] < ptModelBBNegatives.dVal[2]) ptModelBBNegatives.dVal[2] = ptBBNegative.dVal[2] ;

			if (ptBBPositive.dVal[0] > ptModelBBPositives.dVal[0]) ptModelBBPositives.dVal[0] = ptBBPositive.dVal[0] ;
			if (ptBBPositive.dVal[1] > ptModelBBPositives.dVal[1]) ptModelBBPositives.dVal[1] = ptBBPositive.dVal[1] ;
			if (ptBBPositive.dVal[2] > ptModelBBPositives.dVal[2]) ptModelBBPositives.dVal[2] = ptBBPositive.dVal[2] ;
		}

		if (iReadNormal)	// read in normal
			fscanf(pFile, 
					"%f %f %f", 
					&(ptNormal.dVal[0]), 
					&(ptNormal.dVal[1]), 
					&(ptNormal.dVal[2])) ; 

		for (iCount = 0 ; iCount < iNumVertices ; iCount ++)	// read in vertices
		{
			fscanf(pFile, 
					"%f %f %f", 
					&(ptLocation.dVal[0]), 
					&(ptLocation.dVal[1]), 
					&(ptLocation.dVal[2])) ;
			if (!iReadBB)	// calculate bounding box
			{
				if (iCount == 0)
				{
					ptBBNegative = ptLocation ;
					ptBBPositive = ptLocation ;
				} else
				{
					if (ptLocation.dVal[0] < ptBBNegative.dVal[0]) ptBBNegative.dVal[0] = ptLocation.dVal[0] ;
					if (ptLocation.dVal[1] < ptBBNegative.dVal[1]) ptBBNegative.dVal[1] = ptLocation.dVal[1] ;
					if (ptLocation.dVal[2] < ptBBNegative.dVal[2]) ptBBNegative.dVal[2] = ptLocation.dVal[2] ;

					if (ptLocation.dVal[0] > ptBBPositive.dVal[0]) ptBBPositive.dVal[0] = ptLocation.dVal[0] ;
					if (ptLocation.dVal[1] > ptBBPositive.dVal[1]) ptBBPositive.dVal[1] = ptLocation.dVal[1] ;
					if (ptLocation.dVal[2] > ptBBPositive.dVal[2]) ptBBPositive.dVal[2] = ptLocation.dVal[2] ;
				}

				if (ptLocation.dVal[0] < ptModelBBNegatives.dVal[0]) ptModelBBNegatives.dVal[0] = ptLocation.dVal[0] ;
				if (ptLocation.dVal[1] < ptModelBBNegatives.dVal[1]) ptModelBBNegatives.dVal[1] = ptLocation.dVal[1] ;
				if (ptLocation.dVal[2] < ptModelBBNegatives.dVal[2]) ptModelBBNegatives.dVal[2] = ptLocation.dVal[2] ;

				if (ptLocation.dVal[0] > ptModelBBPositives.dVal[0]) ptModelBBPositives.dVal[0] = ptLocation.dVal[0] ;
				if (ptLocation.dVal[1] > ptModelBBPositives.dVal[1]) ptModelBBPositives.dVal[1] = ptLocation.dVal[1] ;
				if (ptLocation.dVal[2] > ptModelBBPositives.dVal[2]) ptModelBBPositives.dVal[2] = ptLocation.dVal[2] ;
			}

			VertexBuffer.SetAlpha(dAlpha) ;
			VertexBuffer.SetColor(ptColor) ;
			VertexBuffer.SetLocation(ptLocation) ;
			VertexBuffer.SetNormal(ptNormal) ;
			pTemp->SetVertex(iCount, VertexBuffer) ;
		}
/*		if (iNumVertices > 2 && !iReadNormal) // calculate normal
		{
			CrossProduct(pTemp->pPoints[0] - pTemp->pPoints[1], pTemp->pPoints[2] - pTemp->pPoints[1], pTemp->ptNormal) ;
			Normalize(ptNormal) ;
		}
*/
		pTemp->SetBBNegative(ptBBNegative) ;
		pTemp->SetBBPositive(ptBBPositive) ;
		pTemp->SetTextureID(iTextureID) ;
		m_pPolygons.push_back(pTemp) ;
	}
	fclose(pFile) ;
}

void Model::ReadML2File(char *szFilename) // read in ML2 file
{
}