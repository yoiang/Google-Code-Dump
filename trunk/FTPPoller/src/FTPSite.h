#ifndef __FTPSITE_H__
#define __FTPSITE_H__

#define POLL_OFF 0
#define POLL_HOURLY 1
#define POLL_DAILY 2

#define POLL_NUM_TYPES 3

//#define POLL_DAY_OF_WEEK_AT_TIME 3
//#define POLL_DATE_TIME 4

#include <afx.h>
#include <afxinet.h>

class FTPSite
{
private:
	bool m_bDownload ;
	
	int m_iPolling ;
	CTime m_tPollingTime ;
	UINT m_nTimer ;
	int m_iRetryCount ;

	bool m_bEncrypt ;

	CString m_cstrName ;
	CString m_cstrAddress ;
	CString m_cstrUsername ;
	CString m_cstrPassword ;
	CString m_cstrWildcard ;
	CString m_cstrRemoteDir ;
	CString m_cstrLocalDir ;

	CString m_cstrEncryptUserID ;
	CString m_cstrEncryptSignID ;
	CString m_cstrEncryptPassword ;
	CString m_cstrEncryptPublicRing ;
	CString m_cstrEncryptPrivateRing ;
		
public:
	FTPSite() ;
	~FTPSite() ;

	void SetDownload(bool bSetDownload) ;
	bool GetDownload() ;

	void SetPolling(int iSetPolling) ;
	int GetPolling() ;

	void SetPollingTime(CTime cSetPollingTime) ;
	CTime GetPollingTime() ;

	void SetEncrypt(bool bSetEncrypt) ;
	bool GetEncrypt() ;

	void SetName(CString cstrSetName) ;
	CString GetName() ;
	void SetAddress(CString cstrSetAddress) ;
	CString GetAddress() ;
	void SetUsername(CString cstrSetUsername) ;
	CString GetUsername() ;
	void SetPassword(CString cstrSetPassword) ;
	CString GetPassword() ;
	void SetWildcard(CString cstrSetWildcard) ;
	CString GetWildcard() ;
	void SetRemoteDir(CString cstrSetRemoteDir) ;
	CString GetRemoteDir() ;
	void SetLocalDir(CString cstrSetLocalDir) ;
	CString GetLocalDir() ;

	void SetEncryptUserID(CString cstrSetEncryptUserID) ;
	CString GetEncryptUserID() ;
	void SetEncryptSignID(CString cstrSetEncryptSignID) ;
	CString GetEncryptSignID() ;
	void SetEncryptPassword(CString cstrSetEncryptPassword) ;
	CString GetEncryptPassword() ;
	void SetEncryptPublicRing(CString cstrSetEncryptPublicRing) ;
	CString GetEncryptPublicRing () ;
	void SetEncryptPrivateRing(CString cstrSetEncryptPrivateRing) ;
	CString GetEncryptPrivateRing() ;

	void EncryptFile(CString cstrFilename) ;
	void DecryptFile(CString cstrFilename) ;
	void MoveSendFile(CFtpConnection* pFTPConnect, CString cstrFilename) ;
	void DoTask();
	void SetTaskTimer(bool bRetry) ;
	UINT GetTimerID() ;
} ;

#endif