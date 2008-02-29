// 1337 Sp34KDlg.cpp : implementation file
//

#include "stdafx.h"
#include "1337 Sp34K.h"
#include "1337 Sp34KDlg.h"
#include <stdlib.h>  
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct Conversion
{
 char *pszFrom ;
 char *pszTo ;
 double rProbability ;
} ConversionTable [] =
{ 
 {"elite", "1337",   1.00},
 {"porn",  "pron",   1.00},
 {"ck",    "xor",    1.00}, 
 {"you",   "joo",    1.00}, 
 {"s ",     "z",     1.00}, 

 {"a",     "4",      0.66}, 
 {"c",     "(",      0.33}, 
 {"c",     "{",      0.33}, 
 {"d",     "|)",     0.33},
 {"e",     "3",      0.66},
 {"e",     "@",      0.33},
 {"f",     "ph",     0.50},
 {"g",     "9",      0.50},
 {"h",     "|-|",    0.33},
 {"i",     "!",      0.66},
 {"j",     "_|",     0.33},
 {"k",     "|<",     0.50},
 {"m",     "|\\/|",  0.66}, 
 {"n",     "|\\|",   0.66},
 {"l",     "1",      0.66},
 {"l",     "£",      0.66},
 {"l",     "|_",     0.50},
 {"o",     "0",      0.66},
 {"o",     "*",      0.50},
 {"r",     "|2",     0.50},
 {"s",     "$",      0.50},
 {"s",     "5",      0.50},
 {"s",     "§",      0.50},
 {"t",     "7",      0.66},
 {"t",     "+",      0.66},
 {"u",     "\\_/",   0.50},
 {"v",     "\\/",    0.66},
 {"w",     "\\/\\/", 0.66},
 {"w",     "|/\\|",  0.33},
 {"x",     "><",     0.50},
 {"y",     "¥",      0.50},
 {"y",     "'/",     0.50},

 {"ph",    "f",      1.00},

 {NULL,    NULL,     0.00}
} ;

void getword(CString cstrNon1337, int &iStart, CString &cstrWord);
void makeleet(CString cstrNon1337, CString &cstr1337);            //convert the word
void ian_is_a_loser(int,float);   //yeah, its true
void expand (char[],int,int);     //make the word longer so extra characters can be added in the middle
void compress (char[],int,int);   //remove a letter from the word

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy1337Sp34KDlg dialog

CMy1337Sp34KDlg::CMy1337Sp34KDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy1337Sp34KDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy1337Sp34KDlg)
	m_cstrNon1337 = _T("");
	m_cstr1337 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1337Sp34KDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy1337Sp34KDlg)
	DDX_Text(pDX, IDE_NON1337, m_cstrNon1337);
	DDX_Text(pDX, IDE_1337, m_cstr1337);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy1337Sp34KDlg, CDialog)
	//{{AFX_MSG_MAP(CMy1337Sp34KDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_GENERATE, OnGenerate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy1337Sp34KDlg message handlers

BOOL CMy1337Sp34KDlg::OnInitDialog()
{
 CDialog::OnInitDialog();

 // Add "About..." menu item to system menu.

 // IDM_ABOUTBOX must be in the system command range.
 ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
 ASSERT(IDM_ABOUTBOX < 0xF000);

 CMenu* pSysMenu = GetSystemMenu(FALSE);
 if (pSysMenu != NULL)
 {
  CString strAboutMenu;
  strAboutMenu.LoadString(IDS_ABOUTBOX);
  if (!strAboutMenu.IsEmpty())
  {
   pSysMenu->AppendMenu(MF_SEPARATOR);
   pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
  }
 }

 // Set the icon for this dialog.  The framework does this automatically
 //  when the application's main window is not a dialog
 SetIcon(m_hIcon, TRUE);			// Set big icon
 SetIcon(m_hIcon, FALSE);		// Set small icon
	
 return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy1337Sp34KDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy1337Sp34KDlg::OnPaint() 
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
HCURSOR CMy1337Sp34KDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy1337Sp34KDlg::OnGenerate() 
{
 UpdateData(TRUE) ;

 CString cstrNon1337Word ;
 CString cstr1337Word ;
 int iStart = 0 ;
 m_cstr1337 = "" ;

 while(iStart < m_cstrNon1337.GetLength())
 {
  getword (m_cstrNon1337, iStart, cstrNon1337Word);

  makeleet(cstrNon1337Word, cstr1337Word);

  m_cstr1337 += cstr1337Word ;
  if (iStart < m_cstrNon1337.GetLength())
  {
   m_cstr1337 += m_cstrNon1337[iStart] ;
  }
  iStart ++ ;
 } 

 UpdateData(FALSE) ;
}

bool CmpConv(CString cstrCompare, int iStart, CString cstrCompareTo)
{
 int iCompareToLength = cstrCompareTo.GetLength() ;
 for (int iTrav = 0 ; iStart + iTrav < cstrCompare.GetLength() && iTrav < iCompareToLength ; iTrav ++)
 {
  if (toupper(cstrCompare[iStart + iTrav]) != toupper(cstrCompareTo[iTrav])) return false ;
 }

 if (iTrav != iCompareToLength) 
 {
  if (cstrCompareTo[iTrav] == ' ') return true ;
  return false ;
 }

 return true ;
}

bool CheckChance(double dProbability)
{
 if (double(rand()) / double(RAND_MAX) <= dProbability) return true ;
 return false ;
}

void makeleet(CString cstrNon1337, CString &cstr1337)
{
 srand(GetTickCount());
	
 int iN = 0 ;
 int iTrav ;
 int iAddToN ;

 cstr1337 = "" ;

 while (iN < cstrNon1337.GetLength())
 {
  iTrav = 0 ;

  while (ConversionTable[iTrav].pszFrom != NULL)
  {
   if (CmpConv(cstrNon1337, iN, ConversionTable[iTrav].pszFrom) && 
       CheckChance(ConversionTable[iTrav].rProbability))
   {
	cstr1337 += ConversionTable[iTrav].pszTo ;
	iAddToN = strlen(ConversionTable[iTrav].pszFrom) ;
    break ;
   }
   iTrav ++ ;
  }
  if (ConversionTable[iTrav].pszFrom == NULL)
  {
   cstr1337 += cstrNon1337[iN] ;
   iAddToN = 1 ;
  }
  iN += iAddToN ;
 }
 for (iTrav = 0; iTrav < cstr1337.GetLength() ; iTrav ++)
 {
  if (cstr1337[iTrav] >= 'A' && cstr1337[iTrav] <= 'Z')
  {
   if (CheckChance(0.50))
   {
    cstr1337.SetAt(iTrav, cstr1337[iTrav] + 32) ;
   }
  } else if (cstr1337[iTrav] >= 'a' && cstr1337[iTrav] <= 'z')
  {
   if (CheckChance(0.50))
   {
    cstr1337.SetAt(iTrav, cstr1337[iTrav] - 32) ;
   }
  }
 }
}

void getword(CString cstrNon1337, int &iStart, CString &cstrNon1337Word)
{
 cstrNon1337Word = "" ;
 while (iStart < cstrNon1337.GetLength() && 
        IsCharAlphaNumeric(cstrNon1337[iStart]))
 {
  cstrNon1337Word += cstrNon1337[iStart] ;
  iStart ++ ;
 }
}

void CMy1337Sp34KDlg::OnClose() 
{
 CDialog::OnClose();
}

void CMy1337Sp34KDlg::OnOK() 
{
 CDialog::OnOK();
}

void CMy1337Sp34KDlg::OnCancel() 
{
 CDialog::OnCancel();
}
