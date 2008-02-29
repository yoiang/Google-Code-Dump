// 1337 Sp34KDlg.h : header file
//

#if !defined(AFX_1337SP34KDLG_H__1BA5DD72_7F3A_4879_842E_C16540984112__INCLUDED_)
#define AFX_1337SP34KDLG_H__1BA5DD72_7F3A_4879_842E_C16540984112__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy1337Sp34KDlg dialog

class CMy1337Sp34KDlg : public CDialog
{
// Construction
public:
	CMy1337Sp34KDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy1337Sp34KDlg)
	enum { IDD = IDD_MY1337SP34K_DIALOG };
	CString	m_cstrNon1337;
	CString	m_cstr1337;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1337Sp34KDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy1337Sp34KDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGenerate();
	virtual void OnOK() ;
	virtual void OnCancel() ;
	afx_msg void OnClose() ;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1337SP34KDLG_H__1BA5DD72_7F3A_4879_842E_C16540984112__INCLUDED_)
