#include "Main.h"

Body::Body()
{
#ifdef TWO_D
// ptLocation = {0.0f, 0.0f} ;
 ptLocation.dX = 0.0f ;
 ptLocation.dY = 0.0f ;

// ptVelocity = {0.0f, 0.0f} ;
 ptVelocity.dX = 0.0f ;
 ptVelocity.dY = 0.0f ;

// ptOld = {0.0f, 0.0f} ;
 ptOldLocation.dX = 0.0f ;
 ptOldLocation.dY = 0.0f ;

// ptCenterOfMass = {0.0f, 0.0f} ;
 ptCenterOfMass.dX = 0.0f ;
 ptCenterOfMass.dY = 0.0f ;

 // ptRadius = {0.0f, 0.0f} ;
 ptRadius.dX = 0.0f ;
 ptRadius.dY = 0.0f ;

// ptNetForce = {0.0f, 0.0f} ;
 ptNetForce.dX = 0.0f ;
 ptNetForce.dY = 0.0f ;

// ptOldNetForce = {0.0f, 0.0f} ;
 ptOldNetForce.dX = 0.0f ;
 ptOldNetForce.dY = 0.0f ;

#else // TWO_D
// ptLocation = {0.0f, 0.0f, 0.0f} ;
 ptLocation.dX = 0.0f ;
 ptLocation.dY = 0.0f ;
 ptLocation.dZ = 0.0f ;

// ptVelocity = {0.0f, 0.0f, 0.0f} ;
 ptVelocity.dX = 0.0f ;
 ptVelocity.dY = 0.0f ;
 ptVelocity.dZ = 0.0f ;

// ptOld = {0.0f, 0.0f, 0.0f} ;
 ptOldLocation.dX = 0.0f ;
 ptOldLocation.dY = 0.0f ;
 ptOldLocation.dZ = 0.0f ;


// ptCenterOfMass = {0.0f, 0.0f, 0.0f} ;
 ptCenterOfMass.dX = 0.0f ;
 ptCenterOfMass.dY = 0.0f ;
 ptCenterOfMass.dZ = 0.0f ;

 // ptRadius = {0.0f, 0.0f, 0.0f} ;
 ptRadius.dX = 0.0f ;
 ptRadius.dY = 0.0f ;
 ptRadius.dZ = 0.0f ;

// ptNetForce = {0.0f, 0.0f, 0.0f} ;
 ptNetForce.dX = 0.0f ;
 ptNetForce.dY = 0.0f ;
 ptNetForce.dZ = 0.0f ;

// ptOldNetForce = {0.0f, 0.0f, 0.0f} ;
 ptOldNetForce.dX = 0.0f ;
 ptOldNetForce.dY = 0.0f ;
 ptOldNetForce.dZ = 0.0f ;
#endif // TWO_D

// pModel = NULL ;

 dMass = 0.0f ;
 dMassTimesCoefficent = 0.0f ;
 dKineticEnergy = 0.0f ;

 szName = NULL ;

 pLast = NULL ;
 pNext = NULL ;

 nRed = 255 ;
 nGreen = 255 ;
 nBlue = 255 ;
 nNameRed = 100 ;
 nNameGreen = 100 ;
 nNameBlue = 100 ;
}

Body::~Body()
{
 if (szName != NULL) delete [] szName ;
}

#ifdef TWO_D

void Body::Recalc (Body *pBody)
{
 PointType dDistanceCubed ;
 Point ptForce ;
 Point ptForceTemp ;

 dDistanceCubed = Distance (ptLocation, pBody->ptLocation) ;
 if (dDistanceCubed == 0.0) return ;
 dDistanceCubed = dDistanceCubed * dDistanceCubed * dDistanceCubed ;

 ptForce.dX = (pBody->ptLocation.dX - ptLocation.dX) / (dDistanceCubed) ;
 ptForce.dY = (pBody->ptLocation.dY - ptLocation.dY) / (dDistanceCubed) ;

 if (ptForce.dX < 0) ptForce.dX *= -1.0 ;
 if (ptForce.dY < 0) ptForce.dY *= -1.0 ;

 if (ptLocation.dX > pBody->ptLocation.dX)
 {
  ptForceTemp.dX = -1.0 * ptForce.dX * pBody->dMassTimesCoefficent ;
  ptNetForce.dX += ptForceTemp.dX * dMass ;
  ptVelocity.dX += ptForceTemp.dX ;

  ptForceTemp.dX = ptForce.dX * dMassTimesCoefficent ;
  pBody->ptNetForce.dX += ptForceTemp.dX * pBody->dMass ;
  pBody->ptVelocity.dX += ptForceTemp.dX ;
 } else
 {
  ptForceTemp.dX = ptForce.dX * pBody->dMassTimesCoefficent ;
  ptNetForce.dX += ptForceTemp.dX * dMass ;
  ptVelocity.dX += ptForceTemp.dX ;

  ptForceTemp.dX = -1.0 * ptForce.dX * dMassTimesCoefficent ;
  pBody->ptNetForce.dX += ptForceTemp.dX * pBody->dMass ;
  pBody->ptVelocity.dX += ptForceTemp.dX ;
 }
 if (ptLocation.dY < pBody->ptLocation.dY) 
 {
  ptForceTemp.dY = ptForce.dY * pBody->dMassTimesCoefficent ;
  ptNetForce.dY += ptForceTemp.dY * dMass ;
  ptVelocity.dY += ptForceTemp.dY ;

  ptForceTemp.dY = -1.0 * ptForce.dY * dMassTimesCoefficent ;
  pBody->ptNetForce.dY += ptForceTemp.dY * pBody->dMass ;
  pBody->ptVelocity.dY += ptForceTemp.dY ;
 } else 
 {
  ptForceTemp.dY = -1.0 * ptForce.dY * pBody->dMassTimesCoefficent ;
  ptNetForce.dY += ptForceTemp.dY * dMass ;
  ptVelocity.dY += ptForceTemp.dY ;

  ptForceTemp.dY = ptForce.dY * dMassTimesCoefficent ;
  pBody->ptNetForce.dY += ptForceTemp.dY * pBody->dMass ;
  pBody->ptVelocity.dY += ptForceTemp.dY ;
 }
}

#else // TWO_D

#endif // TWO_D

PField PFBody [] =
{
 {";", NULL, F_IGNORE},

 {"Location", BODYFM(ptLocation), F_POINT},
 {"Velocity", BODYFM(ptVelocity), F_POINT},
 {"Mass", BODYFM(dMass), F_POINTTYPE},
 {"Radius", BODYFM(ptRadius), F_POINT},

 {"Name", BODYFM(szName), F_STRING},

 {"Red", BODYFM(nRed), F_INT},
 {"Green", BODYFM(nGreen), F_INT},
 {"Blue", BODYFM(nBlue), F_INT},

 {"NameRed", BODYFM(nNameRed), F_INT},
 {"NameGreen", BODYFM(nNameGreen), F_INT},
 {"NameBlue", BODYFM(nNameBlue), F_INT},

 {NULL, NULL, F_END}
} ;