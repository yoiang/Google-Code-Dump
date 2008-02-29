#include "FTPSite.h"

#include <string.h>

#include "ZipArchive\ZipArchive.h"
#import "C:\WINNT\System32\Nsdpgp2.dll" no_namespace

//#include "FTPPollerDlg.h"
void CALLBACK EXPORT TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) ;

bool IsNumericExtension(const char *szFilename)
{
	int iLength = strlen(szFilename) ;
	if (iLength < 4) return false ;
	if (szFilename[iLength - 1] >= '0' && szFilename[iLength - 1] <= '9' &&
		szFilename[iLength - 2] >= '0' && szFilename[iLength - 2] <= '9' &&
		szFilename[iLength - 3] >= '0' && szFilename[iLength - 3] <= '9')
		return true ;

	return false ;
}

FTPSite::FTPSite() 
{
	m_bDownload = true ;
	m_iPolling = POLL_OFF ;
	m_nTimer = -1 ;
	m_iRetryCount = -1 ;

	m_bEncrypt = false ;

	m_cstrName = "" ;
	m_cstrAddress = "" ;
	m_cstrUsername = "" ;
	m_cstrPassword = "" ;
	m_cstrWildcard = "" ;
	m_cstrRemoteDir = "" ;
	m_cstrLocalDir = "" ;
}

FTPSite::~FTPSite()
{
	if (m_nTimer != -1) KillTimer(NULL, m_nTimer) ;
}

void FTPSite::SetDownload(bool bSetDownload)
{	m_bDownload = bSetDownload ;	}

bool FTPSite::GetDownload()
{	return m_bDownload ;	}

void FTPSite::SetPolling(int iSetPolling)
{	m_iPolling = iSetPolling ;	}

int FTPSite::GetPolling()
{	return m_iPolling ;	}

void FTPSite::SetPollingTime(CTime cSetPollingTime)
{	m_tPollingTime = cSetPollingTime ;	}

CTime FTPSite::GetPollingTime() 
{	return m_tPollingTime ;	}

void FTPSite::SetEncrypt(bool bSetEncrypt)
{	m_bEncrypt = bSetEncrypt ;	}

bool FTPSite::GetEncrypt()
{	return m_bEncrypt ;	}

void FTPSite::SetName(CString m_cstrSetName)
{	m_cstrName = m_cstrSetName ;	}

CString FTPSite::GetName()
{	return m_cstrName ;	}

void FTPSite::SetAddress(CString m_cstrSetAddress)
{	m_cstrAddress = m_cstrSetAddress ;	}

CString FTPSite::GetAddress()
{	return m_cstrAddress ;	}

void FTPSite::SetUsername(CString m_cstrSetUsername)
{	m_cstrUsername = m_cstrSetUsername ;	}

CString FTPSite::GetUsername()
{	return m_cstrUsername ;	}

void FTPSite::SetPassword(CString m_cstrSetPassword)
{	m_cstrPassword = m_cstrSetPassword ;	}

CString FTPSite::GetPassword()
{	return m_cstrPassword ;	}

void FTPSite::SetWildcard(CString m_cstrSetWildcard)
{	m_cstrWildcard = m_cstrSetWildcard ;	}

CString FTPSite::GetWildcard()
{	return m_cstrWildcard ;	}

void FTPSite::SetRemoteDir(CString m_cstrSetRemoteDir)
{	m_cstrRemoteDir = m_cstrSetRemoteDir ;	}

CString FTPSite::GetRemoteDir()
{	return m_cstrRemoteDir ;	}

void FTPSite::SetLocalDir(CString m_cstrSetLocalDir)
{	m_cstrLocalDir = m_cstrSetLocalDir ;	}

CString FTPSite::GetLocalDir()
{	return m_cstrLocalDir ;	}

void FTPSite::SetEncryptUserID(CString cstrSetEncryptUserID)
{	m_cstrEncryptUserID = cstrSetEncryptUserID ;	}

CString FTPSite::GetEncryptUserID()
{	return m_cstrEncryptUserID ;	}

void FTPSite::SetEncryptSignID(CString cstrSetEncryptSignID) 
{	m_cstrEncryptSignID = cstrSetEncryptSignID ;	}

CString FTPSite::GetEncryptSignID() 
{	return m_cstrEncryptSignID ;	}

void FTPSite::SetEncryptPassword(CString cstrSetEncryptPassword) 
{	m_cstrEncryptPassword = cstrSetEncryptPassword ;	}

CString FTPSite::GetEncryptPassword() 
{	return m_cstrEncryptPassword ;	}

void FTPSite::SetEncryptPublicRing(CString cstrSetEncryptPublicRing) 
{	m_cstrEncryptPublicRing = cstrSetEncryptPublicRing ;	}

CString FTPSite::GetEncryptPublicRing () 
{	return m_cstrEncryptPublicRing ;	}

void FTPSite::SetEncryptPrivateRing(CString cstrSetEncryptPrivateRing) 
{	m_cstrEncryptPrivateRing = cstrSetEncryptPrivateRing ;	}

CString FTPSite::GetEncryptPrivateRing() 
{	return m_cstrEncryptPrivateRing ;	}


void FTPSite::MoveSendFile(CFtpConnection* pFTPConnect, CString cstrFilename)
{
	pFTPConnect->PutFile(cstrFilename, cstrFilename, FALSE) ;
	MoveFile((LPCTSTR)(cstrFilename), (LPCTSTR)("Send\\" + cstrFilename)) ; 
}

void FTPSite::EncryptFile(CString cstrFilename)
{
	HASH algo = SHA1;
	_bstr_t userID = m_cstrEncryptUserID;
	_bstr_t recipientID;
	_bstr_t signingID = m_cstrEncryptSignID;
	_bstr_t password = m_cstrEncryptPassword;
	_bstr_t inputFile = cstrFilename ;
	_bstr_t outputFile = cstrFilename + ".pgp";
	_bstr_t publicRing = m_cstrEncryptPublicRing;
	_bstr_t privateRing = m_cstrEncryptPrivateRing;

	CoInitialize(NULL);
	try
	{	
		IPGPPtr myRef(__uuidof(PGP));
	
		recipientID = myRef->GetKeyIDFromUserID( publicRing, privateRing, userID );
	
		myRef->EncryptAndSignFile( algo, recipientID, signingID, password, inputFile, outputFile, publicRing, privateRing );
		myRef->WipeFile(inputFile);

		myRef = NULL;
	} catch(_com_error err)
	{
//		cout << err.Description() << endl;
	}

	CoUninitialize();
}

void FTPSite::DecryptFile(CString cstrFilename)
{
	HASH algo = SHA1;
	_bstr_t userID = m_cstrEncryptUserID;
	_bstr_t signingID = m_cstrEncryptSignID;
	_bstr_t password = m_cstrEncryptPassword;
	_bstr_t inputFile = cstrFilename ;
	_bstr_t outputFile = cstrFilename.Left(cstrFilename.GetLength() - 4) ;
	_bstr_t wipeFile = cstrFilename ;
	_bstr_t publicRing = m_cstrEncryptPublicRing;
	_bstr_t privateRing = m_cstrEncryptPrivateRing;
	_bstr_t sigFile = cstrFilename + ".sig";
	_bstr_t recipientID ;

	CoInitialize(NULL);
	try
	{	
		IPGPPtr myRef(__uuidof(PGP));
	
		recipientID = myRef->GetKeyIDFromUserID( publicRing, privateRing, userID );

		myRef->DecryptFile(sigFile, inputFile, outputFile, password, publicRing, privateRing) ;
//		myRef->WipeFile(inputFile);

		myRef = NULL;
	} catch(_com_error err)
	{
//		cout << err.Description() << endl;
	}

	CoUninitialize();
}

void FTPSite::DoTask()
{
	CZipArchive cZip ;

	BOOL bWorking ;
	WIN32_FIND_DATA FindFileData ;
	HANDLE hFind ;
	CString cstrFilename ;

    CInternetSession InternetSession(_T("FTP Poller"));
    CFtpConnection* pFTPConnect ;

	try
	{
		pFTPConnect = InternetSession.GetFtpConnection(m_cstrAddress, m_cstrUsername, m_cstrPassword);
	}
	catch (CInternetException* pEx)
	{
//		TCHAR sz[1024];
//		pEx->GetErrorMessage(sz, 1024);
//		printf("ERROR!  %s\n", sz);
		pEx->Delete();

		SetTaskTimer(true) ;
		return ;
	}

    CFtpFileFind FileFinder(pFTPConnect);

    if (!pFTPConnect->SetCurrentDirectory(m_cstrRemoteDir))
	{
		AfxMessageBox("Invalid remote directory with site "+ m_cstrName) ;
		SetTaskTimer(true) ;
		return ;
	}

    if (!SetCurrentDirectory(m_cstrLocalDir))
	{
		AfxMessageBox("Invalid current directory with site " + m_cstrName) ;
		SetTaskTimer(true) ;
		return ;
	}

    if (m_bDownload)
    {
		CreateDirectory("Recieve", NULL) ;
		bWorking = FileFinder.FindFile(m_cstrWildcard);

		while (bWorking)
		{
			bWorking = FileFinder.FindNextFile();

			cstrFilename = FileFinder.GetFileName() ;
			if (cstrFilename.GetLength() > 4 && cstrFilename.Right(3) == "pgp" && m_bEncrypt)
			{
				pFTPConnect->GetFile(cstrFilename, "Recieve\\" + cstrFilename, FALSE) ;
				DecryptFile("Recieve\\" + cstrFilename) ;
				try
				{
					cZip.Open("Recieve\\" + cstrFilename.Left(cstrFilename.GetLength()-4), CZipArchive::zipOpenReadOnly) ;

					int iNumFiles = cZip.GetCount(false) ;
					for (int iTrav = 0 ; iTrav < iNumFiles ; iTrav ++)
						cZip.ExtractFile(iTrav, ".\\", false) ;
					cZip.Close() ;
				}	catch (CException *e)
				{
				}


			} else pFTPConnect->GetFile(cstrFilename, cstrFilename, FALSE) ;
		}
		bWorking = FileFinder.FindFile(m_cstrWildcard);

		while (bWorking)
		{
			bWorking = FileFinder.FindNextFile();

			cstrFilename = FileFinder.GetFileName() ;
			pFTPConnect->Remove(cstrFilename) ;
		}

	} else
	{
		CreateDirectory("Send", NULL) ;
		hFind = FindFirstFile(m_cstrWildcard, &FindFileData);

		if (m_bEncrypt)
		{
			if (hFind)
			{
				cstrFilename = FindFileData.cFileName ;

				if (IsNumericExtension((LPCTSTR)(cstrFilename)))
				{
					try
					{
						if (GetFileAttributes((LPCTSTR)(cstrFilename.Left(cstrFilename.GetLength() - 3) + "zip")) == -1)
						{
							cZip.Open((LPCTSTR)(cstrFilename.Left(cstrFilename.GetLength() - 3) + "zip"), CZipArchive::zipCreate, 0) ;
						} else
						{
							cZip.Open((LPCTSTR)(cstrFilename.Left(cstrFilename.GetLength() - 3) + "zip"), CZipArchive::zipOpen, 0) ;
						}
						cZip.AddNewFile((LPCTSTR)(cstrFilename), Z_BEST_COMPRESSION) ;
						cZip.Close() ;
					} catch (CException* e)
					{
						 if (e->IsKindOf( RUNTIME_CLASS( CZipException )))
						 {
							CZipException* p = (CZipException*) e;
							  //... and so on 
						 } else if (e->IsKindOf( RUNTIME_CLASS( CFileException )))
						 {
							CFileException* p = (CFileException*) e;
//							if( p->m_cause == CFileException::fileNotFound )
//							{
//								p = p ;
//							}							  //... and so on 
						 } else
						 {
							// the only possibility is a memory exception I suppose
							  //... and so on 
						 }
						 e->Delete();
					}
				}
				while (FindNextFile(hFind, &FindFileData)) 
				{
					cstrFilename = FindFileData.cFileName ;

					if (IsNumericExtension((LPCTSTR)(cstrFilename)))
					{
						try
						{
							if (GetFileAttributes((LPCTSTR)(cstrFilename.Left(cstrFilename.GetLength() - 3) + "zip")) == -1)
							{
								cZip.Open((LPCTSTR)(cstrFilename.Left(cstrFilename.GetLength() - 3) + "zip"), CZipArchive::zipCreate, 0) ;
							} else
							{
								cZip.Open((LPCTSTR)(cstrFilename.Left(cstrFilename.GetLength() - 3) + "zip"), CZipArchive::zipOpen, 0) ;
							}
							cZip.AddNewFile((LPCTSTR)(cstrFilename), Z_BEST_COMPRESSION) ;
							cZip.Close() ;
						} catch (CException* e)
						{
							 if (e->IsKindOf( RUNTIME_CLASS( CZipException )))
							 {
								CZipException* p = (CZipException*) e;
								  //... and so on 
							 } else if (e->IsKindOf( RUNTIME_CLASS( CFileException )))
							 {
								CFileException* p = (CFileException*) e;
			//							if( p->m_cause == CFileException::fileNotFound )
			//							{
			//								p = p ;
			//							}							  //... and so on 
							 } else
							 {
								// the only possibility is a memory exception I suppose
								  //... and so on 
							 }
							 e->Delete();
						}
					}
				}
			
			}

			FindClose(hFind) ;

			hFind = FindFirstFile(m_cstrWildcard, &FindFileData);

			if (hFind)
			{
				cstrFilename = FindFileData.cFileName ;
				if (IsNumericExtension(cstrFilename)) MoveFile(cstrFilename, (LPCTSTR)("Send\\" + cstrFilename)) ;

				while (FindNextFile(hFind, &FindFileData)) 
				{
					cstrFilename = FindFileData.cFileName ;
					if (IsNumericExtension(cstrFilename)) MoveFile(cstrFilename, (LPCTSTR)("Send\\" + cstrFilename)) ;
				}
			}

			FindClose(hFind) ;

			hFind = FindFirstFile("*.zip", &FindFileData);

			char szCurrentDir[256], szBuffer[256] ;
			GetCurrentDirectory(256, szCurrentDir) ;

			if (hFind)
			{
				sprintf(szBuffer, "%s\\%s", szCurrentDir, FindFileData.cFileName) ;
				EncryptFile(szBuffer) ;
				while (FindNextFile(hFind, &FindFileData)) 
				{
					sprintf(szBuffer, "%s\\%s", szCurrentDir, FindFileData.cFileName) ;
					EncryptFile(szBuffer) ;
				}
			}

			FindClose(hFind) ;

			hFind = FindFirstFile("*.pgp", &FindFileData);

			if (hFind)
			{
				MoveSendFile(pFTPConnect, FindFileData.cFileName) ;
				while (FindNextFile(hFind, &FindFileData)) 
				{
					MoveSendFile(pFTPConnect, FindFileData.cFileName) ;
				}
			}
		} else
		{
			if (hFind)
			{
				MoveSendFile(pFTPConnect, FindFileData.cFileName) ;
				while (FindNextFile(hFind, &FindFileData)) 
				{
					MoveSendFile(pFTPConnect, FindFileData.cFileName) ;
				}
			}
		}
	    FindClose(hFind);
	}

	FileFinder.Close() ;
	pFTPConnect->Close() ;
	delete pFTPConnect ;
	InternetSession.Close() ;

	if (m_nTimer != -1) KillTimer(NULL, m_nTimer) ;
	SetTaskTimer(false) ;
}

void FTPSite::SetTaskTimer(bool bRetry)
{
	if (m_nTimer != -1) KillTimer(NULL, m_nTimer) ;

	CTime tCurrentTime = CTime::GetCurrentTime() ;
	CTime tTaskTime ;
	CTimeSpan tsTaskSpan ;
	if (bRetry)
	{
		m_iRetryCount ++ ;
		if (m_iRetryCount <= 5)	m_nTimer = SetTimer(NULL, 0, 60000, (TIMERPROC)TimerProc); 
		return ;
	}

	switch (m_iPolling)
	{
	case POLL_OFF:
	return ;

	case POLL_HOURLY:
		tTaskTime = CTime(tCurrentTime.GetYear(), tCurrentTime.GetMonth(), tCurrentTime.GetDay(), tCurrentTime.GetHour() + 1, 0, 0) ;
		tsTaskSpan = tTaskTime - tCurrentTime ;
	break ;

	case POLL_DAILY:
		if (tCurrentTime.GetHour() < m_tPollingTime.GetHour() || 
		   (tCurrentTime.GetHour() == m_tPollingTime.GetHour() && tCurrentTime.GetMinute() < m_tPollingTime.GetMinute()))
		{
			tTaskTime = CTime(tCurrentTime.GetYear(), tCurrentTime.GetMonth(), tCurrentTime.GetDay(), m_tPollingTime.GetHour(), m_tPollingTime.GetMinute(), 0) ;
		} else
		{
			tTaskTime = CTime(tCurrentTime.GetYear(), tCurrentTime.GetMonth(), tCurrentTime.GetDay() + 1, m_tPollingTime.GetHour(), m_tPollingTime.GetMinute(), 0) ;
		}
		tsTaskSpan = tTaskTime - tCurrentTime ;
	break ;
	}
	m_nTimer = SetTimer(NULL, 0, tsTaskSpan.GetTotalSeconds() * 1000, (TIMERPROC)TimerProc);
	m_iRetryCount = 0 ;
}

UINT FTPSite::GetTimerID()
{	return m_nTimer ;	}