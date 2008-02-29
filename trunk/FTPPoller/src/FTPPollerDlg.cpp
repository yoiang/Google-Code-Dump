// FTPPollerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTPPoller.h"
#include "FTPPollerDlg.h"

#include "FTPSite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFTPPollerDlg *pDialog ;

/////////////////////////////////////////////////////////////////////////////
// CFTPPollerDlg dialog

CFTPPollerDlg::CFTPPollerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFTPPollerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFTPPollerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFTPPollerDlg::~CFTPPollerDlg()
{
	delete m_pHashTable ;
	delete m_pRegKey ;
}

void CFTPPollerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFTPPollerDlg)
	DDX_Control(pDX, IDC_DOWNLOAD, m_cDownload);
	DDX_Control(pDX, IDC_ENCRYPTPUBLICRING, m_cEncryptPublicRing);
	DDX_Control(pDX, IDC_ENCRYPTPRIVATERING, m_cEncryptPrivateRing);
	DDX_Control(pDX, IDC_ENCRYPTPASSWORD, m_cEncryptPassword);
	DDX_Control(pDX, IDC_ENCRYPTSIGNINGID, m_cEncryptSignID);
	DDX_Control(pDX, IDC_ENCRYPTUSERID, m_cEncryptUserID);
	DDX_Control(pDX, IDC_ENCRYPT, m_cEncrypt);
	DDX_Control(pDX, IDC_DAILYTIME, m_cDailyTime);
	DDX_Control(pDX, IDC_SITENAME, m_cSiteName);
	DDX_Control(pDX, IDC_FTPLIST, m_cFTPList);
	DDX_Control(pDX, IDC_LOCALDIR, m_cLocalDir);
	DDX_Control(pDX, IDC_PASSWORD, m_cPassword);
	DDX_Control(pDX, IDC_REMOTEDIR, m_cRemoteDir);
	DDX_Control(pDX, IDC_USERNAME, m_cUsername);
	DDX_Control(pDX, IDC_WILDCARD, m_cWildcard);
	DDX_Control(pDX, IDC_ADDRESS, m_cAddress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFTPPollerDlg, CDialog)
	//{{AFX_MSG_MAP(CFTPPollerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnClickAdd)
	ON_NOTIFY(NM_CLICK, IDC_FTPLIST, OnClickFtpList)
	ON_BN_CLICKED(IDC_DELETE, OnClickDelete)
	ON_BN_CLICKED(IDC_OFF, OnClickOff)
	ON_BN_CLICKED(IDC_HOURLY, OnClickHourly)
	ON_BN_CLICKED(IDC_DAILY, OnClickDaily)
	ON_BN_CLICKED(IDC_UPLOAD, OnClickUpload)
	ON_BN_CLICKED(IDC_DOWNLOAD, OnClickDownload)
	ON_BN_CLICKED(IDC_ENCRYPT, OnClickEncrypt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTPPollerDlg message handlers

BOOL CFTPPollerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	m_pDownload = (CButton *)(*this).GetDlgItem(IDC_DOWNLOAD);
    ASSERT(m_pDownload != NULL);
    m_pDownload->SetCheck(BST_CHECKED);
	m_pUpload = (CButton *)(*this).GetDlgItem(IDC_UPLOAD);
    ASSERT(m_pUpload != NULL);
    m_pUpload->SetCheck(BST_UNCHECKED);

	m_pOff = (CButton *)(*this).GetDlgItem(IDC_OFF);
    ASSERT(m_pOff != NULL);
    m_pOff->SetCheck(BST_CHECKED);

	m_pHourly = (CButton *)(*this).GetDlgItem(IDC_HOURLY);
    ASSERT(m_pHourly != NULL);
    m_pHourly->SetCheck(BST_UNCHECKED);

	m_pDaily = (CButton *)(*this).GetDlgItem(IDC_DAILY);
    ASSERT(m_pDaily != NULL);
    m_pDaily->SetCheck(BST_UNCHECKED);
	m_cDailyTime.EnableWindow(false) ;
	m_cDailyTime.SetFormat(_T("hh:mm tt"));

	m_cEncryptUserID.EnableWindow(false) ;
	m_cEncryptSignID.EnableWindow(false) ;
	m_cEncryptPassword.EnableWindow(false) ;
	m_cEncryptPublicRing.EnableWindow(false) ;
	m_cEncryptPrivateRing.EnableWindow(false) ;

	m_pRegKey = new CRegKey ;
	m_pRegKey->Create(HKEY_CURRENT_USER, "SOFTWARE") ;
	m_pRegKey->Create(m_pRegKey->m_hKey, "FTP Poller");
	m_pRegKey->Close() ;


	m_pHashTable = new HashTable(50) ;

	ReadReg() ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFTPPollerDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFTPPollerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CFTPPollerDlg::OnClickAdd() 
{
	if (m_cSiteName.GetWindowTextLength() == 0)
	{
		AfxMessageBox("Please fill in the FTP site's name") ;
		m_cSiteName.SetFocus() ;
		return ;
	}
	if (m_cAddress.GetWindowTextLength() == 0)
	{
		AfxMessageBox("Please fill in the FTP site's address") ;
		m_cAddress.SetFocus() ;
		return ;
	}
	if (m_cUsername.GetWindowTextLength() == 0)
	{
		AfxMessageBox("Please fill in the FTP site's user name") ;
		m_cUsername.SetFocus() ;
		return ;
	}
	if (m_cPassword.GetWindowTextLength() == 0)
	{
		AfxMessageBox("Please fill in the FTP site's password") ;
		m_cPassword.SetFocus() ;
		return ;
	}
	if (m_cRemoteDir.GetWindowTextLength() == 0)
	{
		AfxMessageBox("Please fill in the FTP site's remote directory") ;
		m_cRemoteDir.SetFocus() ;
		return ;
	}
	if (m_cWildcard.GetWindowTextLength() == 0)
	{
		AfxMessageBox("Please fill in the FTP site's wildcard") ;
		m_cWildcard.SetFocus();
		return ;
	}
	if (m_cLocalDir.GetWindowTextLength() == 0)
	{
		AfxMessageBox("Please fill in the FTP site's local directory") ;
		m_cLocalDir.SetFocus() ;
		return ;
	}
	if (m_cEncrypt.GetCheck())
	{
		if (m_cEncryptUserID.GetWindowTextLength() == 0)
		{
			AfxMessageBox("Please fill in the FTP site's PGP user ID") ;
			m_cEncryptUserID.SetFocus() ;
			return ;
		}
		if (m_cEncryptSignID.GetWindowTextLength() == 0)
		{
			AfxMessageBox("Please fill in the FTP site's PGP sign ID") ;
			m_cEncryptSignID.SetFocus() ;
			return ;
		}
		if (m_cEncryptPassword.GetWindowTextLength() == 0)
		{
			AfxMessageBox("Please fill in the FTP site's PGP password") ;
			m_cEncryptPassword.SetFocus() ;
			return ;
		}
		if (m_cEncryptPublicRing.GetWindowTextLength() == 0)
		{
			AfxMessageBox("Please fill in the FTP site's PGP public ring file") ;
			m_cEncryptPublicRing.SetFocus() ;
			return ;
		}
		if (m_cEncryptPrivateRing.GetWindowTextLength() == 0)
		{
			AfxMessageBox("Please fill in the FTP site's PGP private ring file") ;
			m_cEncryptPrivateRing.SetFocus() ;
			return ;
		}
	}


	char szBuffer[256] ;
	FTPSite *pNewFTPSite = new FTPSite ;
	CTime cTempTime ;

	pNewFTPSite->SetDownload((bool)(m_pDownload->GetCheck())) ;

	if (m_pOff->GetCheck()) pNewFTPSite->SetPolling(POLL_OFF) ;
	else if (m_pHourly->GetCheck()) pNewFTPSite->SetPolling(POLL_HOURLY) ;
	else if (m_pDaily->GetCheck()) 
	{
		pNewFTPSite->SetPolling(POLL_DAILY) ;
		m_cDailyTime.GetTime(cTempTime) ;
		pNewFTPSite->SetPollingTime(cTempTime) ;
	}

	pNewFTPSite->SetEncrypt((bool)(m_cEncrypt.GetCheck())) ;

	m_cSiteName.GetWindowText(szBuffer, 256) ;
	pNewFTPSite->SetName(szBuffer) ;
	
	m_cAddress.GetWindowText(szBuffer, 256) ;
	pNewFTPSite->SetAddress(szBuffer) ;

	m_cUsername.GetWindowText(szBuffer, 256) ;
	pNewFTPSite->SetUsername(szBuffer) ;

	m_cPassword.GetWindowText(szBuffer, 256) ;
	pNewFTPSite->SetPassword(szBuffer) ;

	m_cRemoteDir.GetWindowText(szBuffer, 256) ;
	pNewFTPSite->SetRemoteDir(szBuffer) ;

	m_cWildcard.GetWindowText(szBuffer, 256) ;
	pNewFTPSite->SetWildcard(szBuffer) ;

	m_cLocalDir.GetWindowText(szBuffer, 256) ;
	pNewFTPSite->SetLocalDir(szBuffer) ;

	if (m_cEncrypt.GetCheck())
	{
		m_cEncryptUserID.GetWindowText(szBuffer, 256) ;
		pNewFTPSite->SetEncryptUserID(szBuffer) ;

		m_cEncryptSignID.GetWindowText(szBuffer, 256) ;
		pNewFTPSite->SetEncryptSignID(szBuffer) ;

		m_cEncryptPassword.GetWindowText(szBuffer, 256) ;
		pNewFTPSite->SetEncryptPassword(szBuffer) ;

		m_cEncryptPublicRing.GetWindowText(szBuffer, 256) ;
		pNewFTPSite->SetEncryptPublicRing(szBuffer) ;

		m_cEncryptPrivateRing.GetWindowText(szBuffer, 256) ;
		pNewFTPSite->SetEncryptPrivateRing(szBuffer) ;
	}

	if (m_pHashTable->Add(pNewFTPSite)) m_cFTPList.InsertItem(1, pNewFTPSite->GetName()) ;


	pNewFTPSite->SetTaskTimer(false) ;



	m_pRegKey->Create(HKEY_CURRENT_USER, "SOFTWARE") ;
	m_pRegKey->Create(m_pRegKey->m_hKey, "FTP Poller") ;
	m_pRegKey->Create(m_pRegKey->m_hKey, "FTP Sites") ;

	char szIndex[256] ;
	int iTrav = 0 ;
	DWORD dwCount = 256 ;
	sprintf(szIndex, "%d", iTrav) ;
	while (m_pRegKey->QueryValue(szBuffer, szIndex, &dwCount) == ERROR_SUCCESS)
	{
		dwCount = 256 ;
		if (strcmp(pNewFTPSite->GetName(), szBuffer) == 0) break ;
		iTrav ++ ;
		sprintf(szIndex, "%d", iTrav) ;
	}

	m_pRegKey->SetValue(pNewFTPSite->GetName(), szIndex) ;
	m_pRegKey->Create(m_pRegKey->m_hKey, pNewFTPSite->GetName()) ;

	m_pRegKey->SetValue(pNewFTPSite->GetAddress(), "Address") ;
	m_pRegKey->SetValue(pNewFTPSite->GetUsername(), "Username") ;
	m_pRegKey->SetValue(pNewFTPSite->GetPassword(), "Password") ;
	m_pRegKey->SetValue(pNewFTPSite->GetRemoteDir(), "RemoteDir") ;
	m_pRegKey->SetValue(pNewFTPSite->GetWildcard(), "Wildcard") ;
	m_pRegKey->SetValue(pNewFTPSite->GetLocalDir(), "LocalDir") ;

	m_pRegKey->SetValue(pNewFTPSite->GetEncryptUserID(), "EncryptUserID") ;
	m_pRegKey->SetValue(pNewFTPSite->GetEncryptSignID(), "EncryptSignID") ;
	m_pRegKey->SetValue(pNewFTPSite->GetEncryptPassword(), "EncryptPassword") ;
	m_pRegKey->SetValue(pNewFTPSite->GetEncryptPublicRing(), "EncryptPublicRing") ;
	m_pRegKey->SetValue(pNewFTPSite->GetEncryptPrivateRing(), "EncryptPrivateRing") ;


	if (pNewFTPSite->GetDownload() == true) m_pRegKey->SetValue("true", "Download") ;
	else m_pRegKey->SetValue("false", "Download") ;
	m_pRegKey->SetValue(itoa(pNewFTPSite->GetPolling(), szBuffer, 10), "Polling") ;
	if (pNewFTPSite->GetPolling() == POLL_DAILY)
	{
		m_pRegKey->SetValue((LPCTSTR)((pNewFTPSite->GetPollingTime()).Format("%H")), "Hour");

		m_pRegKey->SetValue((LPCTSTR)((pNewFTPSite->GetPollingTime()).Format("%M")), "Minute") ;
	}
	if (pNewFTPSite->GetEncrypt() == true) m_pRegKey->SetValue("true", "Encrypt") ;
	else m_pRegKey->SetValue("false", "Encrypt") ;

	m_pRegKey->Close() ;
}

void CFTPPollerDlg::OnClickDelete() 
{
	if (m_cSiteName.GetWindowTextLength() == 0)
	{
		AfxMessageBox("Please fill in the FTP site's name") ;
		m_cSiteName.SetFocus() ;
		return ;
	}

	char szBuffer[256] ;
	m_cSiteName.GetWindowText(szBuffer, 256) ;

	LVFINDINFO FindDelete ;
	FindDelete.flags = LVFI_STRING ;
	FindDelete.psz = szBuffer ;

	int iFindItem = m_cFTPList.FindItem(&FindDelete) ;
	if (iFindItem == -1) return ;

	m_cFTPList.DeleteItem(iFindItem) ;
	
	m_pHashTable->Remove(szBuffer) ;

	m_pRegKey->Create(HKEY_CURRENT_USER, "SOFTWARE") ;
	m_pRegKey->Create(m_pRegKey->m_hKey, "FTP Poller") ;
	m_pRegKey->Create(m_pRegKey->m_hKey, "FTP Sites") ;

	m_pRegKey->RecurseDeleteKey(szBuffer);

	char szIndex[256], szResult[256] ;
	int iTrav = 0 ;
	DWORD dwCount = 256 ;
	sprintf(szIndex, "%d", iTrav) ;
	while (m_pRegKey->QueryValue(szResult, szIndex, &dwCount) == ERROR_SUCCESS)
	{
		dwCount = 256 ;
		if (strcmp(szBuffer, szResult) == 0) break ;

		iTrav ++ ;
		sprintf(szIndex, "%d", iTrav) ;
	}

	int iLast = iTrav ;
	sprintf(szIndex, "%d", iLast) ;
	while (m_pRegKey->QueryValue(szResult, szIndex, &dwCount) == ERROR_SUCCESS)
	{
		dwCount = 256 ;
		iLast ++ ;
		sprintf(szIndex, "%d", iLast) ;
	}
	iLast -= 1 ;
	if (iLast != iTrav)
	{
		sprintf(szIndex, "%d", iLast) ;
		dwCount = 256 ;
		m_pRegKey->QueryValue(szResult, szIndex, &dwCount) ;
		m_pRegKey->DeleteValue(szIndex) ;

		sprintf(szIndex, "%d", iTrav) ;
		m_pRegKey->SetValue(szResult, szIndex) ; 
	} else
	{
		sprintf(szIndex, "%d", iTrav) ;
		m_pRegKey->DeleteValue(szIndex) ;
	}
}

void CFTPPollerDlg::OnClickFtpList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	char szBuffer[256] ;

	int iItemNumber = m_cFTPList.GetSelectionMark() ;
	if (iItemNumber == -1) return ;
	m_cFTPList.GetItemText(iItemNumber, 0, szBuffer, 256) ;

	FTPSite *pTempFTPSite = m_pHashTable->Get(szBuffer) ;
	if (pTempFTPSite == NULL)
	{
		*pResult = 0;
		return ;
	}

	m_cSiteName.SetWindowText(pTempFTPSite->GetName()) ;
	m_cAddress.SetWindowText(pTempFTPSite->GetAddress()) ;
	m_cUsername.SetWindowText(pTempFTPSite->GetUsername()) ;
	m_cPassword.SetWindowText(pTempFTPSite->GetPassword()) ;
	m_cRemoteDir.SetWindowText(pTempFTPSite->GetRemoteDir()) ;
	m_cWildcard.SetWindowText(pTempFTPSite->GetWildcard()) ;
	m_cLocalDir.SetWindowText(pTempFTPSite->GetLocalDir()) ;

	m_cEncryptUserID.SetWindowText(pTempFTPSite->GetEncryptUserID()) ;
	m_cEncryptSignID.SetWindowText(pTempFTPSite->GetEncryptSignID()) ;
	m_cEncryptPassword.SetWindowText(pTempFTPSite->GetEncryptPassword()) ;
	m_cEncryptPublicRing.SetWindowText(pTempFTPSite->GetEncryptPublicRing()) ;
	m_cEncryptPrivateRing.SetWindowText(pTempFTPSite->GetEncryptPrivateRing()) ;


	m_cEncrypt.SetCheck(pTempFTPSite->GetEncrypt()) ;

	OnClickEncrypt() ;
	if (m_cDownload.GetCheck())
	{
		m_cEncrypt.SetWindowText("Decrypt") ;
	} else
	{
		m_cEncrypt.SetWindowText("Encrypt") ;
	}

	if (pTempFTPSite->GetDownload() == true)
	{
	    m_pDownload->SetCheck(BST_CHECKED);
		m_pUpload->SetCheck(BST_UNCHECKED);
	} else
	{
	    m_pDownload->SetCheck(BST_UNCHECKED);
		m_pUpload->SetCheck(BST_CHECKED);
	}

	switch(pTempFTPSite->GetPolling())
	{
	case POLL_OFF:
		m_pOff->SetCheck(BST_CHECKED) ;
		m_pHourly->SetCheck(BST_UNCHECKED) ;
		m_pDaily->SetCheck(BST_UNCHECKED) ;
		m_cDailyTime.EnableWindow(false) ;
	break ;
	case POLL_HOURLY:
		m_pOff->SetCheck(BST_UNCHECKED) ;
		m_pHourly->SetCheck(BST_CHECKED) ;
		m_pDaily->SetCheck(BST_UNCHECKED) ;
		m_cDailyTime.EnableWindow(false) ;
	break ;
	case POLL_DAILY:
		m_pOff->SetCheck(BST_UNCHECKED) ;
		m_pHourly->SetCheck(BST_UNCHECKED) ;
		m_pDaily->SetCheck(BST_CHECKED) ;

		m_cDailyTime.EnableWindow(true) ;
		m_cDailyTime.SetTime(&(pTempFTPSite->GetPollingTime())) ;
	break ;
	}
	
	*pResult = 0;
}

void CFTPPollerDlg::ReadReg()
{
	FTPSite *pNewFTPSite ;

	char szIndex[256], szBuffer[256] ;
	int iTrav = 0 ;
	DWORD dwCount = 256 ;
	sprintf(szIndex, "%d", iTrav) ;

	m_pRegKey->Create(HKEY_CURRENT_USER, "SOFTWARE") ;
	m_pRegKey->Create(m_pRegKey->m_hKey, "FTP Poller") ;
	m_pRegKey->Create(m_pRegKey->m_hKey, "FTP Sites") ;
	while (m_pRegKey->QueryValue(szBuffer, szIndex, &dwCount) == ERROR_SUCCESS)
	{
		pNewFTPSite = new FTPSite ;
		pNewFTPSite->SetName(szBuffer) ;

		m_pRegKey->Create(m_pRegKey->m_hKey, szBuffer) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "Address", &dwCount) ;
		pNewFTPSite->SetAddress(szBuffer) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "Username", &dwCount) ;
		pNewFTPSite->SetUsername(szBuffer) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "Password", &dwCount) ;
		pNewFTPSite->SetPassword(szBuffer) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "RemoteDir", &dwCount) ;
		pNewFTPSite->SetRemoteDir(szBuffer) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "Wildcard", &dwCount) ;
		pNewFTPSite->SetWildcard(szBuffer) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "LocalDir", &dwCount) ;
		pNewFTPSite->SetLocalDir(szBuffer) ;


		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "EncryptUserID", &dwCount) ;
		pNewFTPSite->SetEncryptUserID(szBuffer) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "EncryptSignID", &dwCount) ;
		pNewFTPSite->SetEncryptSignID(szBuffer) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "EncryptPassword", &dwCount) ;
		pNewFTPSite->SetEncryptPassword(szBuffer) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "EncryptPublicRing", &dwCount) ;
		pNewFTPSite->SetEncryptPublicRing(szBuffer) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "EncryptPrivateRing", &dwCount) ;
		pNewFTPSite->SetEncryptPrivateRing(szBuffer) ;


		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "Download", &dwCount) ;
		if (strcmp(szBuffer, "true") == 0) pNewFTPSite->SetDownload(true) ;
		else pNewFTPSite->SetDownload(false) ;

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "Polling", &dwCount) ;
		pNewFTPSite->SetPolling(atoi(szBuffer)) ;

		if (pNewFTPSite->GetPolling() == POLL_DAILY)
		{
			dwCount = 256 ;
			m_pRegKey->QueryValue(szBuffer, "Hour", &dwCount) ;

			dwCount = 256 ;
			m_pRegKey->QueryValue(szIndex, "Minute", &dwCount) ;

			CTime cTempTime(1999, 2, 2, atoi(szBuffer), atoi(szIndex), 0) ;
			pNewFTPSite->SetPollingTime(cTempTime) ;
		}

		dwCount = 256 ;
		m_pRegKey->QueryValue(szBuffer, "Encrypt", &dwCount) ;
		if (strcmp(szBuffer, "true") == 0) pNewFTPSite->SetEncrypt(true) ;
		else pNewFTPSite->SetEncrypt(false) ;

		dwCount = 256 ;
		m_pRegKey->Close() ;

		if (m_pHashTable->Add(pNewFTPSite)) m_cFTPList.InsertItem(1, pNewFTPSite->GetName()) ;

		pNewFTPSite->SetTaskTimer(false) ;


		iTrav ++ ;
		sprintf(szIndex, "%d", iTrav) ;
		m_pRegKey->Create(HKEY_CURRENT_USER, "SOFTWARE") ;
		m_pRegKey->Create(m_pRegKey->m_hKey, "FTP Poller") ;
		m_pRegKey->Create(m_pRegKey->m_hKey, "FTP Sites") ;
	}


	m_pRegKey->Close() ;
}

UINT FTPEventThreadCreator( LPVOID pParam )
{
	pDialog->CallTimers((UINT)(pParam)) ;
	return 0 ;
}

void CALLBACK EXPORT TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	AfxBeginThread(FTPEventThreadCreator, (LPVOID)(nIDEvent)) ;
}

void CFTPPollerDlg::CallTimers(UINT nIDEvent) 
{
//	CBitmap *cTempGo = (CBitmap*)(*this).GetDlgItem(IDB_GO) ;
//	CBitmap *cTempStop = (CBitmap*)(*this).GetDlgItem(IDB_STOP) ;
////	if (nIDEvent == m_nHourly)
////	{
//		m_cHourlyStatus.SetBitmap( ::LoadBitmap(NULL, MAKEINTRESOURCE(IDB_GO)) ) ;
//		m_cHourlyStatus.SetBitmap((HBITMAP)(*cTempGo));
	m_pHashTable->CallPolling(nIDEvent) ;
//		m_cHourlyStatus.SetBitmap((HBITMAP)(*cTempStop)) ;
////	}
//	KillTimer(m_nHourly) ;
}

void CFTPPollerDlg::OnClickOff() 
{
	m_cDailyTime.EnableWindow(false) ;
}

void CFTPPollerDlg::OnClickHourly() 
{
	m_cDailyTime.EnableWindow(false) ;
}

void CFTPPollerDlg::OnClickDaily() 
{
	m_cDailyTime.EnableWindow(true) ;
}

void CFTPPollerDlg::OnClickUpload() 
{
	m_cEncrypt.SetWindowText("Encrypt") ;
}

void CFTPPollerDlg::OnClickDownload() 
{
	m_cEncrypt.SetWindowText("Decrypt") ;
}

void CFTPPollerDlg::OnClickEncrypt() 
{
	if (m_cEncrypt.GetCheck())
	{
		m_cEncryptUserID.EnableWindow(true) ;
		m_cEncryptSignID.EnableWindow(true) ;
		m_cEncryptPassword.EnableWindow(true) ;
		m_cEncryptPublicRing.EnableWindow(true) ;
		m_cEncryptPrivateRing.EnableWindow(true) ;
	} else
	{
		m_cEncryptUserID.EnableWindow(false) ;
		m_cEncryptSignID.EnableWindow(false) ;
		m_cEncryptPassword.EnableWindow(false) ;
		m_cEncryptPublicRing.EnableWindow(false) ;
		m_cEncryptPrivateRing.EnableWindow(false) ;
	}
}
