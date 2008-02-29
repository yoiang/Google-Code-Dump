// FTPPoller.h : main header file for the FTPPOLLER application
//

#if !defined(AFX_FTPPOLLER_H__973A05E2_8EDA_49FC_9A56_36EC6E68F59C__INCLUDED_)
#define AFX_FTPPOLLER_H__973A05E2_8EDA_49FC_9A56_36EC6E68F59C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFTPPollerApp:
// See FTPPoller.cpp for the implementation of this class
//

class CFTPPollerApp : public CWinApp
{
public:
	CFTPPollerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPPollerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFTPPollerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPPOLLER_H__973A05E2_8EDA_49FC_9A56_36EC6E68F59C__INCLUDED_)
