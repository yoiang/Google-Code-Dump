#include "Main.h"

LRESULT CALLBACK MainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
 switch (uMsg)
 {
 case WM_ACTIVATE:
  if (LOWORD(wParam) != WA_ACTIVE && LOWORD(wParam) != WA_CLICKACTIVE) break ;
  PostMessage(hMain, WM_PAINT, 0, 0) ;
  PostMessage(hStat, WM_PAINT, 0, 0) ;
 return 0 ;
 case WM_KEYDOWN:
  int nVirtKey ;
  nVirtKey = (int) wParam ;
  switch (nVirtKey)
  {
  case 'B':
  case 'b':
   if (pCamera->pFollow == NULL) pCamera->pFollow = pBodyHead ;
   else pCamera->pFollow = pCamera->pFollow->pNext ;
   if (pCamera->pFollow == NULL) InvalidateRect(hStat, NULL, 1) ;

   bForceDisplay = 1 ;
   SetStatTitle () ;
   InvalidateRect(hWnd, NULL, 1) ;
  return 0 ;
  case 'C':
  case 'c':
   if (pCamera->pNext != NULL) pCamera = pCamera->pNext ;
   else pCamera = pCameraHead ;
   InvalidateRect(hStat, NULL, 1) ;
   bForceDisplay = 1 ;
   SetStatTitle () ;
   InvalidateRect(hWnd, NULL, 1) ;
  return 0 ;
  case 'R':
  case 'r':
   bForceDisplay = 1 ;
   InvalidateRect(hWnd, NULL, 1) ;
  return 0 ;
  case 'P':
  case 'p':
   if (bPaused == 0) bPaused = 1 ;
   else bPaused = 0 ;
  return 0 ;
  case 'T':
  case 't':
   if (bTimed == 0)
   {
	bTimed = 1 ;
	uMainTimer =  SetTimer (hWnd, 0, 1, (TIMERPROC)CalcTimer) ;
   } else
   {
	bTimed = 0 ;
	KillTimer (hWnd, uMainTimer) ;
	uMainTimer = 0 ;
   }
  return 0 ;
  case 'N':
  case 'n':
   if (bShowNames == 0) bShowNames = 1 ;
   else bShowNames = 0 ; 
   InvalidateRect(hWnd, NULL, 1) ;
  return 0 ;
  case 'F':
  case 'f':
   if (bShowNetForce == 0) bShowNetForce = 1 ;
   else bShowNetForce = 0 ; 
   InvalidateRect(hWnd, NULL, 1) ;
  return 0 ;
  case 187:
  case 107:
   pCamera->dMagnification *= 2.0 ;
   bForceDisplay = 1 ;
   InvalidateRect(hWnd, NULL, 1) ;
  return 0 ;
  case 189:
  case 109:
   pCamera->dMagnification /= 2.0 ;
   bForceDisplay = 1 ;
   InvalidateRect(hWnd, NULL, 1) ;
  return 0 ;
  default:
//   nAlwaysSee = nAlwaysSee ;
  break ;
  }
 break ;
 case WM_COMMAND:
  if (HIWORD(wParam) == 0)
  {
   switch (LOWORD(wParam))
   {
   case ID_FILE_OPEN_SCRIPT:
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_OPEN), hWnd, (DLGPROC)OpenDlgProc) ;
   break ;
   case ID_FILE_EXIT:
	PostMessage (hWnd, WM_CLOSE, NULL, NULL);
   break ;
   case ID_HELP_ABOUT:
    DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_ABOUT), hWnd, (DLGPROC)AboutDlgProc) ;
   break ;
   }
  }
 return 0;
 case WM_PAINT:
  HDC hDC ;
  PAINTSTRUCT lpPaint ;

  if ((hDC = BeginPaint(hWnd, &lpPaint)) == NULL) FatalError ("MainProc - BeginPaint failed with hWnd") ;
  SetBkMode(hDC, TRANSPARENT);
  Body *pBody ;
  pBody = pBodyHead ;
  InvalidateRect(hStat, NULL, 0) ;

  LOGBRUSH hLogBrush ;
  LOGPEN hLogPen ;
  HBRUSH hBrush, hClearBrush ;
  HPEN hPen, hClearPen ;
  HGDIOBJ hOldBrush, hOldPen ;
  hLogBrush.lbStyle = BS_HOLLOW ;

  hLogPen.lopnColor = RGB(0,0,0) ;
  hLogPen.lopnStyle = PS_SOLID ;
  hLogPen.lopnWidth.x = 1 ;
  hClearPen = CreatePenIndirect(&hLogPen);

  hLogBrush.lbColor = RGB(0,0,0) ;
  hClearBrush = CreateBrushIndirect(&hLogBrush) ;

  while (pBody != NULL)
  {
   Point ptDifference, ptScaled, ptScaledForce ;
   PointType dScaled ;
   double dForceAngle ;

   if (pCamera->pFollow == NULL)
   {
    ptDifference.dX = pBody->ptLocation.dX - pCamera->ptLocation.dX ;
    ptDifference.dY = pBody->ptLocation.dY - pCamera->ptLocation.dY ;
   } else
   {
    ptDifference.dX = pBody->ptLocation.dX - pCamera->pFollow->ptLocation.dX + pCamera->ptFollowDistance.dX ;
    ptDifference.dY = pBody->ptLocation.dY - pCamera->pFollow->ptLocation.dY + pCamera->ptFollowDistance.dY ;
   }
   pCamera->ScaleToCamera (ptDifference, ptScaled, pBody->ptRadius.dX, dScaled) ;

   dForceAngle = sqrt(pBody->ptNetForce.dX * pBody->ptNetForce.dX + pBody->ptNetForce.dY * pBody->ptNetForce.dY) ;
   ptScaledForce.dX = 15.0 * pBody->ptNetForce.dX / dForceAngle ;
   ptScaledForce.dY = 15.0 * pBody->ptNetForce.dY / dForceAngle ;

   if (dScaled < 1.0) dScaled = (PointType)(nAlwaysSee) ;
   if (!bForceDisplay && pCamera->pFollow != pBody || (int)(ptScaledForce.dX) != (int)(pBody->ptOldNetForce.dX) || (int)(ptScaledForce.dY) != (int)(pBody->ptOldNetForce.dY))
   {
    if ((int)(dScaled) >= 1)
	{
	 if (pCamera->pFollow != pBody || ((int)(ptScaled.dX) != (int)(pBody->ptOldLocation.dX) || (int)(ptScaled.dY) != (int)(pBody->ptOldLocation.dY)))
     {
	  DisplayBody(hDC, pBody->ptOldLocation, pBody->ptOldNetForce, dScaled, hClearBrush, hClearPen, pBody->szName, RGB(0,0,0)) ;
     } else if (bShowNetForce && ((int)(ptScaledForce.dX) != (int)(pBody->ptOldNetForce.dX) || (int)(ptScaledForce.dY) != (int)(pBody->ptOldNetForce.dY)))
	 {
      hOldPen = SelectObject (hDC, (HGDIOBJ)hClearPen);

      SetTextColor(hDC, RGB(0,0,0)) ;

	  MoveToEx(hDC,(int)(pBody->ptOldLocation.dX) + int((PointType)(hRect.right) / 2.0),
 	               (int)(pBody->ptOldLocation.dY) + int((PointType)(hRect.bottom) / 2.0), NULL) ; 

	  LineTo (hDC, (int)(pBody->ptOldLocation.dX) + (int)(pBody->ptOldNetForce.dX) + int((PointType)(hRect.right) / 2.0), 
	               (int)(pBody->ptOldLocation.dY) + (int)(pBody->ptOldNetForce.dY) + int((PointType)(hRect.bottom) / 2.0)) ;

	  SelectObject(hDC, hOldPen) ;
	 }
	}
   }
   if ((int)(dScaled) >= 1) 
   {
    hLogPen.lopnColor = RGB(pBody->nRed,pBody->nGreen,pBody->nBlue) ;
    hPen = CreatePenIndirect(&hLogPen);

    hLogBrush.lbColor = RGB(pBody->nRed,pBody->nGreen,pBody->nBlue) ;
    hBrush = CreateBrushIndirect(&hLogBrush) ;

	DisplayBody(hDC, ptScaled, ptScaledForce, dScaled, hBrush, hPen, pBody->szName, RGB(pBody->nNameRed,pBody->nNameGreen,pBody->nNameBlue)) ;

	DeleteObject((HGDIOBJ)hBrush) ;
	DeleteObject((HGDIOBJ)hPen) ;
   }
   pBody->ptOldLocation.dX = ptScaled.dX ;
   pBody->ptOldLocation.dY = ptScaled.dY ;

   pBody->ptOldNetForce.dX = ptScaledForce.dX ;
   pBody->ptOldNetForce.dY = ptScaledForce.dY ;
   pBody = pBody->pNext ;
  }
  DeleteObject((HGDIOBJ)hClearBrush) ;
  DeleteObject((HGDIOBJ)hClearPen) ;

  EndPaint(hWnd, &lpPaint) ;
  bForceDisplay = 0 ;
 return 0 ;
 case WM_CLOSE:
  DestroyWindow(hWnd) ;
 return 0 ;
 case WM_DESTROY:
  PostQuitMessage(0) ;
 return 0 ;
 }
 return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


void DisplayBody (HDC hDC, Point ptLocation, Point ptNetForce, PointType dRadius, HBRUSH hBrush, HPEN hPen, char *szName, COLORREF dwTextColor)
{
 HGDIOBJ hOldBrush, hOldPen ;

 hOldPen = SelectObject (hDC, (HGDIOBJ)hPen);

 hOldBrush = SelectObject (hDC, (HGDIOBJ)hBrush);

 SetTextColor(hDC, dwTextColor) ;


/* if ((int)(ptLocation.dX) - int(dRadius) > 0 ||
     (int)(ptLocation.dX) + int(dRadius) < int((PointType)(hRect.right)) ||
	 (int)(ptLocation.dY) - int(dRadius) > 0 ||
	 (int)(ptLocation.dY) + int(dRadius) < int((PointType)(hRect.bottom)))
*/  Ellipse(hDC, (int)(ptLocation.dX) - int(dRadius) + int((PointType)(hRect.right) / 2.0),  
	           (int)(ptLocation.dY) - int(dRadius) + int((PointType)(hRect.bottom) / 2.0), 
			   (int)(ptLocation.dX) + int(dRadius) + int((PointType)(hRect.right) / 2.0),  
			   (int)(ptLocation.dY) + int(dRadius) + int((PointType)(hRect.bottom) / 2.0)) ; //) FatalError("WTF?") ;

/* if ((((int)(ptLocation.dX) > 0 &&
       (int)(ptLocation.dX) < int((PointType)(hRect.right)) &&
	   (int)(ptLocation.dY) > 0 &&
	   (int)(ptLocation.dY) < int((PointType)(hRect.bottom))) ||
	  ((int)(ptLocation.dX) + (int)(ptNetForce.dX) > 0 &&
	   (int)(ptLocation.dX) + (int)(ptNetForce.dX) < int((PointType)(hRect.right)) &&
	   (int)(ptLocation.dY) + (int)(ptNetForce.dY) > 0 &&
	   (int)(ptLocation.dY) + (int)(ptNetForce.dY) < int((PointType)(hRect.bottom)))) && bShowNetForce)
*/
 if (bShowNetForce)
{
  MoveToEx(hDC,(int)(ptLocation.dX) + int((PointType)(hRect.right) / 2.0),
 	           (int)(ptLocation.dY) + int((PointType)(hRect.bottom) / 2.0), NULL) ; 

  LineTo (hDC, (int)(ptLocation.dX) + (int)(ptNetForce.dX) + int((PointType)(hRect.right) / 2.0), 
	           (int)(ptLocation.dY) + (int)(ptNetForce.dY) + int((PointType)(hRect.bottom) / 2.0)) ;
 }

 if (bShowNames) TextOut(hDC, (int)(ptLocation.dX) + int((PointType)(hRect.right) / 2.0), 
	                          (int)(ptLocation.dY) + int((PointType)(hRect.bottom) / 2.0), szName, strlen(szName)) ;


 SelectObject(hDC, hOldPen) ;

 SelectObject(hDC, hOldBrush) ;
}

LRESULT CALLBACK StatProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
 switch (uMsg)
 {
 case WM_PAINT:
  HDC hDC ;
  PAINTSTRUCT lpPaint ;

  if ((hDC = BeginPaint(hWnd, &lpPaint)) == NULL) FatalError ("StatProc - BeginPaint failed with hWnd") ;

  if (pCamera != NULL)
  {
   RECT hRectStat ;
   GetClientRect (hWnd, &hRectStat) ;
   SetTextColor(hDC, RGB(0,0,0)) ;
   if (pCamera->pFollow != NULL)
   {
    sprintf (szGBuffer, "Magnification: %le X   ", pCamera->dMagnification) ;
    ExtTextOut(hDC, 1, 1, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;

    ExtTextOut(hDC, 1, 21, ETO_CLIPPED, &hRectStat, "Location:", strlen("Location:"), NULL) ;
    sprintf (szGBuffer, "X: %le m   ", pCamera->pFollow->ptLocation.dX) ;
    ExtTextOut(hDC, 5, 41, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;
    sprintf (szGBuffer, "Y: %le m   ", pCamera->pFollow->ptLocation.dY) ;
    ExtTextOut(hDC, 5, 61, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;

    ExtTextOut(hDC, 1, 81, ETO_CLIPPED, &hRectStat, "Velocity:", strlen("Velocity:"), NULL) ;
    sprintf (szGBuffer, "X: %le m/s   ", pCamera->pFollow->ptVelocity.dX) ;
    ExtTextOut(hDC, 5, 101, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;
    sprintf (szGBuffer, "Y: %le m/s   ", pCamera->pFollow->ptVelocity.dY) ;
    ExtTextOut(hDC, 5, 121, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;

    sprintf (szGBuffer, "Mass: %le kg  ", pCamera->pFollow->dMass) ;
    ExtTextOut(hDC, 1, 141, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;
    sprintf (szGBuffer, "Radius: %le m  ", pCamera->pFollow->ptRadius.dX) ;
    ExtTextOut(hDC, 1, 161, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;

	ExtTextOut(hDC, 1, 181, ETO_CLIPPED, &hRectStat, "Net Force:", strlen("Net Force:"), NULL) ;
    sprintf (szGBuffer, "X: %le N   ", pCamera->pFollow->ptNetForce.dX) ;
    ExtTextOut(hDC, 5, 201, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;
    sprintf (szGBuffer, "Y: %le N   ", pCamera->pFollow->ptNetForce.dY) ;
    ExtTextOut(hDC, 5, 221, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;

	sprintf (szGBuffer, "Kinetic Energy: %le J    ", pCamera->pFollow->dKineticEnergy) ;
	ExtTextOut(hDC, 1, 241, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;
   } else
   {
    sprintf (szGBuffer, "Magnification: %le X   ", pCamera->dMagnification) ;
    ExtTextOut(hDC, 1, 1, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;

    ExtTextOut(hDC, 1, 21, ETO_CLIPPED, &hRectStat, "Location:", strlen("Location:"), NULL) ;
    sprintf (szGBuffer, "X: %le m   ", pCamera->ptLocation.dX) ;
    ExtTextOut(hDC, 5, 41, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;
    sprintf (szGBuffer, "Y: %le m   ", pCamera->ptLocation.dY) ;
    ExtTextOut(hDC, 5, 61, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;

    ExtTextOut(hDC, 1, 81, ETO_CLIPPED, &hRectStat, "Velocity:", strlen("Velocity:"), NULL) ;
    sprintf (szGBuffer, "X: %le m/s   ", pCamera->ptVelocity.dX) ;
    ExtTextOut(hDC, 5, 101, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;
    sprintf (szGBuffer, "Y: %le m/s   ", pCamera->ptVelocity.dY) ;
    ExtTextOut(hDC, 5, 121, ETO_CLIPPED, &hRectStat, szGBuffer, strlen(szGBuffer), NULL) ;
   }
  }
  EndPaint(hWnd, &lpPaint) ;
 return 0 ;
 }
 return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void SetStatTitle ()
{
 if (pCamera != NULL)
 {
  if (pCamera->pFollow != NULL)
  {
   sprintf (szGBuffer, "%s -> %s", pCamera->szName, pCamera->pFollow->szName) ;
   SetWindowText(hStat, szGBuffer) ;
  } else
  {
   SetWindowText(hStat, pCamera->szName) ;
  }
 } else SetWindowText(hStat, "") ;
}

void CALLBACK DisplayTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
 pCamera->Display();
}

void CALLBACK CalcTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
 if (bPaused) return ;
 Body *pBody, *pBody2 ;
 pBody = pBodyHead ;

 while (pBody != NULL)
 {
  pBody->ptNetForce.dX = 0.0f ;
  pBody->ptNetForce.dY = 0.0f ;
  pBody = pBody->pNext ;
 }
 pBody = pBodyHead ;
 if (bOnlyFirst && pBody != NULL)
 {
  pBody2 = pBody->pNext ;

  while (pBody2 != NULL)
  {
   pBody->Recalc(pBody2) ;
   pBody2->ptLocation.dX += pBody2->ptVelocity.dX * dXVelocity ;
   pBody2->ptLocation.dY += pBody2->ptVelocity.dY * dXVelocity ;
   pBody2->dKineticEnergy = 0.5 * pBody2->dMass * pBody2->ptVelocity.dX * pBody2->ptVelocity.dX * pBody2->ptVelocity.dY * pBody2->ptVelocity.dY ;
   pBody2 = pBody2->pNext ;
  }
  pBody->dKineticEnergy = 0.5 * pBody->dMass * pBody->ptVelocity.dX * pBody->ptVelocity.dX * pBody->ptVelocity.dY * pBody->ptVelocity.dY ;
 } else
 {
  while (pBody != NULL)
  {
   pBody2 = pBody->pNext ;
   while (pBody2 != NULL)
   {
    pBody->Recalc(pBody2) ;
    pBody2 = pBody2->pNext ;
   }
   pBody->ptLocation.dX += pBody->ptVelocity.dX * dXVelocity ;
   pBody->ptLocation.dY += pBody->ptVelocity.dY * dXVelocity ;
   pBody->dKineticEnergy = 0.5 * pBody->dMass * pBody->ptVelocity.dX * pBody->ptVelocity.dX * pBody->ptVelocity.dY * pBody->ptVelocity.dY ;
   pBody = pBody->pNext ;
  }
 }
 pCamera->Display();
}

LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
 switch(uMsg) 
 {
 case WM_INITDIALOG:
 return 1 ;

 case WM_COMMAND:
  switch (LOWORD(wParam)) 
  {
  case IDOK: 
   EndDialog(hWnd, 1);
  return 0 ;
  }
  break;
 }
 return 0 ;
}

LRESULT CALLBACK OpenDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
 switch(uMsg) 
 {
 case WM_INITDIALOG:
 return 1 ;

 case WM_COMMAND:
  switch (LOWORD(wParam)) 
  {
  case ID_CANCEL: 
   EndDialog(hWnd, 1);
  return 0 ;
  case ID_OK:
   GetDlgItemText(hWnd, IDE_PATH, szGBuffer, 255) ;
   if (InitData(szGBuffer))
   {
    InvalidateRect(hMain, NULL, 1) ;
    InvalidateRect(hStat, NULL, 1) ;
    EndDialog(hWnd, 1) ;
   }
  return 0 ;
  }
  break;
 }
 return 0 ;
}
