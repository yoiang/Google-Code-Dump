#ifndef INCLUDED_MarioDSFlipPuzzle
#define INCLUDED_MarioDSFlipPuzzle

#include "..\res\resource.h"
#include <afxwin.h>

class CMarioDSFlipPuzzleApp : public CWinApp
{
public:
	CMarioDSFlipPuzzleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarioDSFlipPuzzleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMarioDSFlipPuzzleApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif