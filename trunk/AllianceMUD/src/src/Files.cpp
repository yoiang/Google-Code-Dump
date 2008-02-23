/*

  Files.cpp
  Version 0.004.000

*/

#include "Main.h"

int ReadNumScripts (char *szFileName, Entity *&pEntity, int nEntType, Entity *pOwner)
{
 int nLFileName = strlen(szFileName) ;
 char *szFile = new char [nLFileName + MAX_FILE_DIGITS + 1] ;
#ifdef MEM_DEBUG
 if (szFile == NULL) FatalError("ReadNumScripts - Heap overflow") ;
#endif // MEM_DEBUG
 sprintf (szFile, "%s%i", szFileName, MAX_FILE_NUMBER) ;
 int nNumDigit ;
 for (int nNumFile = 0 ; nNumFile < MAX_FILE_NUMBER ; nNumFile ++)
 {
  for (nNumDigit = 1 ; nNumDigit <= MAX_FILE_DIGITS ; nNumDigit ++)
  {
   szFile[nLFileName + nNumDigit - 1] = char ('0' + int (nNumFile / (pow (10, (MAX_FILE_DIGITS - nNumDigit))))) ;
  }
  if (pEntity == NULL)
  {
   pEntity = new Entity ;
#ifdef MEM_DEBUG
   if (pEntity == NULL) FatalError("ReadNumScripts - Heap overflow") ;
#endif // MEM_DEBUG
   if (!ReadScript (szFile, pEntity, nEntType, pOwner))
   {
    delete pEntity ;
	pEntity = NULL ;
    delete [] szFile ;
	return 0 ;
   }
   pEntity->pOwner = pOwner ;
   pEntity->Register () ;
  } else
  {
   pEntity->pNext = new Entity ;
#ifdef MEM_DEBUG
   if (pEntity->pNext == NULL) FatalError("ReadNumScripts - Heap overflow") ;
#endif // MEM_DEBUG
   if (!ReadScript (szFile, pEntity->pNext, nEntType, pOwner))
   {
    delete pEntity->pNext ;
	pEntity->pNext = NULL ;
	while (pEntity->pLast != NULL) pEntity = pEntity->pLast ;
    delete [] szFile ;
	return nNumFile ;
	}
   pEntity->pNext->pOwner = pOwner ;
   pEntity->pNext->pLast = pEntity ;
   pEntity = pEntity->pNext ;
   pEntity->Register () ;
  }
 }
 while (pEntity->pLast != NULL) pEntity = pEntity->pLast ;
 return nNumFile ;
}

int ReadScript (char *szFileName, Entity *pEntity, int nEntType, Entity *pOwner)
{
 char *szFile = new char [strlen (szFileName) + 5] ;
#ifdef MEM_DEBUG
 if (szFile == NULL) FatalError("ReadScript - Heap overflow") ;
#endif // MEM_DEBUG
 sprintf (szFile, "%s.ent", szFileName) ;

 if (!ReadFields (szFile, EntPField, pEntity)) 
 {
  delete [] szFile ;
  return 0 ;
 }

 if (nEntType) ReadFields (szFile, (PField*)(EntTypePField[nEntType][1].pVar), (void*)((byte*)pEntity + (int)EntTypePField[nEntType][0].pVar)) ; 
 else
 {
  delete [] szFile ;
  return 0 ;
 }

 int nFunc = 0 ;
 while (strcmp(((PFField*)(EntTypePField[nEntType][2].pVar))[nFunc].szName, "END") != 0 && strcmp(((PFField*)(EntTypePField[nEntType][2].pVar))[nFunc].szName, "Spawn") != 0) nFunc ++ ;
 if (strcmp(((PFField*)(EntTypePField[nEntType][2].pVar))[nFunc].szName, "END") != 0)
 {
  pEntity->Spawn = (((PFField*)(EntTypePField[nEntType][2].pVar))[nFunc].pVar) ;
 }
 nFunc = 0 ;
 while (strcmp(((PFField*)(EntTypePField[nEntType][2].pVar))[nFunc].szName, "END") != 0 && strcmp(((PFField*)(EntTypePField[nEntType][2].pVar))[nFunc].szName, "Die") != 0) nFunc ++ ;
 if (strcmp(((PFField*)(EntTypePField[nEntType][2].pVar))[nFunc].szName, "END") != 0)
 {
  pEntity->Die = (((PFField*)(EntTypePField[nEntType][2].pVar))[nFunc].pVar) ;
 }

 pEntity->nEntType = nEntType ;

 TVITEM hTVI ;
 TVINSERTSTRUCT hTVIns ;

 hTVI.mask = TVIF_TEXT | TVIF_PARAM ; //| TVIF_IMAGE | TVIF_SELECTEDIMAGE ;

 if (pEntity->szName != NULL)
 {
  hTVI.pszText = new char [strlen(szFile) + strlen (pEntity->szName) + 6] ;
#ifdef MEM_DEBUG
  if (hTVI.pszText == NULL) FatalError("ReadScript - Heap overflow") ;
#endif // MEM_DEBUG
  sprintf (hTVI.pszText, "%s - \"%s\"", szFile, pEntity->szName) ;
  hTVI.cchTextMax = strlen(szFile) + strlen (pEntity->szName) ;
 } else
 {
  hTVI.pszText = new char [strlen(szFile) + 1] ;
#ifdef MEM_DEBUG
  if (hTVI.pszText == NULL) FatalError("ReadScript - Heap overflow") ;
#endif // MEM_DEBUG
  sprintf (hTVI.pszText, "%s", szFile) ;
  hTVI.cchTextMax = strlen(szFile) ;
 }
// hTVI.iImage = NULL ;
// hTVI.iSelectedImage = NULL ;
 hTVIns.item = hTVI ;
 if (pOwner == NULL)
 {
  hTVIns.hInsertAfter = TVI_LAST ;
  hTVIns.hParent = TVI_ROOT ;
 } else
 {
  hTVIns.hInsertAfter = TVI_LAST ;
  hTVIns.hParent = pOwner->hTreeItem ;
 }

 pEntity->hTreeItem = (HTREEITEM) SendMessage(hEntitys, TVM_INSERTITEM, 0, (LPARAM)(LPTVINSERTSTRUCT) &hTVIns) ;
#ifdef MEM_DEBUG
 if (pEntity->hTreeItem == 0) Logs.AddLine("ReadNumScripts - SendMessage(TVM_INSERTITEM) failed") ;
#endif // MEM_DEBUG

 if (!SetCurrentDirectory (szFileName)) 
 {
  delete [] szFile ;
  return 1 ;
 }

 int nType = 1 ;
 while (EntPField[nType].Type != F_END)
 {
  if (EntPField[nType].Type == F_CPOINT)
  {
   ReadNumScripts (EntPField[nType].szName, *(Entity**)((byte*)pEntity + (int)EntPField[nType].pVar), nType, pEntity) ;
  }
  nType ++ ;
 }
 SetCurrentDirectory ("..") ;
 delete [] szFile ;
 return 1 ;
}

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
 case F_LONG:
  fscanf (pFile, "\t\n%li", (long*)pMemLocation) ;
 return 1 ;
//	case F_BYTE:
//	 fscanf (pFile, "\t\n%i", &nTempInt) ;
//	 *(unsigned char*)pMemLocation = nTempInt ;
//	return 1 ;
// case F_BOOL:
 case F_STRING:
  char szString[2] ;
  fscanf (pFile, "%1[ ]%256[^\n\0]", szString, szGBuffer) ;
  *(char **)pMemLocation = new char [strlen(szGBuffer) + 1] ;
#ifdef MEM_DEBUG
  if (*(char **)pMemLocation == NULL) FatalError("ReadField - Heap overflow") ;
#endif // MEM_DEBUG
  sprintf(*(char **)pMemLocation, "%s", szGBuffer) ;
 return 1 ;
// case F_VECTOR:
//	 fscanf (pFile, "\t\n%f", (float*)pMemLocation) ;
//	 fscanf (pFile, "\t\n%f", ((float*)pMemLocation + 1)) ;
//	 fscanf (pFile, "\t\n%f", ((float*)pMemLocation + 2)) ;
//	return 1 ;

// case F_PPOINT:

// All Field Types that are ignored
 case F_HANDLE: // Windows handle
 case F_POINT:  // Normal Pointer
 case F_TYPE:   // Field Type
 case F_PFIELD: // Point Field
 case F_TPOINT: // Type pointer
 case F_CPOINT: // Contained pointer
 case F_IGNORE:
 case F_END:
  while (!feof(pFile) && getc(pFile) != '\n') ;
 return 1 ;
 default:
  Logs.AddLine ("ReadField - Unknown field type") ;
 return 0 ;
 }
}

int ReadFields (char *szFileName, PField *pFields, void *byOffset) // Read in a set of fields
{
 int nIndexReadTo ;
 FILE *pFile ;
 if ((pFile = fopen (szFileName, "rt")) == NULL) return 0 ;

 while (!feof(pFile))
 {
//  fscanf (pFile, "\t\n%256s", szGBuffer) ;
  fscanf (pFile, "%256s", szGBuffer) ;
  if (szGBuffer[0] == ';') while (!feof(pFile) && fgetc(pFile) != '\n') ;
  else
  {
	nIndexReadTo = 0 ;
	while (pFields[nIndexReadTo].Type != F_END && strcmp (pFields[nIndexReadTo].szName, szGBuffer) != 0) nIndexReadTo ++ ;
	if (pFields[nIndexReadTo].Type != F_END) ReadField (pFile, pFields[nIndexReadTo].Type, (void*)((byte*)byOffset + (int)pFields[nIndexReadTo].pVar)) ;
	else while (!feof(pFile) && getc(pFile) != '\n') ;
  }
 }
 fclose(pFile) ;
 return 1 ;
}

/*int WriteField (FILE *&pFile, FieldTypes Type, char *szName, void* pMemLocation)
{
 switch (Type)
 {
 case F_IGNORE:
 case F_END:
 case F_POINT:
 return 1 ;
 case F_FLOAT:
  fprintf(pFile, "%s %f\n", szName, *(float*)pMemLocation) ;
 return 1 ;
 case F_LONG:
  fprintf(pFile, "%s %li\n", szName, *(long*)pMemLocation) ;
 return 1 ;
 case F_STRING:
  fprintf(pFile, "%s %s\n", szName, *(char*)pMemLocation) ;
 return 1 ;
// case F_BYTE:
// int nTempChar ;
//  nTempChar = *(unsigned char*)pMemLocation ;
//  fprintf(pFile, "%s %i\n", szName, nTempChar) ;
// break ;
 case F_BOOL:
 case F_INT:
// case F_HANDLE:
  fprintf(pFile, "%s %i\n", szName, *(int*)pMemLocation) ;
 return 1 ;
// case F_VECTOR:
//  fprintf(pFile, "%s %f %f %f\n", szName, *(float*)pMemLocation, *((float*)pMemLocation + 1), *((float*)pMemLocation + 2)) ;
// break ;
 default: 
  Logs.AddLine ("WriteField - Unknown type") ;
 return 0 ;
 }
}

int WriteFields (char *szFileName, PField *pFields, void *vMemLocation) // Write a set of fields
{
 FILE *pFile ;
 if ((pFile = fopen (szFileName, "wt")) == NULL)
 {
  sprintf(szGBuffer, "%.51s for writing", szFileName) ;
  Logs.AddLine ("ReadInFile: cannot open file ", szGBuffer) ;
  return 0 ;
 }

 int nIndexWriteTo = 0 ;
 int nNumCompositeIfs = 0 ;
 int nIfResult = 0 ;
 while (pFields[nIndexWriteTo].Type != F_END)
 {
  if (strcmp(pFields[nIndexWriteTo].szName, "if") == 0)      
  {
   nNumCompositeIfs = 1 ;
   switch (pFields[nIndexWriteTo].Type)
   {
   case F_FLOAT:
    nIfResult = ((*(float*)((byte*)vMemLocation + (int)pFields[nIndexWriteTo].pVar)) != 0) ;
   break ;
   case F_LONG:
    nIfResult = ((*(long*)((byte*)vMemLocation + (int)pFields[nIndexWriteTo].pVar)) != 0) ;
   break ;
//   case F_BYTE:
//    nIfResult = ((*(unsigned char*)((byte*)vMemLocation + (int)pFields[nIndexWriteTo].pVar)) != 0) ;
//   break ;
   case F_BOOL:
	case F_INT:
//   case F_HANDLE:
    nIfResult = ((*(int*)((byte*)vMemLocation + (int)pFields[nIndexWriteTo].pVar)) != 0) ;
  break ;
   default: 
	Logs.AddLine ("WriteFields - Unknown or invalid \"if\" type") ;
	nIfResult = 0 ;
   break ;
   }
   if (nIfResult == 0) 
   {
	while (pFields[nIndexWriteTo].Type != F_END && nNumCompositeIfs > 0) 
	 {
	 if (strcmp(pFields[nIndexWriteTo].szName, "if") == 0) nNumCompositeIfs ++ ;
     else if (strcmp(pFields[nIndexWriteTo].szName, "endif") == 0) nNumCompositeIfs -- ;
	 nIndexWriteTo ++ ;
	}
	if (pFields[nIndexWriteTo].Type == F_END) nIndexWriteTo -- ;
   } else 
   {
	nIndexWriteTo ++ ;
	WriteField(pFile, pFields[nIndexWriteTo].Type, pFields[nIndexWriteTo].szName, (void*)((byte*)vMemLocation + (int)pFields[nIndexWriteTo].pVar)) ;
   }
  } else WriteField(pFile, pFields[nIndexWriteTo].Type, pFields[nIndexWriteTo].szName, (void*)((byte*)vMemLocation + (int)pFields[nIndexWriteTo].pVar)) ;
  nIndexWriteTo ++ ;
 }
 fclose(pFile) ;
 return 1 ;
} */
