// FTPPollerDlg.h : header file
//

#if !defined(AFX_FTPPOLLERDLG_H__54639BB3_5F7F_4AF9_956E_01F357687D57__INCLUDED_)
#define AFX_FTPPOLLERDLG_H__54639BB3_5F7F_4AF9_956E_01F357687D57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFTPPollerDlg dialog

#include "HashTable.h"
#include <atlbase.h>

class CFTPPollerDlg : public CDialog
{
// Construction
public:
	void CallTimers(UINT nIDEvent) ;
	CFTPPollerDlg(CWnd* pParent = NULL);	// standard constructor
	~CFTPPollerDlg() ;

// Dialog Data
	//{{AFX_DATA(CFTPPollerDlg)
	enum { IDD = IDD_FTPPOLLER_DIALOG };
	CButton	m_cDownload;
	CEdit	m_cEncryptPublicRing;
	CEdit	m_cEncryptPrivateRing;
	CEdit	m_cEncryptPassword;
	CEdit	m_cEncryptSignID;
	CEdit	m_cEncryptUserID;
	CButton	m_cEncrypt;
	CDateTimeCtrl	m_cDailyTime;
	CEdit	m_cSiteName;
	CListCtrl	m_cFTPList;
	CEdit	m_cLocalDir;
	CEdit	m_cPassword;
	CEdit	m_cRemoteDir;
	CEdit	m_cUsername;
	CEdit	m_cWildcard;
	CEdit	m_cAddress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPPollerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL


//	CStatic	m_cHourlyStatus;
	CButton *m_pDownload ;
	CButton *m_pUpload ;
	CButton *m_pOff ;
	CButton *m_pHourly ;
	CButton *m_pDaily ;

	HashTable *m_pHashTable ;

	CRegKey *m_pRegKey ;

	void ReadReg() ;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFTPPollerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickAdd();
	afx_msg void OnClickFtpList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickDelete();
	afx_msg void OnClickOff();
	afx_msg void OnClickHourly();
	afx_msg void OnClickDaily();
	afx_msg void OnClickUpload();
	afx_msg void OnClickDownload();
	afx_msg void OnClickEncrypt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPPOLLERDLG_H__54639BB3_5F7F_4AF9_956E_01F357687D57__INCLUDED_)
