#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera
{
public:
 Point ptLocation ;
 Point ptVelocity ;

 Point ptTheta ;
 Point ptThetaVelocity ;

 PointType dMagnification ;

 char *szName ;

 Body *pFollow ;
 Point ptFollowDistance ;

 Camera () ;
 ~Camera () ;

 Camera *pLast ;
 Camera *pNext ;

 void Display () ;
 void ScaleToCamera (Point ptOriginal, Point &ptScale, PointType dRadius, PointType &dScale) ;
} ;

#define CAMFM(x) (void *)&(((Camera *)0)->x)

extern PField PFCamera [] ;
#endif // __CAMERA_H__