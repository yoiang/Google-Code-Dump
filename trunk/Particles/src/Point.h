#ifndef __POINT_H__
#define __POINT_H__

#include <math.h>
#include <stdlib.h>

typedef float PointType ;

class Point	// point class
{
public:
	PointType dVal[3] ;	// coordinates of point

	Point() ;	// point constructor
	Point(Point &Copy) ;
	Point(PointType dSetX, PointType dSetY, PointType dSetZ) ;

	// operators
	const Point operator +(const Point &Add) ;
	const Point operator +(const PointType &Add) ;
	const Point operator -(const Point &Subtract) ;
	const Point operator -(const PointType &Subtract) ;
	const Point operator *(const Point &Multiply) ;
	const Point operator *(const PointType &Multiply) ;
	const Point operator /(const Point &Divide) ;
	const Point operator /(const PointType &Divide) ;
	const Point operator =(const Point &Assign) ;
	const Point operator =(const PointType &Assign) ;
	const Point operator =(const PointType *Assign) ;

	const bool operator <(const Point &Compare) ;
	const bool operator <(const PointType &Compare) ;
	const bool operator >(const Point &Compare) ;
	const bool operator >(const PointType &Compare) ;
	const bool operator ==(const Point &Compare) ;

	Point operator +(Point &Add) ;
	Point operator +(PointType &Add) ;
	Point operator -(Point &Subtract) ;
	Point operator -(PointType &Subtract) ;
	Point operator *(Point &Multiply) ;
	Point operator *(PointType &Multiply) ;
	Point operator /(Point &Divide) ;
	Point operator /(PointType &Divide) ;
} ;
	
PointType Distance (Point ptFirst, Point ptSecond) ;	// calculate distance
PointType DotProduct (Point ptFirst, Point ptSecond) ;	// calculate dot product
void CrossProduct (Point ptFirst, Point ptSecond, Point &ptResult) ; // calculate cross product
void Normalize(Point &ptNormalize) ; // normalize vector
Point CalcInitial(Point ptInitial, Point ptDeviance) ;
float InnerProduct(Point ptV, Point ptQ) ;
float RandomPercent() ;

#endif

// Ian Grossberg - 1999