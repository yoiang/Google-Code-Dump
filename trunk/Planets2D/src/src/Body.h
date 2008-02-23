#ifndef __BODY_H__
#define __BODY_H__

class Body
{
public :
 Point ptLocation ;
 Point ptOldLocation ;
 Point ptVelocity ;
 Point ptNetForce ;
 Point ptOldNetForce ;

 PointType dMass ;
 PointType dMassTimesCoefficent ;
 PointType dKineticEnergy ;
 Point ptCenterOfMass ;
 Point ptRadius ;

 int nRed, nGreen, nBlue ;
 int nNameRed, nNameGreen, nNameBlue ;
// int bTrail ;

 char *szName ;

 Body *pLast ;
 Body *pNext ;

 void Recalc (Body *pBody) ;

 Body() ;
 ~Body() ;
} ;

#define BODYFM(x) (void *)&(((Body *)0)->x)

extern PField PFBody [] ;

#endif // __BODY_H__