// QueueDelete.h : main header file for the QUEUEDELETE application
//

#if !defined(AFX_QUEUEDELETE_H__8BA26AF1_4382_41D7_A3FB_3199B25DCE3E__INCLUDED_)
#define AFX_QUEUEDELETE_H__8BA26AF1_4382_41D7_A3FB_3199B25DCE3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "../resource/resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQueueDeleteApp:
// See QueueDelete.cpp for the implementation of this class
//

class CQueueDeleteApp : public CWinApp
{
public:
	CQueueDeleteApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueueDeleteApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQueueDeleteApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUEUEDELETE_H__8BA26AF1_4382_41D7_A3FB_3199B25DCE3E__INCLUDED_)
