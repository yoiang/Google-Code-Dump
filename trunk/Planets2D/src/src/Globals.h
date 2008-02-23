#ifndef __GLOBALS_H__
#define __GLOBALS_H__

extern HINSTANCE hCurrentInstance ;

extern HWND hMain ;
extern HWND hStat ;
extern RECT hRect ;

extern int bPaused ;

extern int bTimed ;

extern UINT uMainTimer ;

extern PointType dGCoefficent ;

extern PointType dXVelocity ;
extern PointType dXRadius ;

extern int nCalcs ;
extern int nCalcsPDisplay ;

extern int bForceDisplay ;

extern PointType dMoveSpeed ;
extern PointType dTurnSpeed ;

extern int bOnlyFirst ;
extern int nAlwaysSee ;
extern int bShowNames ;
extern int bShowNetForce ;

extern Body *pBodyHead ;
extern Body *pBodyTail ;
extern Camera *pCameraHead ;
extern Camera *pCameraTail ;
extern Camera *pCamera ;

extern char szGBuffer[256] ;
extern PField PFGlobal [] ;

#endif // __GLOBALS_H__