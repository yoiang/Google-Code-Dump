#ifndef __POLYGOON_H__
#define __POLYGOON_H__

#ifdef TWO_D
struct Point
{
 PointType dX, dY ;
} ;

PointType Distance (Point ptFirst, Point ptSecond) ;

#else // TWO_D
struct Point
{
 PointType dX, dY, dZ ;
} ;

PointType Distance (Point ptFirst, Point ptSecond) ;
PointType DotProduct (Point ptFirst, Point ptSecond) ;
void CrossProduct (Point ptFirst, Point ptSecond, Point &ptResult) ;

#endif // TWO_D

#endif // __POLYGOON_H__
