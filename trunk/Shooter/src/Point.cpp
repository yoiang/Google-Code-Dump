#include "Point.h"

Point::Point()
{
}

Point::Point(PointType dSetX, PointType dSetY, PointType dSetZ)
{
	dX = dSetX ;
	dY = dSetY ;
	dZ = dSetZ ;
}

Point Point::operator +(Point &Add)
{
	Point ptTemp ;
	ptTemp.dX = dX + Add.dX ;
	ptTemp.dY = dY + Add.dY ;
	ptTemp.dZ = dZ + Add.dZ ;
	return ptTemp ;
}

Point Point::operator +(PointType &Add)
{
	Point ptTemp ;
	ptTemp.dX = dX + Add ;
	ptTemp.dY = dY + Add ;
	ptTemp.dZ = dZ + Add ;
	return ptTemp ;
}

Point Point::operator -(Point &Subtract)
{
	Point ptTemp ;
	ptTemp.dX = dX - Subtract.dX ;
	ptTemp.dY = dY - Subtract.dY ;
	ptTemp.dZ = dZ - Subtract.dZ ;
	return ptTemp ;
}

Point Point::operator -(PointType &Subtract)
{
	Point ptTemp ;
	ptTemp.dX = dX - Subtract ;
	ptTemp.dY = dY - Subtract ;
	ptTemp.dZ = dZ - Subtract ;
	return ptTemp ;
}

Point Point::operator *(Point &Multiply)
{
	Point ptTemp ;
	ptTemp.dX = dX * Multiply.dX ;
	ptTemp.dY = dY * Multiply.dY ;
	ptTemp.dZ = dZ * Multiply.dZ ;
	return ptTemp ;
}

Point Point::operator *(PointType &Multiply)
{
	Point ptTemp ;
	ptTemp.dX = dX * Multiply ;
	ptTemp.dY = dY * Multiply ;
	ptTemp.dZ = dZ * Multiply ;
	return ptTemp ;
}

Point Point::operator /(Point &Divide)
{
	Point ptTemp ;
	ptTemp.dX = dX / Divide.dX ;
	ptTemp.dY = dY / Divide.dY ;
	ptTemp.dZ = dZ / Divide.dZ ;
	return ptTemp ;
}

Point Point::operator /(PointType &Divide)
{
	Point ptTemp ;
	ptTemp.dX = dX / Divide ;
	ptTemp.dY = dY / Divide ;
	ptTemp.dZ = dZ / Divide ;
	return ptTemp ;
}

const Point Point::operator +(const Point &Add)
{
	Point ptTemp ;
	ptTemp.dX = dX + Add.dX ;
	ptTemp.dY = dY + Add.dY ;
	ptTemp.dZ = dZ + Add.dZ ;
	return ptTemp ;
}

const Point Point::operator +(const PointType &Add)
{
	Point ptTemp ;
	ptTemp.dX = dX + Add ;
	ptTemp.dY = dY + Add ;
	ptTemp.dZ = dZ + Add ;
	return ptTemp ;
}

const Point Point::operator -(const Point &Subtract)
{
	Point ptTemp ;
	ptTemp.dX = dX - Subtract.dX ;
	ptTemp.dY = dY - Subtract.dY ;
	ptTemp.dZ = dZ - Subtract.dZ ;
	return ptTemp ;
}

const Point Point::operator -(const PointType &Subtract)
{
	Point ptTemp ;
	ptTemp.dX = dX - Subtract ;
	ptTemp.dY = dY - Subtract ;
	ptTemp.dZ = dZ - Subtract ;
	return ptTemp ;
}

const Point Point::operator *(const Point &Multiply)
{
	Point ptTemp ;
	ptTemp.dX = dX * Multiply.dX ;
	ptTemp.dY = dY * Multiply.dY ;
	ptTemp.dZ = dZ * Multiply.dZ ;
	return ptTemp ;
}

const Point Point::operator *(const PointType &Multiply)
{
	Point ptTemp ;
	ptTemp.dX = dX * Multiply ;
	ptTemp.dY = dY * Multiply ;
	ptTemp.dZ = dZ * Multiply ;
	return ptTemp ;
}

const Point Point::operator /(const Point &Divide)
{
	Point ptTemp ;
	ptTemp.dX = dX / Divide.dX ;
	ptTemp.dY = dY / Divide.dY ;
	ptTemp.dZ = dZ / Divide.dZ ;
	return ptTemp ;
}

const Point Point::operator /(const PointType &Divide)
{
	Point ptTemp ;
	ptTemp.dX = dX / Divide ;
	ptTemp.dY = dY / Divide ;
	ptTemp.dZ = dZ / Divide ;
	return ptTemp ;
}

const Point Point::operator =(const Point &Assign)
{
	Point ptTemp ;
	ptTemp.dX = dX = Assign.dX ;
	ptTemp.dY = dY = Assign.dY ;
	ptTemp.dZ = dZ = Assign.dZ ;
	return ptTemp ;
}

const Point Point::operator =(const PointType &Assign)
{
	Point ptTemp ;
	ptTemp.dX = dX = Assign ;
	ptTemp.dY = dY = Assign ;
	ptTemp.dZ = dZ = Assign ;
	return ptTemp ;
}

const bool Point::operator <(const Point &Compare)
{
	if (dX < Compare.dX && dY < Compare.dY && dZ < Compare.dZ) return true ;
	return false ;
}

const bool Point::operator <(const PointType &Compare)
{
	if (dX < Compare && dY < Compare && dZ < Compare) return true ;
	return false ;
}

const bool Point::operator >(const Point &Compare)
{
	if (dX > Compare.dX && dY > Compare.dY && dZ > Compare.dZ) return true ;
	return false ;
}

const bool Point::operator >(const PointType &Compare)
{
	if (dX > Compare && dY > Compare && dZ > Compare) return true ;
	return false ;
}

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

PointType Distance2D (Point ptFirst, Point ptSecond)
{
 ptFirst.dX = ptFirst.dX - ptSecond.dX ;
 ptFirst.dY = ptFirst.dY - ptSecond.dY ;

 ptFirst.dX *= ptFirst.dX ;
 ptFirst.dY *= ptFirst.dY ;

#ifdef LONG_DOUBLE
 return sqrtl (ptFirst.dX + ptFirst.dY) ;
#else // LONG_DOUBLE
 return sqrt (ptFirst.dX + ptFirst.dY) ;
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

void Normalize(Point &ptNormalize)
{
	PointType dMagnitude = sqrt(ptNormalize.dX * ptNormalize.dX + ptNormalize.dY * ptNormalize.dY + ptNormalize.dZ * ptNormalize.dZ) ;
	ptNormalize.dX /= dMagnitude ;
	ptNormalize.dY /= dMagnitude ;
	ptNormalize.dZ /= dMagnitude ;
}

