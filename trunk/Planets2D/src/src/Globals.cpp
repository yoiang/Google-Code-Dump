#include "Main.h"

HINSTANCE hCurrentInstance = 0 ;

HWND hMain = 0 ;
HWND hStat = 0 ;
RECT hRect = {0, 0, 0, 0} ;

int bPaused = 0 ;

int bTimed = 0 ;

UINT uMainTimer = 0 ;

PointType dGCoefficent = G ;

PointType dXVelocity = 1.0f ;
PointType dXRadius = 1.0f ;

int nCalcs = 0;
int nCalcsPDisplay = 1 ;

int bForceDisplay = 1 ;

int bOnlyFirst = 0 ;
int nAlwaysSee = 0 ;
int bShowNames = 1 ;
int bShowNetForce = 1 ; 

Body *pBodyHead = NULL ;
Body *pBodyTail = NULL ;
Camera *pCameraHead = NULL ;
Camera *pCameraTail = NULL ;
Camera *pCamera = NULL ;

char szGBuffer [256] ;

PField PFGlobal [] =
{
 {";", NULL, F_IGNORE},

 {"GCoefficent", GFM(dGCoefficent), F_POINTTYPE},

 {"XVelocity", GFM(dXVelocity), F_POINTTYPE},
 {"XRadius", GFM(dXRadius), F_POINTTYPE},

 {"OnlyFirst", GFM(bOnlyFirst), F_INT},
 {"AlwaysSee", GFM(nAlwaysSee), F_INT},
 {"ShowNames", GFM(bShowNames), F_INT},
 {"ShowNetForce", GFM(bShowNetForce), F_INT},

 {NULL, NULL, F_END}
} ;