#ifndef INCLUDED_MarioDSFlipPuzzleDlg
#define INCLUDED_MarioDSFlipPuzzleDlg

#include <afxwin.h>
#include "MarioDSFlipPuzzleBoard.h"
#include <vector>

class CMarioDSFlipPuzzleDlg : public CDialog
{
// Construction
public:
	CMarioDSFlipPuzzleDlg(CWnd* pParent = NULL);	// standard constructor
	~CMarioDSFlipPuzzleDlg();

// Dialog Data
	//{{AFX_DATA(CMarioDSFlipPuzzleDlg)
	enum { IDD = IDD_MARIODSFLIPPUZZLE_DIALOG };
	CStatic	m_csStepsCount;
	CButton	m_cgMatchingArea;
	CButton	m_ccLinkDimensions;
	CButton	m_cgWorkingArea;
	CButton	m_cgBeforeArea;
	CButton	m_cgAfterArea;
	CEdit	m_ceWidthValue;
	CEdit	m_ceHeightValue;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarioDSFlipPuzzleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	enum 
	{
		IMAGE_WIDTH = 15,
		IMAGE_HEIGHT = 15,
		IMAGE_LEFT_SPACING = 5,
		IMAGE_TOP_SPACING = 15,
		IMAGE_WIDTH_SPACING = 5,
		IMAGE_HEIGHT_SPACING = 5,
	};

// Implementation
protected:
	HICON m_hIcon;
	MarioDSFlipPuzzleBoard *m_pBefore, *m_pAfter, *m_pWorking;
	WINDOWPLACEMENT m_BeforePlacement, m_AfterPlacement, m_WorkingPlacement;
	bool m_bChanging;
	std::vector<CPoint> m_vSteps;

	// Generated message map functions
	//{{AFX_MSG(CMarioDSFlipPuzzleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeWidthValue();
	afx_msg void OnChangeHeightValue();
	afx_msg void OnClickLinkDimensions();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickSetToBefore();
	afx_msg void OnClickUndo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnOK();

	void UpdateBoardSizes();
	void UpdateDialogSize();
	void UpdateMatchingStatus();
	void UpdateStepsCount();

	void DisplayBoards();
	void DisplayBoard( MarioDSFlipPuzzleBoard *pDisplay, int iX, int iY );
	void DisplaySpace( int iX, int iY, int iSpaceX, int iSpaceY, bool bFacing );
	void DisplaySpace( int iX, int iY, bool bFacing );

	bool IsWithin( WINDOWPLACEMENT *pArea, CPoint *pPoint );
	bool FindSpace( WINDOWPLACEMENT *pArea, CPoint *pPoint, int &iXSpace, int &iYSpace );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
