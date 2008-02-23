#include "Main.h"

int InitWC ()
{
#ifndef OLD
 WNDCLASSEX WndClass;

 WndClass.cbSize        = sizeof(WndClass);
 WndClass.style         = CS_HREDRAW | CS_VREDRAW;
 WndClass.lpfnWndProc   = StatProc;
 WndClass.cbClsExtra    = 0;
 WndClass.cbWndExtra    = 0;
 WndClass.hInstance     = hCurrentInstance;
 WndClass.hIcon         = NULL ;
 WndClass.hCursor       = LoadCursor(NULL,IDC_ARROW);
 WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
 WndClass.lpszMenuName  = NULL ;
 WndClass.hIconSm       = NULL ;
 WndClass.lpszClassName = "PStat" ;
 if (!RegisterClassEx(&WndClass)) return 0 ;

 WndClass.cbSize        = sizeof(WndClass);
 WndClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;
 WndClass.lpfnWndProc   = MainProc;
 WndClass.cbClsExtra    = 0;
 WndClass.cbWndExtra    = 0;
 WndClass.hInstance     = hCurrentInstance;
 WndClass.hIcon         = LoadIcon(hCurrentInstance, MAKEINTRESOURCE(IDI_MAIN));
 WndClass.hCursor       = LoadCursor(NULL,IDC_ARROW);
 WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
 WndClass.lpszMenuName  = MAKEINTRESOURCE(IDM_MAIN) ;
 WndClass.lpszClassName = "PMain" ;
 WndClass.hIconSm       = LoadIcon(hCurrentInstance, MAKEINTRESOURCE(IDI_MAIN));
 return (RegisterClassEx(&WndClass)) ;
#else // OLD
 WNDCLASS WndClass;

 WndClass.style         = CS_HREDRAW | CS_VREDRAW;
 WndClass.lpfnWndProc   = StatProc;
 WndClass.cbClsExtra    = 0;
 WndClass.cbWndExtra    = 0;
 WndClass.hInstance     = hCurrentInstance;
 WndClass.hIcon         = NULL ;
 WndClass.hCursor       = LoadCursor(NULL,IDC_ARROW);
 WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
 WndClass.lpszMenuName  = NULL ;
 WndClass.lpszClassName = "PStat" ;
 if (!RegisterClass(&WndClass)) return 0 ;

 WndClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;
 WndClass.lpfnWndProc   = MainProc;
 WndClass.cbClsExtra    = 0;
 WndClass.cbWndExtra    = 0;
 WndClass.hInstance     = hCurrentInstance;
 WndClass.hIcon         = LoadIcon(hCurrentInstance, MAKEINTRESOURCE(IDI_MAIN));
 WndClass.hCursor       = LoadCursor(NULL,IDC_ARROW);
 WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
 WndClass.lpszMenuName  = MAKEINTRESOURCE(IDM_MAIN) ;
 WndClass.lpszClassName = "PMain" ;
 return (RegisterClass(&WndClass)) ;
#endif // OLD
}

int InitWindow(int nCmdShow)
{
 hRect.left = 0 ;
 hRect.top = 0 ;
 hRect.right = GetSystemMetrics(SM_CXMAXIMIZED) ;
 hRect.bottom = GetSystemMetrics(SM_CYMAXIMIZED) ;
 if (!(hMain = CreateWindowEx(0,
                              "PMain",
                              "Planets2D",
                              WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN,
                              0,
                              0,
                              hRect.right,
                              hRect.bottom,
                              NULL,
                              NULL,
                              hCurrentInstance,
                              NULL))) return 0 ;
    
 ShowWindow(hMain, nCmdShow) ;
 if (!UpdateWindow(hMain)) return 0 ;

 if (!(hStat = CreateWindowEx(0,
                              "PStat",
             				  "",
							  WS_CHILD | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
                              hRect.right * 0.6,
                              hRect.bottom * 0.6,
                              hRect.right * 0.2,
                              291,
							  hMain,
							  NULL,
							  hCurrentInstance,
							  NULL))) return 0 ;
 ShowWindow(hStat, nCmdShow) ;
 return (UpdateWindow(hStat)) ;
}

int InitData (char *szFileName)
{
 FILE *pFile ;
 if ((pFile = fopen (szFileName, "rt")) == NULL)
 {
  UnFatalError ("cannot open file for reading") ;
  return 0 ;
 }
 DeallAll () ;
 if (!ReadFields(pFile, PFGlobal, NULL)) return 0 ;
 fclose(pFile) ;
 if (pCameraHead == NULL) 
 {
  pCameraTail = pCameraHead = new Camera ;
  pCameraHead->szName = new char [strlen ("Camera1") + 1] ;
  strcpy(pCameraHead->szName, "Camera1") ;
 }
 pCamera = pCameraHead ;

 PointType dScaled ;
 Point ptDifference ;
 Body *pBody ;
 pBody = pBodyHead ;
 while (pBody != NULL)
 {
  pBody->dMassTimesCoefficent = pBody->dMass * dGCoefficent ;
  ptDifference.dX = pBody->ptLocation.dX - pCamera->ptLocation.dX ;
  ptDifference.dY = pBody->ptLocation.dY - pCamera->ptLocation.dY ;
  pCamera->ScaleToCamera (ptDifference, pBody->ptOldLocation, pBody->ptRadius.dX, dScaled) ;

  pBody = pBody->pNext ;
 }

 SetStatTitle () ;
 InvalidateRect(hStat, NULL, 1) ;
 return 1 ;
}

int InitInst (int nCmdShow, LPSTR lpCmdLine)
{
 if (!InitWindow (nCmdShow)) return 0 ;
 char *szFileName = NULL ;

 if (strcmp(lpCmdLine, "") != 0)
 {
  int nTrav = 0, nTravB ;
  while (nTrav < strlen (lpCmdLine))
  {
   while (lpCmdLine[nTrav] == ' ') nTrav ++ ;
   if (lpCmdLine[nTrav] == '-')
   {
  	nTrav ++ ;
	switch (lpCmdLine[nTrav])
	{
     case 's':
	 case 'S':
	 if (szFileName != NULL) break ;
	 nTrav ++ ;
	 nTravB = 0 ;
	 while (lpCmdLine[nTrav] != '\0' && lpCmdLine[nTrav] != ' ' && lpCmdLine[nTrav] != '\n')
	 {
	  szGBuffer[nTravB] = lpCmdLine[nTrav] ;
	  nTravB ++ ;
	  nTrav ++ ;
	 }
	 szGBuffer[nTravB] = '\0' ;
	 szFileName = new char [strlen(szGBuffer) + 1] ;
	 strcpy (szFileName, szGBuffer) ;
	break ;
    case 't':
	case 'T':
	 nTrav ++ ;
	 bTimed = 1 ;
	break ;
	default: UnFatalError("Unknown switch") ; break ;
	}
   } else 
   {
	UnFatalError("Unknown paramater") ;
	break ;
   }
  }
 }

 if (szFileName == NULL)
 {
  szFileName = new char [strlen("default.pla") + 1] ;
  strcpy(szFileName, "default.pla") ;
 }

 InitData(szFileName) ;
 delete [] szFileName ;

 if (bTimed) if (!(uMainTimer = SetTimer (hMain, 0, 1, (TIMERPROC)CalcTimer))) FatalError("InitInst - SetTimer failed") ;

 return 1 ;
}


void DeallAll ()
{
 while (pBodyHead != NULL)
 {
  pBodyTail = pBodyHead->pNext ;
  delete pBodyHead ;
  pBodyHead = pBodyTail ;
 }
 while (pCameraHead != NULL)
 {
  pCameraTail = pCameraHead->pNext ;
  delete pCameraHead ;
  pCameraHead = pCameraTail ;
 }
}

void CloseInst ()
{
 if (hCurrentInstance == 0) return ;
 hCurrentInstance = 0 ;

 if (uMainTimer != 0) KillTimer(hMain, uMainTimer) ;
 DeallAll () ;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
 //LPTSTR GetCommandLine () ;

 MSG uMsg ;

 hCurrentInstance = hInstance ;

 if (!hPrevInstance) if (!InitWC()) FatalError("WinMain - InitWC failed") ;

 if (!InitInst(nCmdShow, lpCmdLine)) FatalError("WinMain - InitInst failed") ;

 while (1)
 {
  if (PeekMessage(&uMsg, NULL, 0, 0, PM_NOREMOVE))
  {
   GetMessage(&uMsg, NULL, 0,0) ;
   TranslateMessage(&uMsg) ;
   DispatchMessage(&uMsg) ;
   if (uMsg.message == WM_QUIT) 
   {
    CloseInst () ;
    return uMsg.wParam ;
   }
  } else if (!bTimed && !bPaused) CalcTimer(hMain, 0, 0, 0) ;
 }
 CloseInst () ;
 return uMsg.wParam ;
}

void FatalError (char *szError)
{
 MessageBox (NULL, szError, "Fatal Error!", MB_OK | MB_ICONERROR) ;

 CloseInst () ;

 exit(-1) ;
}

void UnFatalError (char *szError)
{
 MessageBox (NULL, szError, "Error!", MB_OK | MB_ICONERROR) ;
}
