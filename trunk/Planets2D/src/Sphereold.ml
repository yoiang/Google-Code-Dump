
void Init_Poly ()
{
	int trav, trav2 ;
	CPolygon Polygon ;
 Polygon.Number_of_Vertices = 6 ;
 Polygon.Vertices = new GrVertex[Polygon.Number_of_Vertices] ;
 Polygon.Vertices[0].x = 0.0f;
	Polygon.Vertices[0].y = 0.0f;
	Polygon.Vertices[0].z = -1.0f;
	Polygon.Vertices[1].x = 0.0f;
	Polygon.Vertices[1].y = 0.0f;
	Polygon.Vertices[1].z = 1.0f;
	Polygon.Vertices[2].x = 0.0f;
	Polygon.Vertices[2].y = -1.0f;
	Polygon.Vertices[2].z = 0.0f;
	Polygon.Vertices[3].x = 0.0f;
	Polygon.Vertices[3].y = 1.0f;
	Polygon.Vertices[3].z = 0.0f;
	Polygon.Vertices[4].x = -1.0f;
	Polygon.Vertices[4].y = 0.0f;
	Polygon.Vertices[4].z = 0.0f;
	Polygon.Vertices[5].x = 1.0f;
	Polygon.Vertices[5].y = 0.0f;
	Polygon.Vertices[5].z = 0.0f;

 Polygon.Number_of_Triangles = 8 ;
 Polygon.Triangles = new CTriVert_List [Polygon.Number_of_Triangles] ; 
	Polygon.Triangles[0].Vertices[0] = 0 ;
	Polygon.Triangles[0].Vertices[1] = 4 ;
	Polygon.Triangles[0].Vertices[2] = 2 ;

	Polygon.Triangles[1].Vertices[0] = 0 ;
	Polygon.Triangles[1].Vertices[1] = 5 ;
	Polygon.Triangles[1].Vertices[2] = 2 ;

	Polygon.Triangles[2].Vertices[0] = 1 ;
	Polygon.Triangles[2].Vertices[1] = 4 ;
	Polygon.Triangles[2].Vertices[2] = 2 ;

	Polygon.Triangles[3].Vertices[0] = 1 ;
	Polygon.Triangles[3].Vertices[1] = 5 ;
	Polygon.Triangles[3].Vertices[2] = 2 ;

	Polygon.Triangles[4].Vertices[0] = 0 ;
	Polygon.Triangles[4].Vertices[1] = 4 ;
	Polygon.Triangles[4].Vertices[2] = 3 ;

	Polygon.Triangles[5].Vertices[0] = 0 ;
	Polygon.Triangles[5].Vertices[1] = 5 ;
	Polygon.Triangles[5].Vertices[2] = 3 ;

	Polygon.Triangles[6].Vertices[0] = 1 ;
	Polygon.Triangles[6].Vertices[1] = 4 ;
	Polygon.Triangles[6].Vertices[2] = 3 ;

	Polygon.Triangles[7].Vertices[0] = 1 ;
	Polygon.Triangles[7].Vertices[1] = 5 ;
	Polygon.Triangles[7].Vertices[2] = 3 ;

/*
	CPolygon Polygon ;
 Polygon.Number_of_Vertices = 14 ;
 Polygon.Vertices = new GrVertex[Polygon.Number_of_Vertices] ;
	Polygon.Vertices[0].x = -0.57735f;
	Polygon.Vertices[0].y = -0.57735f;
	Polygon.Vertices[0].z = -0.57735f;
	Polygon.Vertices[1].x = -0.57735f;
	Polygon.Vertices[1].y = 0.57735f;
	Polygon.Vertices[1].z = -0.57735f;
	Polygon.Vertices[2].x = 0.57735f;
	Polygon.Vertices[2].y = 0.57735f;
	Polygon.Vertices[2].z = -0.57735f;
	Polygon.Vertices[3].x = 0.57735f;
	Polygon.Vertices[3].y = -0.57735f;
	Polygon.Vertices[3].z = -0.57735f;
	Polygon.Vertices[4].x = 0.57735f;
	Polygon.Vertices[4].y = -0.57735f;
	Polygon.Vertices[4].z = 0.57735f;
	Polygon.Vertices[5].x = 0.57735f;
	Polygon.Vertices[5].y = 0.57735f;
	Polygon.Vertices[5].z = 0.57735f;
	Polygon.Vertices[6].x = -0.57735f;
	Polygon.Vertices[6].y = 0.57735f;
	Polygon.Vertices[6].z = 0.57735f;
	Polygon.Vertices[7].x = -0.57735f;
	Polygon.Vertices[7].y = -0.57735f;
	Polygon.Vertices[7].z = 0.57735f;

 Polygon.Vertices[8].x = 0.0f;
	Polygon.Vertices[8].y = 0.0f;
	Polygon.Vertices[8].z = -1.0f;
	Polygon.Vertices[9].x = 0.0f;
	Polygon.Vertices[9].y = 0.0f;
	Polygon.Vertices[9].z = 1.0f;
	Polygon.Vertices[10].x = 0.0f;
	Polygon.Vertices[10].y = -1.0f;
	Polygon.Vertices[10].z = 0.0f;
	Polygon.Vertices[11].x = 0.0f;
	Polygon.Vertices[11].y = 1.0f;
	Polygon.Vertices[11].z = 0.0f;
	Polygon.Vertices[12].x = -1.0f;
	Polygon.Vertices[12].y = 0.0f;
	Polygon.Vertices[12].z = 0.0f;
	Polygon.Vertices[13].x = 1.0f;
	Polygon.Vertices[13].y = 0.0f;
	Polygon.Vertices[13].z = 0.0f;

 Polygon.Number_of_Triangles = 24 ;
 Polygon.Triangles = new CTriVert_List [Polygon.Number_of_Triangles] ; 

 Polygon.Triangles[0].Vertices[0] = 0 ; 
 Polygon.Triangles[0].Vertices[1] = 1 ; 
 Polygon.Triangles[0].Vertices[2] = 8 ; 

 Polygon.Triangles[1].Vertices[0] = 1 ;
 Polygon.Triangles[1].Vertices[1] = 2 ;
 Polygon.Triangles[1].Vertices[2] = 8 ;
 
 Polygon.Triangles[2].Vertices[0] = 2 ;
 Polygon.Triangles[2].Vertices[1] = 3 ;
 Polygon.Triangles[2].Vertices[2] = 8 ;
 
 Polygon.Triangles[3].Vertices[0] = 3 ;
 Polygon.Triangles[3].Vertices[1] = 0 ;
 Polygon.Triangles[3].Vertices[2] = 8 ;

 Polygon.Triangles[4].Vertices[0] = 0 ;
	Polygon.Triangles[4].Vertices[1] = 7 ;
	Polygon.Triangles[4].Vertices[2] = 12 ; 

	Polygon.Triangles[5].Vertices[0] = 7 ;
	Polygon.Triangles[5].Vertices[1] = 6 ;
	Polygon.Triangles[5].Vertices[2] = 12 ;
 
	Polygon.Triangles[6].Vertices[0] = 6 ;
	Polygon.Triangles[6].Vertices[1] = 1 ;
	Polygon.Triangles[6].Vertices[2] = 12 ; 

	Polygon.Triangles[7].Vertices[0] = 1 ;
	Polygon.Triangles[7].Vertices[1] = 0 ;
	Polygon.Triangles[7].Vertices[2] = 12 ;

	Polygon.Triangles[8].Vertices[0] = 7 ;
	Polygon.Triangles[8].Vertices[1] = 4 ;
	Polygon.Triangles[8].Vertices[2] = 9 ;

 Polygon.Triangles[9].Vertices[0] = 4 ;
	Polygon.Triangles[9].Vertices[1] = 5 ;
	Polygon.Triangles[9].Vertices[2] = 9 ;

	Polygon.Triangles[10].Vertices[0] = 5 ;
	Polygon.Triangles[10].Vertices[1] = 6 ;
	Polygon.Triangles[10].Vertices[2] = 9 ;

 Polygon.Triangles[11].Vertices[0] = 6 ;
	Polygon.Triangles[11].Vertices[1] = 7 ;
	Polygon.Triangles[11].Vertices[2] = 9 ;

	Polygon.Triangles[12].Vertices[0] = 4 ;
	Polygon.Triangles[12].Vertices[1] = 5 ;
	Polygon.Triangles[12].Vertices[2] = 13 ;

	Polygon.Triangles[13].Vertices[0] = 5 ; 
	Polygon.Triangles[13].Vertices[1] = 2 ; 
	Polygon.Triangles[13].Vertices[2] = 13 ; 

	Polygon.Triangles[14].Vertices[0] = 2 ; 
	Polygon.Triangles[14].Vertices[1] = 3 ;
	Polygon.Triangles[14].Vertices[2] = 13 ; 

	Polygon.Triangles[15].Vertices[0] = 3 ;
	Polygon.Triangles[15].Vertices[1] = 4 ; 
	Polygon.Triangles[15].Vertices[2] = 13 ;

	Polygon.Triangles[16].Vertices[0] = 0 ;
	Polygon.Triangles[16].Vertices[1] = 3 ;
	Polygon.Triangles[16].Vertices[2] = 10 ;
 
	Polygon.Triangles[17].Vertices[0] = 3 ;
	Polygon.Triangles[17].Vertices[1] = 4 ;
	Polygon.Triangles[17].Vertices[2] = 10 ;

 Polygon.Triangles[18].Vertices[0] = 4 ;
	Polygon.Triangles[18].Vertices[1] = 7 ;
	Polygon.Triangles[18].Vertices[2] = 10 ;

 Polygon.Triangles[19].Vertices[0] = 7 ;
	Polygon.Triangles[19].Vertices[1] = 0 ;
	Polygon.Triangles[19].Vertices[2] = 10 ;

 Polygon.Triangles[20].Vertices[0] = 1 ;
	Polygon.Triangles[20].Vertices[1] = 2 ;
	Polygon.Triangles[20].Vertices[2] = 11 ;
 
	Polygon.Triangles[21].Vertices[0] = 2 ; 
	Polygon.Triangles[21].Vertices[1] = 5 ;
	Polygon.Triangles[21].Vertices[2] = 11 ;
 
	Polygon.Triangles[22].Vertices[0] = 5 ;
	Polygon.Triangles[22].Vertices[1] = 6 ;
	Polygon.Triangles[22].Vertices[2] = 11 ;

 Polygon.Triangles[23].Vertices[0] = 6 ;
	Polygon.Triangles[23].Vertices[1] = 1 ;
	Polygon.Triangles[23].Vertices[2] = 11 ;
*/
// delete [] Polygon.Vertices ;
// delete [] Polygon.Triangles ;
// Read_VertexList("vertex.dat", "facet.dat", Polygon) ;
/*
 Polygon.Normals = new point_class<double> [Polygon.Number_of_Vertices] ;
	point_class<double> temp_Normal, temp_Normal2 ;
	int deler;
	double x,y,z,length;	
	// Take a vertex
	for (trav = 0 ; trav < Polygon.Number_of_Vertices ; trav ++)
	{	
	 deler = 0; 
		// deler is used as to divide x, y and z by the number of faces which share the vertex
		// Go though all faces to see which faces have this vertex in common
		for (trav2 = 0 ; trav2 < Polygon.Number_of_Triangles; trav2 ++)
		{	
			// Now if if the face shares the vertex -- compute face normal and add its x component to x, its y to y and its z to z
			// also increase deler.
			if(Polygon.Triangles[trav2].Vertices[0] == trav || Polygon.Triangles[trav2].Vertices[1] == trav || Polygon.Triangles[trav2].Vertices[2] == trav)
			{
				deler++;
				temp_Normal.x = Polygon.Vertices[Polygon.Triangles[trav2].Vertices[2]].x - Polygon.Vertices[Polygon.Triangles[trav2].Vertices[0]].x;
				temp_Normal.y = Polygon.Vertices[Polygon.Triangles[trav2].Vertices[2]].y - Polygon.Vertices[Polygon.Triangles[trav2].Vertices[0]].y;
				temp_Normal.z = Polygon.Vertices[Polygon.Triangles[trav2].Vertices[2]].z - Polygon.Vertices[Polygon.Triangles[trav2].Vertices[0]].z;
				temp_Normal2.x = Polygon.Vertices[Polygon.Triangles[trav2].Vertices[1]].x - Polygon.Vertices[Polygon.Triangles[trav2].Vertices[0]].x;
				temp_Normal2.y = Polygon.Vertices[Polygon.Triangles[trav2].Vertices[1]].y - Polygon.Vertices[Polygon.Triangles[trav2].Vertices[0]].y;
				temp_Normal2.z = Polygon.Vertices[Polygon.Triangles[trav2].Vertices[1]].z - Polygon.Vertices[Polygon.Triangles[trav2].Vertices[0]].z;	
				
				x += ((temp_Normal2.y * temp_Normal.z) - (temp_Normal2.z * temp_Normal.y));	
				y += ((temp_Normal2.z * temp_Normal.x) - (temp_Normal2.x * temp_Normal.z));
				z += ((temp_Normal2.x * temp_Normal.y) - (temp_Normal2.y * temp_Normal.x));
			}	
		}
		if (deler != 0)
		{	
			Polygon.Normals[trav].x = x / deler; 
			Polygon.Normals[trav].y = y / deler; 
			Polygon.Normals[trav].z = z / deler; 
		} else
		{
			Polygon.Normals[trav].x = 0 ; 
			Polygon.Normals[trav].y = 0 ; 
			Polygon.Normals[trav].z = 0 ;
		}
		// Normalize the length to 1 to save dividing time in our (realtime) routine as dividing by 1 is not needed !
		length = sqrt((Polygon.Normals[trav].x*Polygon.Normals[trav].x) + (Polygon.Normals[trav].y*Polygon.Normals[trav].y) + (Polygon.Normals[trav].z*Polygon.Normals[trav].z));
		if (length != 0)
		{
		 Polygon.Normals[trav].x /= length;
		 Polygon.Normals[trav].y /= length;
		 Polygon.Normals[trav].z /= length;
		} else
		{
		 Polygon.Normals[trav].x = 0 ;
		 Polygon.Normals[trav].y = 0 ;
		 Polygon.Normals[trav].z = 0 ;
		}
		x=0;y=0;z=0;
	}*/


	CPlanet *pPlanet = planets ;
	while (pPlanet != NULL)
	{
		pPlanet->Model = new CPolygon (Polygon) ;
		for (trav = 0 ; trav < pPlanet->Model->Number_of_Vertices ; trav ++)
		{
			pPlanet->Model->Vertices[trav].x *= pPlanet->radius.x ;
			pPlanet->Model->Vertices[trav].y *= pPlanet->radius.y ;
			pPlanet->Model->Vertices[trav].z *= pPlanet->radius.z ;
			pPlanet->Model->Vertices[trav].r = pPlanet->red ;
			pPlanet->Model->Vertices[trav].g = pPlanet->green ;
			pPlanet->Model->Vertices[trav].b = pPlanet->blue ;
		}
		pPlanet = pPlanet->next ;
	}
}
