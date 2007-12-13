// QueueDeleteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QueueDelete.h"
#include "QueueDeleteDlg.h"

#include <atlbase.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueueDeleteDlg dialog

CQueueDeleteDlg::CQueueDeleteDlg(char *szAppPath, bool bAutoDelete, bool bAutoShutdown, CWnd* pParent /*=NULL*/)
: CDialog(CQueueDeleteDlg::IDD, pParent), m_bAutoDelete(bAutoDelete), m_bAutoShutdown(bAutoShutdown)
{
	//{{AFX_DATA_INIT(CQueueDeleteDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	strcpy(m_szAppPath, szAppPath);
}

void CQueueDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueueDeleteDlg)
	DDX_Control(pDX, IDC_FILELIST, m_cFileList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQueueDeleteDlg, CDialog)
//{{AFX_MSG_MAP(CQueueDeleteDlg)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_NOTIFY(NM_CLICK, IDC_FILELIST, OnClickFilelist)
ON_NOTIFY(NM_DBLCLK, IDC_FILELIST, OnDblclkFilelist)
ON_WM_SIZE()
ON_WM_DROPFILES()
ON_WM_DESTROY()
ON_NOTIFY(LVN_KEYDOWN, IDC_FILELIST, OnKeyDownFilelist)
ON_COMMAND(ID_OPTIONS_DELETEFILESNOW, OnOptionsDeleteFilesNow)
ON_WM_SYSCOMMAND()
ON_COMMAND(ID_OPTIONS_TOGGLEAUTOSTART, OnOptionsToggleAutoStart)
ON_MESSAGE(IDM_SYSTEMTRAYMESSAGE, OnSystemTrayMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueueDeleteDlg message handlers

BOOL CQueueDeleteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon	
	
	ReadQueueFile();	
	
	if (m_bAutoShutdown)
	{
		SendMessage(WM_CLOSE, 0, 0);
	}

	m_MainMenu.LoadMenu( IDR_MAINMENU );

	m_niData.cbSize = sizeof( NOTIFYICONDATA );
    m_niData.hIcon = m_hIcon;
	m_niData.hWnd = m_hWnd;
	sprintf( m_niData.szTip, "QueueDelete" );
	m_niData.uCallbackMessage = IDM_SYSTEMTRAYMESSAGE;
	m_niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_niData.uID = IDR_MAINFRAME;
    Shell_NotifyIcon( NIM_ADD, &m_niData );
	
	return TRUE;  
}

void CQueueDeleteDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CQueueDeleteDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CQueueDeleteDlg::OnClickFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	*pResult = 0;
}

void CQueueDeleteDlg::OnDblclkFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CQueueDeleteDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	m_cFileList.SetWindowPos(0, 1, 1, cx-1, cy-1, 0);
}

void CQueueDeleteDlg::OnOptionsDeleteFilesNow() 
{
	DeleteFiles();
}

void CQueueDeleteDlg::AddFileToList(char *szPath, bool bPrompt, bool bRecurseSubfolders)
{
	std::string strFileName, strLocation;
	SplitPath(szPath, strLocation, strFileName);
	if (strFileName == "." || strFileName == "..")
	{
		return;
	}

	if (Duplicate(szPath))
	{
		return;
	}

	WIN32_FIND_DATA findData;
	if (FindFirstFile(szPath, &findData) == INVALID_HANDLE_VALUE)
	{
		return;
	}
	if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM && bPrompt)
		{
			char szBuffer[MAX_PATH+40];
			sprintf(szBuffer, "%s is a system file, are you sure?", szPath);
			if (MessageBox(szBuffer, 0, MB_YESNO) == IDNO)
			{
				return;
			}
		}
		m_cFileList.InsertItem(m_cFileList.GetItemCount(), szPath);
	} else
	{
		m_cFileList.InsertItem(m_cFileList.GetItemCount(), szPath);

		if (bPrompt)
		{
			if (MessageBox("Check folders?", 0, MB_YESNO) == IDYES)
			{
				bRecurseSubfolders = true;
			} else
			{
				bRecurseSubfolders = false;
			}
		}

		char szBuffer[MAX_PATH+5];
		if (szPath[strlen(szPath)-1] != '\\' && szPath[strlen(szPath)-1] != '/')
		{
			sprintf(szBuffer, "%s/*.*", szPath);
		} else
		{
			sprintf(szBuffer, "%s*.*", szPath);
		}

		HANDLE hResult = FindFirstFile(szBuffer, &findData);
		if (hResult == INVALID_HANDLE_VALUE)
		{
			return;
		}
		
		AddFileToList(findData.cFileName, false, bRecurseSubfolders);

		while (FindNextFile(hResult, &findData))
		{
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && bRecurseSubfolders))
			{

				if (szPath[strlen(szPath)-1] != '\\' && szPath[strlen(szPath)-1] != '/')
				{
					sprintf(szBuffer, "%s\\%s", szPath, findData.cFileName);
				} else
				{
					sprintf(szBuffer, "%s%s", szPath, findData.cFileName);
				}		
				
				AddFileToList(szBuffer, false, bRecurseSubfolders);
			}
		}
	}


}

void CQueueDeleteDlg::RemoveFileFromList(int iSelection, int iCount)
{
	while (iCount)
	{
		m_cFileList.DeleteItem(iSelection);
		--iCount;
	}
}

void CQueueDeleteDlg::OnKeyDownFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;
	
	if (pLVKeyDown->wVKey == 46 || pLVKeyDown->wVKey == 101)
	{
		RemoveFileFromList(m_cFileList.GetSelectionMark(), 1);
	}
	
	*pResult = 0;
}

void CQueueDeleteDlg::OnDropFiles(HDROP hDropped) 
{
	UINT iAddFilesCount = DragQueryFile(hDropped, 0xFFFFFFFF, 0, 0);
	UINT iCount = 0, iPathLength;
	char *szPath;
	while (iCount < iAddFilesCount)
	{
		iPathLength = DragQueryFile(hDropped, iCount, 0, 0);
		
		szPath = new char[iPathLength + 1];
		DragQueryFile(hDropped, iCount, szPath, iPathLength + 1);
		AddFileToList(szPath);
		delete [] szPath;
		
		++iCount;
	}
}

void CQueueDeleteDlg::ReadQueueFile()
{
	std::string strLocation, strFileName;
	SplitPath(m_szAppPath, strLocation, strFileName);
	FILE *pInputFile = fopen((strLocation + "files.lst").c_str(), "rt");
	if (pInputFile == 0)
	{
		return;
	}
	
	char szBuffer[MAX_PATH+1];
	unsigned int iIndex = 0;
	char cBuffer;
	while (!feof(pInputFile))
	{
		iIndex = 0;
		cBuffer = fgetc(pInputFile);
		if (feof(pInputFile))
		{
			break;
		}

		while (cBuffer != '\n')
		{

			szBuffer[iIndex] = cBuffer;
			++iIndex;
			if (feof(pInputFile))
			{
				break;
			}
			cBuffer = fgetc(pInputFile);
		}
		szBuffer[iIndex] = '\0';
		
		if (m_bAutoDelete)
		{
			if (DeleteFileRegardless(szBuffer) == 0)
			{
				AddFileToList(szBuffer, false);
			}
		} else
		{
			AddFileToList(szBuffer, false);
		}
	}

	fclose(pInputFile);
}

void CQueueDeleteDlg::WriteQueueFile()
{
	std::string strLocation, strFileName;
	SplitPath(m_szAppPath, strLocation, strFileName);
	FILE *pOutputFile = fopen((strLocation + "files.lst").c_str(), "wt");
	if (pOutputFile == 0)
	{
		MessageBox("Cannot write file list (files.lst)", "Error", MB_ICONERROR | MB_OK);
		return;
	}
	
	unsigned int iCount = 0;
	char szBuffer[MAX_PATH + 1];
	
	while (iCount < m_cFileList.GetItemCount())
	{
		m_cFileList.GetItemText(iCount, 0, szBuffer, MAX_PATH);
		fprintf(pOutputFile, "%s\n", szBuffer);
		
		++iCount;
	}

	fclose(pOutputFile);	
}

void CQueueDeleteDlg::SplitPath(char *szPath, std::string &strLocation, std::string &strFileName)
{
	strFileName = "";
	strLocation = "";
	
	unsigned int iLength = strlen(szPath);
	while (iLength > 0 && szPath[iLength] != '\\' && szPath[iLength] != '/')
	{
		--iLength;
	}
	if (szPath[iLength] == '\\' || szPath[iLength] == '/')
	{
		++iLength;
	}
	strFileName = szPath+iLength;
	
	char cBuffer = szPath[iLength];
	if (iLength > 0)
	{
		szPath[iLength] = '\0';
		strLocation = szPath;
	}
	szPath[iLength] = cBuffer;
}

void CQueueDeleteDlg::OnDestroy() 
{
	Shell_NotifyIcon( NIM_DELETE, &m_niData );
	WriteQueueFile();
	CDialog::OnDestroy();
}

bool CQueueDeleteDlg::Duplicate(char *szPath)
{
	unsigned int iCount = 0;
	char szBuffer[MAX_PATH + 1];
	
	while (iCount < m_cFileList.GetItemCount())
	{
		m_cFileList.GetItemText(iCount, 0, szBuffer, MAX_PATH);
		if (strcmp(szBuffer, szPath) == 0)
		{
			return true;
		}
		
		++iCount;
	}

	return false;
}

void CQueueDeleteDlg::DeleteFiles()
{
	if (m_cFileList.GetItemCount() == 0)
	{
		MessageBox("No files to delete", "Error", MB_ICONERROR | MB_OK);
		return;
	}

	if (MessageBox("Are you sure you want to delete all files now?", "Delete files now...", MB_YESNO) == IDNO)
	{
		return;
	}

	unsigned int iCount = 0;
	char szBuffer[MAX_PATH + 1];
	

	while (iCount < m_cFileList.GetItemCount())
	{
		m_cFileList.GetItemText(iCount, 0, szBuffer, MAX_PATH);
		if (DeleteFileRegardless(szBuffer))
		{
			m_cFileList.DeleteItem(iCount);
		} else
		{	
			LPVOID lpMsgBuf;
			FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &lpMsgBuf,
				0,
				NULL 
			);
			MessageBox( (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
			LocalFree( lpMsgBuf );
			++iCount;
		}
	}
}

bool CQueueDeleteDlg::DeleteFileRegardless(char *szPath)
{
	if (GetFileAttributes(szPath) & FILE_ATTRIBUTE_DIRECTORY)
	{
		return (bool)(RemoveDirectory(szPath));
	}
	if (!(GetFileAttributes(szPath) & FILE_ATTRIBUTE_NORMAL))
	{
		SetFileAttributes(szPath, FILE_ATTRIBUTE_NORMAL);
	}

	return (bool)(DeleteFile(szPath));
}

void CQueueDeleteDlg::OnOptionsToggleAutoStart() 
{
	CRegKey *pRegKey = new CRegKey;
	pRegKey->Create(HKEY_CURRENT_USER, "Software");
	pRegKey->Create(pRegKey->m_hKey, "Microsoft");
	pRegKey->Create(pRegKey->m_hKey, "Windows");
	pRegKey->Create(pRegKey->m_hKey, "CurrentVersion");
	pRegKey->Create(pRegKey->m_hKey, "Run");

	char szBuffer[MAX_PATH+1];
	char szPathBuffer[MAX_PATH+30];
	sprintf(szPathBuffer, "%s \"autoshutdown\" \"delete\"", m_szAppPath);
	DWORD dwLength = MAX_PATH+1;
	if (pRegKey->QueryValue(szBuffer, "Queue Delete", &dwLength) == ERROR_SUCCESS && strcmp(szPathBuffer, szBuffer) == 0)
	{
		pRegKey->DeleteValue("Queue Delete");
	} else
	{
		pRegKey->SetValue(szPathBuffer, "Queue Delete");
	}

	pRegKey->Close();
	delete pRegKey;
}

void CQueueDeleteDlg::OnOK()
{
}

void CQueueDeleteDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ( nID == 61472 )
	{
		ShowWindow( SW_HIDE );	
	} else
	{
		CDialog::OnSysCommand( nID, lParam );
	}
}

void CQueueDeleteDlg::OnSystemTrayMessage(WPARAM wParam, LPARAM lParam)
{
	CMenu *PopUpMenu;	
	switch(lParam)
	{
	case WM_LBUTTONDOWN:
		ShowWindow( SW_RESTORE );
		ShowWindow( SW_SHOW );
	break;
	case WM_RBUTTONDOWN:
		{
			
			PopUpMenu = m_MainMenu.GetSubMenu( 0 );

			SetForegroundWindow();
			CPoint pt;
			GetCursorPos( &pt );

			SetForegroundWindow();

			PopUpMenu->TrackPopupMenu( TPM_RIGHTALIGN,pt.x,pt.y, this );
			
			break;
		}
	}

}

void CQueueDeleteDlg::ShowWindow( int nCmdShow )
{
	CDialog::ShowWindow( nCmdShow );
}