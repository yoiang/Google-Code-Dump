// QueueDelete.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "QueueDelete.h"
#include "QueueDeleteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueueDeleteApp

BEGIN_MESSAGE_MAP(CQueueDeleteApp, CWinApp)
//{{AFX_MSG_MAP(CQueueDeleteApp)
//}}AFX_MSG
ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueueDeleteApp construction

CQueueDeleteApp::CQueueDeleteApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CQueueDeleteApp object

CQueueDeleteApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CQueueDeleteApp initialization

BOOL CQueueDeleteApp::InitInstance()
{
	// Standard initialization
	
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	bool bAutoDelete = false, bAutoShutdown = false;
	std::string strAppPath(__targv[0]);

	for (int i = 1; i < __argc; i++)
	{
		LPCTSTR pszParam = __targv[i];
		if (stricmp(pszParam, "delete") == 0)
		{
			bAutoDelete = true;
		} else if (stricmp(pszParam, "queue") == 0)
		{
			bAutoDelete = false;
		} else if (stricmp(pszParam, "autoshutdown") == 0)
		{
			bAutoShutdown = true;
		} else
		{
		}
	}
	
	CQueueDeleteDlg dlg((char*)strAppPath.c_str(), bAutoDelete, bAutoShutdown);
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
