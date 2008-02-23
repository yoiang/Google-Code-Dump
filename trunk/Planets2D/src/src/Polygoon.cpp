#include "Main.h"

#ifdef TWO_D
PointType Distance (Point ptFirst, Point ptSecond)
{
 ptFirst.dX = ptFirst.dX - ptSecond.dX ;
 ptFirst.dY = ptFirst.dY - ptSecond.dY ;

 ptFirst.dX *= ptFirst.dX ;
 ptFirst.dY *= ptFirst.dY ;

#ifdef LONG_DOUBLE
 return sqrtl (ptFirst.dX + ptFirst.dY) ;
#else
 return sqrt (ptFirst.dX + ptFirst.dY) ;
#endif // LONG_DOUBLE
}

#else // TWO_D
PointType Distance (Point ptFirst, Point ptSecond)
{
 ptFirst.dX = ptFirst.dX - ptSecond.dX ;
 ptFirst.dY = ptFirst.dY - ptSecond.dY ;
 ptFirst.dZ = ptFirst.dZ - ptSecond.dZ ;

 ptFirst.dX *= ptFirst.dX ;
 ptFirst.dY *= ptFirst.dY ;
 ptFirst.dZ *= ptFirst.dZ ;

#ifdef LONG_DOUBLE
 return sqrtl (ptFirst.dX + ptFirst.dY + ptFirst.dZ) ;
#else // LONG_DOUBLE
 return sqrt (ptFirst.dX + ptFirst.dY + ptFirst.dZ) ;
#endif // LONG_DOUBLE
}

PointType DotProduct (Point ptFirst, Point ptSecond)
{ return ptFirst.dX * ptSecond.dX + ptFirst.dY * ptSecond.dY + ptFirst.dZ * ptSecond.dZ ; }

void CrossProduct (Point ptFirst, Point ptSecond, Point &ptResult)
{
 ptResult.dX = ptFirst.dY * ptSecond.dZ - ptFirst.dZ * ptSecond.dY ;
 ptResult.dY = ptFirst.dZ * ptSecond.dX - ptFirst.dX * ptSecond.dZ ;
 ptResult.dZ = ptFirst.dX * ptSecond.dY - ptFirst.dY * ptSecond.dX ;
}

#endif // TWO_D

