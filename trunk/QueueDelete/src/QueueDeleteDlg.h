// QueueDeleteDlg.h : header file
//

#if !defined(AFX_QUEUEDELETEDLG_H__498AF0BF_00EB_4FDC_91EB_086BB4F23545__INCLUDED_)
#define AFX_QUEUEDELETEDLG_H__498AF0BF_00EB_4FDC_91EB_086BB4F23545__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CQueueDeleteDlg dialog

#include <vector>
#include <string>

class CQueueDeleteDlg : public CDialog
{
// Construction
public:
	CQueueDeleteDlg(char *szAppPath, bool bAutoDelete = true, bool bAutoShutdown = false, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CQueueDeleteDlg)
	enum { IDD = IDD_QUEUEDELETE_DIALOG };
	CListCtrl	m_cFileList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueueDeleteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void ShowWindow( int nCmdShow );

// Implementation
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_niData;
	CMenu m_MainMenu;
	
	bool m_bAutoDelete, m_bAutoShutdown, m_bAlwaysRun;
	char m_szAppPath[MAX_PATH+1];

	void SplitPath(char *szPath, std::string &strLocation, std::string &strFileName);

	void AddFileToList(char *szPath, bool bPrompt = true, bool bRecurseSubfolders = false);
	void RemoveFileFromList(int iSelection, int iCount);

	void ReadQueueFile();
	void WriteQueueFile();

	bool Duplicate(char *szPath);

	void DeleteFiles();
	bool DeleteFileRegardless(char *szPath);

	// Generated message map functions
	//{{AFX_MSG(CQueueDeleteDlg)
	afx_msg void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickFilelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkFilelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDropFiles(HDROP hDropped);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDownFilelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOptionsDeleteFilesNow();
	afx_msg void OnOptionsToggleAutoStart();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSystemTrayMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUEUEDELETEDLG_H__498AF0BF_00EB_4FDC_91EB_086BB4F23545__INCLUDED_)
