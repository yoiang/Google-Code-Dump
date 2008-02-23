/*

  Files.h
  Version 0.004.000

*/

#ifndef __FILES_H__
#define __FILES_H__

int ReadNumScripts (char *szFileName, Entity *&pEntity, int nEntType, Entity *pOwner) ;
int ReadScript (char *szFileName, Entity *pEntity, int nEntType, Entity *pOwner) ;

int ReadField (FILE *&pFile, FieldTypes Type, void* pMemLocation) ;
int ReadFields (char *szFileName, PField *pFields, void *byOffset) ; // Read in a set of fields

#endif // __FILES_H__