#include "Main.h"

Camera::Camera ()
{
#ifdef TWO_D
// ptLocation = {0.0f, 0.0f} ;
 ptLocation.dX = 0.0f ;
 ptLocation.dY = 0.0f ;

// ptVelocity = {0.0f, 0.0f} ;
 ptVelocity.dX = 0.0f ;
 ptVelocity.dY = 0.0f ;

// ptTheta = {0.0f, 0.0f} ;
 ptTheta.dX = 0.0f ;
 ptTheta.dY = 0.0f ;

// ptThetaVelocity = {0.0f, 0.0f} ;
 ptThetaVelocity.dX = 0.0f ;
 ptThetaVelocity.dY = 0.0f ;

 ptFollowDistance.dX = 0.0f ;
 ptFollowDistance.dY = 0.0f ;
#else // TWO_D
// ptLocation = {0.0f, 0.0f, 0.0f} ;
 ptLocation.dX = 0.0f ;
 ptLocation.dY = 0.0f ;
 ptLocation.dZ = 0.0f ;

// ptVelocity = {0.0f, 0.0f, 0.0f} ;
 ptVelocity.dX = 0.0f ;
 ptVelocity.dY = 0.0f ;
 ptVelocity.dZ = 0.0f ;

// ptTheta = {0.0f, 0.0f, 0.0f} ;
 ptTheta.dX = 0.0f ;
 ptTheta.dY = 0.0f ;
 ptTheta.dZ = 0.0f ;

// ptThetaVelocity = {0.0f, 0.0f, 0.0f} ;
 ptThetaVelocity.dX = 0.0f ;
 ptThetaVelocity.dY = 0.0f ;
 ptThetaVelocity.dZ = 0.0f ;

 ptFollowDistance.dX = 0.0f ;
 ptFollowDistance.dY = 0.0f ;
 ptFollowDistance.dZ = 0.0f ;
#endif // TWO_D
 dMagnification = 1.0f ;

 szName = NULL ;

 pLast = NULL ;
 pNext = NULL ;

 pFollow = NULL ;
}

Camera::~Camera ()
{
}

#ifdef TWO_D
void Camera::Display()
{
 nCalcs ++ ;
 if (nCalcs == nCalcsPDisplay) 
 {
  nCalcs = 0 ;
  InvalidateRect(hMain, NULL, 0) ;
 }
}

void Camera::ScaleToCamera (Point ptOriginal, Point &ptScale, PointType dRadius, PointType &dScale)
{
 ptScale.dX = ptOriginal.dX * dMagnification ;
 ptScale.dY = ptOriginal.dY * dMagnification ;
 dScale = dRadius * dMagnification ;
// if (!(ptScale.dX + dScale >= (PointType)(hRect.right) * -1.0 / 2.0 && ptScale.dX - dScale <= (PointType)(hRect.right) / 2.0 &&
//       ptScale.dY + dScale >= (PointType)(hRect.top) * -1.0 / 2.0 && ptScale.dY - dScale <= (PointType)(hRect.bottom) / 2.0)) dScale = 0 ;
}

#else // TWO_D

#endif // TWO_D

PField PFCamera [] =
{
 {";", NULL, F_IGNORE},

 {"Location", CAMFM(ptLocation), F_POINT},
 {"Velocity", CAMFM(ptVelocity), F_POINT},
 {"Magnification", CAMFM(dMagnification), F_POINTTYPE},

 {"Name", CAMFM(szName), F_STRING},

 {NULL, NULL, F_END}
} ;