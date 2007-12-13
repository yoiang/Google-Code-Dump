#include "MarioDSFlipPuzzle.h"
#include "MarioDSFlipPuzzleDlg.h"


BEGIN_MESSAGE_MAP(CMarioDSFlipPuzzleApp, CWinApp)
	//{{AFX_MSG_MAP(CMarioDSFlipPuzzleApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CMarioDSFlipPuzzleApp::CMarioDSFlipPuzzleApp()
{
}

CMarioDSFlipPuzzleApp theApp;

BOOL CMarioDSFlipPuzzleApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	CMarioDSFlipPuzzleDlg dlg;
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
