#include "Point.h"

Point::Point()
{
}

Point::Point(PointType dSetX, PointType dSetY, PointType dSetZ)
{
	dVal[0] = dSetX ;
	dVal[1] = dSetY ;
	dVal[2] = dSetZ ;
}

Point Point::operator +(Point &Add)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] + Add.dVal[0] ;
	ptTemp.dVal[1] = dVal[1] + Add.dVal[1] ;
	ptTemp.dVal[2] = dVal[2] + Add.dVal[2] ;
	return ptTemp ;
}

Point Point::operator +(PointType &Add)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] + Add ;
	ptTemp.dVal[1] = dVal[1] + Add ;
	ptTemp.dVal[2] = dVal[2] + Add ;
	return ptTemp ;
}

Point Point::operator -(Point &Subtract)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] - Subtract.dVal[0] ;
	ptTemp.dVal[1] = dVal[1] - Subtract.dVal[1] ;
	ptTemp.dVal[2] = dVal[2] - Subtract.dVal[2] ;
	return ptTemp ;
}

Point Point::operator -(PointType &Subtract)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] - Subtract ;
	ptTemp.dVal[1] = dVal[1] - Subtract ;
	ptTemp.dVal[2] = dVal[2] - Subtract ;
	return ptTemp ;
}

Point Point::operator *(Point &Multiply)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] * Multiply.dVal[0] ;
	ptTemp.dVal[1] = dVal[1] * Multiply.dVal[1] ;
	ptTemp.dVal[2] = dVal[2] * Multiply.dVal[2] ;
	return ptTemp ;
}

Point Point::operator *(PointType &Multiply)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] * Multiply ;
	ptTemp.dVal[1] = dVal[1] * Multiply ;
	ptTemp.dVal[2] = dVal[2] * Multiply ;
	return ptTemp ;
}

Point Point::operator /(Point &Divide)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] / Divide.dVal[0] ;
	ptTemp.dVal[1] = dVal[1] / Divide.dVal[1] ;
	ptTemp.dVal[2] = dVal[2] / Divide.dVal[2] ;
	return ptTemp ;
}

Point Point::operator /(PointType &Divide)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] / Divide ;
	ptTemp.dVal[1] = dVal[1] / Divide ;
	ptTemp.dVal[2] = dVal[2] / Divide ;
	return ptTemp ;
}

const Point Point::operator +(const Point &Add)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] + Add.dVal[0] ;
	ptTemp.dVal[1] = dVal[1] + Add.dVal[1] ;
	ptTemp.dVal[2] = dVal[2] + Add.dVal[2] ;
	return ptTemp ;
}

const Point Point::operator +(const PointType &Add)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] + Add ;
	ptTemp.dVal[1] = dVal[1] + Add ;
	ptTemp.dVal[2] = dVal[2] + Add ;
	return ptTemp ;
}

const Point Point::operator -(const Point &Subtract)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] - Subtract.dVal[0] ;
	ptTemp.dVal[1] = dVal[1] - Subtract.dVal[1] ;
	ptTemp.dVal[2] = dVal[2] - Subtract.dVal[2] ;
	return ptTemp ;
}

const Point Point::operator -(const PointType &Subtract)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] - Subtract ;
	ptTemp.dVal[1] = dVal[1] - Subtract ;
	ptTemp.dVal[2] = dVal[2] - Subtract ;
	return ptTemp ;
}

const Point Point::operator *(const Point &Multiply)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] * Multiply.dVal[0] ;
	ptTemp.dVal[1] = dVal[1] * Multiply.dVal[1] ;
	ptTemp.dVal[2] = dVal[2] * Multiply.dVal[2] ;
	return ptTemp ;
}

const Point Point::operator *(const PointType &Multiply)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] * Multiply ;
	ptTemp.dVal[1] = dVal[1] * Multiply ;
	ptTemp.dVal[2] = dVal[2] * Multiply ;
	return ptTemp ;
}

const Point Point::operator /(const Point &Divide)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] / Divide.dVal[0] ;
	ptTemp.dVal[1] = dVal[1] / Divide.dVal[1] ;
	ptTemp.dVal[2] = dVal[2] / Divide.dVal[2] ;
	return ptTemp ;
}

const Point Point::operator /(const PointType &Divide)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] / Divide ;
	ptTemp.dVal[1] = dVal[1] / Divide ;
	ptTemp.dVal[2] = dVal[2] / Divide ;
	return ptTemp ;
}

const Point Point::operator =(const Point &Assign)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] = Assign.dVal[0] ;
	ptTemp.dVal[1] = dVal[1] = Assign.dVal[1] ;
	ptTemp.dVal[2] = dVal[2] = Assign.dVal[2] ;
	return ptTemp ;
}

const Point Point::operator =(const PointType &Assign)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] = Assign ;
	ptTemp.dVal[1] = dVal[1] = Assign ;
	ptTemp.dVal[2] = dVal[2] = Assign ;
	return ptTemp ;
}

const Point Point::operator =(const PointType *Assign)
{
	Point ptTemp ;
	ptTemp.dVal[0] = dVal[0] = Assign[0] ;
	ptTemp.dVal[1] = dVal[1] = Assign[1] ;
	ptTemp.dVal[2] = dVal[2] = Assign[2] ;
	return ptTemp ;
}


const bool Point::operator <(const Point &Compare)
{
	if (dVal[0] < Compare.dVal[0] && dVal[1] < Compare.dVal[1] && dVal[2] < Compare.dVal[2]) return true ;
	return false ;
}

const bool Point::operator <(const PointType &Compare)
{
	if (dVal[0] < Compare && dVal[1] < Compare && dVal[2] < Compare) return true ;
	return false ;
}

const bool Point::operator >(const Point &Compare)
{
	if (dVal[0] > Compare.dVal[0] && dVal[1] > Compare.dVal[1] && dVal[2] > Compare.dVal[2]) return true ;
	return false ;
}

const bool Point::operator >(const PointType &Compare)
{
	if (dVal[0] > Compare && dVal[1] > Compare && dVal[2] > Compare) return true ;
	return false ;
}

PointType Distance (Point ptFirst, Point ptSecond)
{
 ptFirst.dVal[0] = ptFirst.dVal[0] - ptSecond.dVal[0] ;
 ptFirst.dVal[1] = ptFirst.dVal[1] - ptSecond.dVal[1] ;
 ptFirst.dVal[2] = ptFirst.dVal[2] - ptSecond.dVal[2] ;

 ptFirst.dVal[0] *= ptFirst.dVal[0] ;
 ptFirst.dVal[1] *= ptFirst.dVal[1] ;
 ptFirst.dVal[2] *= ptFirst.dVal[2] ;

 return PointType(sqrt (ptFirst.dVal[0] + ptFirst.dVal[1] + ptFirst.dVal[2])) ;
}

PointType Distance2D (Point ptFirst, Point ptSecond)
{
 ptFirst.dVal[0] = ptFirst.dVal[0] - ptSecond.dVal[0] ;
 ptFirst.dVal[1] = ptFirst.dVal[1] - ptSecond.dVal[1] ;

 ptFirst.dVal[0] *= ptFirst.dVal[0] ;
 ptFirst.dVal[1] *= ptFirst.dVal[1] ;

 return PointType(sqrt (ptFirst.dVal[0] + ptFirst.dVal[1])) ;
}

PointType DotProduct (Point ptFirst, Point ptSecond)
{ return ptFirst.dVal[0] * ptSecond.dVal[0] + ptFirst.dVal[1] * ptSecond.dVal[1] + ptFirst.dVal[2] * ptSecond.dVal[2] ; }

void CrossProduct (Point ptFirst, Point ptSecond, Point &ptResult)
{
 ptResult.dVal[0] = ptFirst.dVal[1] * ptSecond.dVal[2] - ptFirst.dVal[2] * ptSecond.dVal[1] ;
 ptResult.dVal[1] = ptFirst.dVal[2] * ptSecond.dVal[0] - ptFirst.dVal[0] * ptSecond.dVal[2] ;
 ptResult.dVal[2] = ptFirst.dVal[0] * ptSecond.dVal[1] - ptFirst.dVal[1] * ptSecond.dVal[0] ;
}

void Normalize(Point &ptNormalize)
{
	PointType dMagnitude = PointType(sqrt(ptNormalize.dVal[0] * ptNormalize.dVal[0] + ptNormalize.dVal[1] * ptNormalize.dVal[1] + ptNormalize.dVal[2] * ptNormalize.dVal[2])) ;
	ptNormalize.dVal[0] /= dMagnitude ;
	ptNormalize.dVal[1] /= dMagnitude ;
	ptNormalize.dVal[2] /= dMagnitude ;
}

float randp()
{
	return float(rand())/float(RAND_MAX) ;
}

Point CalcInitial(Point ptInitial, Point ptDeviance)
{
	Point ptTemp ;
	ptTemp.dVal[0] = ptInitial.dVal[0] + ptDeviance.dVal[0] * randp() - ptDeviance.dVal[0] / 2.0 ;
	ptTemp.dVal[1] = ptInitial.dVal[1] + ptDeviance.dVal[1] * randp() - ptDeviance.dVal[1] / 2.0 ;
	ptTemp.dVal[2] = ptInitial.dVal[2] + ptDeviance.dVal[2] * randp() - ptDeviance.dVal[2] / 2.0 ;
	return ptTemp ;
}


float InnerProduct(Point ptV, Point ptQ)
{
	return 
		ptV.dVal[0] * ptQ.dVal[0] +
		ptV.dVal[1] * ptQ.dVal[1] +
		ptV.dVal[2] * ptQ.dVal[2] ;
}