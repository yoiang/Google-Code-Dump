/*
 
  Defs.h
  Version 0.004.000

*/
  
#ifndef __DEFS_H__
#define __DEFS_H__

// 32 individual bits for use in bitmaps
#define BIT00 (1 << 0)
#define BIT01 (1 << 1)
#define BIT02 (1 << 2)
#define BIT03 (1 << 3)
#define BIT04 (1 << 4)
#define BIT05 (1 << 5)
#define BIT06 (1 << 6)
#define BIT07 (1 << 7)
#define BIT08 (1 << 8)
#define BIT09 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1 << 31)

#define DEFAULT_PORT 4000

#define MAX_FILE_NUMBER 9999
#define MAX_FILE_DIGITS 4

class Entity ; // Entity class prototype

#define	GFM(x) (&x) // Global File Macro for reading and writing variables to and from files

typedef enum // Types allowed to be read/written to and from files
{
 F_INT, // int types
 F_FLOAT, // float types
 F_LONG, // long types
// F_BYTE,
// F_BOOL,
 F_STRING,
// F_VECTOR,
 F_POINT, // Normal pointer
// F_PPOINT,
 F_HANDLE, // Windows handle
 F_TYPE,   // Field Type
 F_PFIELD, // Point Field
 F_TPOINT, // Type pointer
 F_CPOINT, // Contained pointer
 F_IGNORE, // ignore field
 F_END // end fields array
} FieldTypes ;

typedef struct
{
 char *szName ;
 void *pVar ;
 FieldTypes Type ;
} PField ;

typedef struct
{
 char *szName ;
 void (*pVar)(Entity *pSelf) ;
} PFField ;

typedef struct
{
 char *szName ;
 void (*Command)(Entity *pEntity, char *szParam) ;
} PCommand ;

//#define MAX_CONNECTION_REQUESTS 50 // Maximum connection requests at once
//#define DEFAULT_PORT 4000 // Default connection port

// Probably temporary (breaks seperation of app and server)
// Application Specific Messages
//#define MW_CONNECTED 200 // Connection request
//#define MW_DATAREADY 201 // Data ready from transmision

#endif // __DEFS_H__
