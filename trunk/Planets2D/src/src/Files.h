#ifndef __FILES_H__
#define __FILES_H__

int ReadField (FILE *&pFile, FieldTypes Type, void* pMemLocation) ; // Read in a field
int ReadFields (FILE *&pFile, PField *pFields, void *byOffset) ; // Read in a set of fields

#endif // __FILES_H__