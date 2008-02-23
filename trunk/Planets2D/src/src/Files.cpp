#include "Main.h"

int ReadField (FILE *&pFile, FieldTypes Type, void* pMemLocation)
{
 switch (Type)
 {
 case F_INT:
  fscanf (pFile, "\t\n%i", (int*)pMemLocation) ;
 return 1 ;
 case F_FLOAT:
  fscanf (pFile, "\t\n%f", (float*)pMemLocation) ;
 return 1 ;
 case F_STRING:
  char szString[2] ;
  fscanf (pFile, "%1[ ]%256[^\n\0]", szString, szGBuffer) ;
  *(char **)pMemLocation = new char [strlen(szGBuffer) + 1] ;
#ifdef MEM_DEBUG
  if (*(char **)pMemLocation == NULL) FatalError("ReadField - Heap overflow") ;
#endif // MEM_DEBUG
  sprintf(*(char **)pMemLocation, "%s", szGBuffer) ;
 return 1 ;
 case F_POINTTYPE:
  fscanf (pFile, "\t\n%lf", (float*)pMemLocation) ;
 return 1 ;
 case F_POINT:
  fscanf(pFile, "\t\n%lf", (double*)pMemLocation) ;
  fscanf(pFile, "\t\n%lf", ((double*)pMemLocation + 1)) ;
#ifndef TWO_D
  fscanf(pFile, "\t\n%lf", ((double*)pMemLocation + 2)) ;
#endif // TWO_D
 return 1 ;
 // All Field Types that are ignored
 case F_IGNORE:
 case F_END:
  while (!feof(pFile) && getc(pFile) != '\n') ;
 return 1 ;
 default:
  FatalError ("ReadField - Unknown field type") ;
 return 0 ;
 }
}

int ReadFields (FILE *&pFile, PField *pFields, void *byOffset) // Read in a set of fields
{
 int nIndexReadTo ;
 while (!feof(pFile))
 {
//  fscanf (pFile, "\t\n%256s", szGBuffer) ;
  fscanf (pFile, "%256s", szGBuffer) ;
  if (strcmp(szGBuffer, "}") == 0) return 1 ;
  else if (strcmp(szGBuffer, "Body") == 0)
  {
   if (byOffset != NULL) FatalError ("ReadFields - Body declaration within a previous declaration") ;
   fscanf (pFile, "%256s", szGBuffer) ;
   if (strcmp(szGBuffer, "{") != 0) FatalError ("ReadFields - missing { after Body declaration") ;
   if (pBodyHead == NULL)
   {
	pBodyHead = new Body ;
	pBodyTail = pBodyHead ;
   } else
   {
	pBodyTail->pNext = new Body ;
	pBodyTail->pNext->pLast = pBodyTail ;
	pBodyTail = pBodyTail->pNext ;
   }
   ReadFields(pFile, PFBody, (void*)pBodyTail) ;
  } else if (strcmp(szGBuffer, "Camera") == 0)
  {
   if (byOffset != NULL) FatalError ("ReadFields - Camera declaration within a previous declaration") ;
   fscanf (pFile, "%256s", szGBuffer) ;
   if (strcmp(szGBuffer, "{") != 0) FatalError ("ReadFields - missing { after Camera declaration") ;
   if (pCameraHead == NULL)
   {
	pCameraHead = new Camera ;
	pCameraTail = pCameraHead ;
   } else
   {
	pCameraTail->pNext = new Camera ;
	pCameraTail->pNext->pLast = pCameraTail ;
	pCameraTail = pCameraTail->pNext ;
   }
   ReadFields(pFile, PFCamera, (void*)pCameraTail) ;
  } else
  {
   nIndexReadTo = 0 ;
   while (pFields[nIndexReadTo].Type != F_END && strcmp (pFields[nIndexReadTo].szName, szGBuffer) != 0) nIndexReadTo ++ ;
   if (pFields[nIndexReadTo].Type != F_END) ReadField (pFile, pFields[nIndexReadTo].Type, (void*)((unsigned char*)byOffset + (int)pFields[nIndexReadTo].pVar)) ;
   else while (!feof(pFile) && getc(pFile) != '\n') ;
  }
 }

 return 1 ;
}