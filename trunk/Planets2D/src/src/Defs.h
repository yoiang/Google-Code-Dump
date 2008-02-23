#ifndef __DEFS_H__
#define __DEFS_H__

#define PI 3.14159265358979323846f

#define G 6.67E-11f ;
#define K 9E9f ;

#ifndef STRICT
#define STRICT
#endif

//#define DEG2RAD( x ) ( (x) * PI / 180.0f )

#define TWO_D

#ifdef LONG_DOUBLE
typedef (long double) PointType ;
#else // LONG_DOUBLE
typedef double PointType ;
#endif // LONG_DOUBLE

#define	GFM(x) (&x) // Global File Macro for reading and writing variables to and from files

typedef enum // Types allowed to be read/written to and from files
{
 F_INT,    // int types
 F_FLOAT,  // float types
 F_STRING, // String
 F_POINT, // Point
 F_POINTTYPE, // PointType
 F_IGNORE, // ignore field
 F_END     // end fields array
} FieldTypes ;

typedef struct
{
 char *szName ;
 void *pVar ;
 FieldTypes Type ;
} PField ;

#endif // __DEFS_H__