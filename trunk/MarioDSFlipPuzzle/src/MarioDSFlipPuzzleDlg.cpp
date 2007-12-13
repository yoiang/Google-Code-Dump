#include "MarioDSFlipPuzzle.h"
#include "MarioDSFlipPuzzleDlg.h"

CMarioDSFlipPuzzleDlg::CMarioDSFlipPuzzleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMarioDSFlipPuzzleDlg::IDD, pParent),
	m_pBefore( 0 ), m_pAfter( 0 ), m_pWorking( 0 ), m_bChanging( false )
{
	//{{AFX_DATA_INIT(CMarioDSFlipPuzzleDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pBefore = new MarioDSFlipPuzzleBoard();
	m_pAfter = new MarioDSFlipPuzzleBoard();
	m_pWorking = new MarioDSFlipPuzzleBoard();
}

CMarioDSFlipPuzzleDlg::~CMarioDSFlipPuzzleDlg()
{
	delete m_pBefore;
	delete m_pAfter;
	delete m_pWorking;
}

void CMarioDSFlipPuzzleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMarioDSFlipPuzzleDlg)
	DDX_Control(pDX, IDCS_STEPSCOUNT, m_csStepsCount);
	DDX_Control(pDX, IDCS_STATUS, m_cgMatchingArea);
	DDX_Control(pDX, IDCC_LINKDIMENSIONS, m_ccLinkDimensions);
	DDX_Control(pDX, IDCG_WORKING, m_cgWorkingArea);
	DDX_Control(pDX, IDCG_BEFORE, m_cgBeforeArea);
	DDX_Control(pDX, IDCG_AFTER, m_cgAfterArea);
	DDX_Control(pDX, IDCE_WIDTHVALUE, m_ceWidthValue);
	DDX_Control(pDX, IDCE_HEIGHTVALUE, m_ceHeightValue);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMarioDSFlipPuzzleDlg, CDialog)
	//{{AFX_MSG_MAP(CMarioDSFlipPuzzleDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDCE_WIDTHVALUE, OnChangeWidthValue)
	ON_EN_CHANGE(IDCE_HEIGHTVALUE, OnChangeHeightValue)
	ON_BN_CLICKED(IDCC_LINKDIMENSIONS, OnClickLinkDimensions)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDCB_SETTOBEFORE, OnClickSetToBefore)
	ON_BN_CLICKED(IDCB_UNDO, OnClickUndo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMarioDSFlipPuzzleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_ceWidthValue.SetWindowText( "0" );
	m_ceHeightValue.SetWindowText( "0" );
	m_ccLinkDimensions.SetCheck( 1 );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMarioDSFlipPuzzleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

HCURSOR CMarioDSFlipPuzzleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMarioDSFlipPuzzleDlg::OnChangeWidthValue() 
{
	if ( m_bChanging ) return;
	m_bChanging = true;
	if ( m_ccLinkDimensions.GetCheck() == 1 )
	{
		char szBuffer[ 256 ];
		m_ceWidthValue.GetWindowText( szBuffer, 256 );
		m_ceHeightValue.SetWindowText( szBuffer );
	}
	UpdateBoardSizes();
	UpdateDialogSize();
	DisplayBoards();
	m_bChanging = false;
}

void CMarioDSFlipPuzzleDlg::OnChangeHeightValue() 
{
	if ( m_bChanging ) return;
	m_bChanging = true;
	if ( m_ccLinkDimensions.GetCheck() == 1 )
	{
		char szBuffer[ 256 ];
		m_ceHeightValue.GetWindowText( szBuffer, 256 );
		m_ceWidthValue.SetWindowText( szBuffer );
	}
	UpdateBoardSizes();
	UpdateDialogSize();
	DisplayBoards();
	m_bChanging = false;
}

void CMarioDSFlipPuzzleDlg::OnClickLinkDimensions() 
{
	m_bChanging = true;
	if ( m_ccLinkDimensions.GetCheck() == 1 )
	{
		char szBuffer[ 256 ];
		m_ceWidthValue.GetWindowText( szBuffer, 256 );
		m_ceHeightValue.SetWindowText( szBuffer );
	
		UpdateBoardSizes();
		UpdateDialogSize();
		DisplayBoards();
	}
	m_bChanging = false;	
}


void CMarioDSFlipPuzzleDlg::OnLButtonDown( UINT nFlags, CPoint point ) 
{
	if ( point.y >= m_BeforePlacement.rcNormalPosition.top )
	{
		if ( IsWithin( &m_BeforePlacement, &point ) )
		{
			int iXSpace, iYSpace;
			if ( FindSpace( &m_BeforePlacement, &point, iXSpace, iYSpace ) )
			{
				m_pBefore->FlipSpace( iXSpace, iYSpace );
			}
			DisplaySpace( m_BeforePlacement.rcNormalPosition.left + IMAGE_LEFT_SPACING, m_BeforePlacement.rcNormalPosition.top + IMAGE_TOP_SPACING, iXSpace, iYSpace, m_pBefore->GetFacing( iXSpace, iYSpace ) );
		} else if ( IsWithin( &m_AfterPlacement, &point ) )
		{
			int iXSpace, iYSpace;
			if ( FindSpace( &m_AfterPlacement, &point, iXSpace, iYSpace ) )
			{
				m_pAfter->FlipSpace( iXSpace, iYSpace );
			}
			DisplaySpace( m_AfterPlacement.rcNormalPosition.left + IMAGE_LEFT_SPACING, m_AfterPlacement.rcNormalPosition.top + IMAGE_TOP_SPACING, iXSpace, iYSpace, m_pAfter->GetFacing( iXSpace, iYSpace ) );
			UpdateMatchingStatus();
		} else if ( IsWithin( &m_WorkingPlacement, &point ) )
		{
			int iXSpace, iYSpace;
			if ( FindSpace( &m_WorkingPlacement, &point, iXSpace, iYSpace ) )
			{
				m_pWorking->FlipArea( iXSpace, iYSpace );
			}	
			DisplayBoard( m_pWorking, m_WorkingPlacement.rcNormalPosition.left + IMAGE_LEFT_SPACING, m_WorkingPlacement.rcNormalPosition.top + IMAGE_TOP_SPACING );
			UpdateMatchingStatus();

			m_vSteps.push_back( CPoint( iXSpace, iYSpace ) );
			UpdateStepsCount();
		}
	} else
	{
		CDialog::OnLButtonDown(nFlags, point);
	}
}

void CMarioDSFlipPuzzleDlg::OnClickSetToBefore() 
{
	*m_pWorking = *m_pBefore;
	UpdateMatchingStatus();
	DisplayBoard( m_pWorking, m_WorkingPlacement.rcNormalPosition.left + IMAGE_LEFT_SPACING, m_WorkingPlacement.rcNormalPosition.top + IMAGE_TOP_SPACING );

	m_vSteps.clear();
	UpdateStepsCount();
}

void CMarioDSFlipPuzzleDlg::OnClickUndo() 
{
	if ( m_vSteps.size() > 0 )
	{
		m_pWorking->FlipArea( m_vSteps[ m_vSteps.size() - 1 ].x, m_vSteps[ m_vSteps.size() - 1 ].y );
		DisplayBoard( m_pWorking, m_WorkingPlacement.rcNormalPosition.left + IMAGE_LEFT_SPACING, m_WorkingPlacement.rcNormalPosition.top + IMAGE_TOP_SPACING );
		UpdateMatchingStatus();

		m_vSteps.pop_back();
		UpdateStepsCount();
	}
}

void CMarioDSFlipPuzzleDlg::OnOK() {}

void CMarioDSFlipPuzzleDlg::UpdateBoardSizes()
{
	char szBuffer[ 256 ];
	m_ceWidthValue.GetWindowText( szBuffer, 256 );
	int iWidthValue = atoi( szBuffer );
	m_ceHeightValue.GetWindowText( szBuffer, 256 );
	int iHeightValue = atoi( szBuffer );

	m_pBefore->CreateBoard( iWidthValue, iHeightValue );
	m_pBefore->ClearBoard();

	m_pAfter->CreateBoard( iWidthValue, iHeightValue );
	m_pAfter->ClearBoard();

	m_pWorking->CreateBoard( iWidthValue, iHeightValue );
	m_pWorking->ClearBoard();

	m_cgMatchingArea.SetWindowText( "Matching!" );
}

void CMarioDSFlipPuzzleDlg::UpdateDialogSize()
{
	char szBuffer[ 256 ];
	m_ceWidthValue.GetWindowText( szBuffer, 256 );
	int iWidthValue = atoi( szBuffer );
	m_ceHeightValue.GetWindowText( szBuffer, 256 );
	int iHeightValue = atoi( szBuffer );

	m_cgBeforeArea.GetWindowPlacement( &m_BeforePlacement );
	m_BeforePlacement.rcNormalPosition.right = IMAGE_LEFT_SPACING + iWidthValue * ( IMAGE_WIDTH + IMAGE_WIDTH_SPACING ) + m_BeforePlacement.rcNormalPosition.left;
	m_BeforePlacement.rcNormalPosition.bottom = IMAGE_TOP_SPACING + iHeightValue * ( IMAGE_HEIGHT + IMAGE_HEIGHT_SPACING ) + m_BeforePlacement.rcNormalPosition.top;
	m_cgBeforeArea.SetWindowPlacement( &m_BeforePlacement );

	WINDOWPLACEMENT tempPlacement;
	m_cgMatchingArea.GetWindowPlacement( &tempPlacement );
	tempPlacement.rcNormalPosition.left = m_BeforePlacement.rcNormalPosition.right + m_BeforePlacement.rcNormalPosition.left;
	tempPlacement.rcNormalPosition.bottom = m_BeforePlacement.rcNormalPosition.bottom + m_BeforePlacement.rcNormalPosition.left;

	m_AfterPlacement.rcNormalPosition.left = tempPlacement.rcNormalPosition.left + m_BeforePlacement.rcNormalPosition.left;
	m_AfterPlacement.rcNormalPosition.top = m_BeforePlacement.rcNormalPosition.top;
	m_AfterPlacement.rcNormalPosition.right = m_AfterPlacement.rcNormalPosition.left + IMAGE_LEFT_SPACING + iWidthValue * ( IMAGE_WIDTH + IMAGE_WIDTH_SPACING );
	m_AfterPlacement.rcNormalPosition.bottom = m_BeforePlacement.rcNormalPosition.bottom;
	m_cgAfterArea.SetWindowPlacement( &m_AfterPlacement );

	m_WorkingPlacement.rcNormalPosition.left = m_AfterPlacement.rcNormalPosition.right + m_BeforePlacement.rcNormalPosition.left;
	m_WorkingPlacement.rcNormalPosition.top = m_BeforePlacement.rcNormalPosition.top;
	m_WorkingPlacement.rcNormalPosition.right = m_WorkingPlacement.rcNormalPosition.left + IMAGE_LEFT_SPACING + iWidthValue * ( IMAGE_WIDTH + IMAGE_WIDTH_SPACING );
	m_WorkingPlacement.rcNormalPosition.bottom = m_BeforePlacement.rcNormalPosition.bottom;
	m_cgWorkingArea.SetWindowPlacement( &m_WorkingPlacement );

	tempPlacement.rcNormalPosition.right = m_WorkingPlacement.rcNormalPosition.right + m_BeforePlacement.rcNormalPosition.left;
	m_cgMatchingArea.SetWindowPlacement( &tempPlacement );

	int iWindowWidth = tempPlacement.rcNormalPosition.right + m_BeforePlacement.rcNormalPosition.left + 6;
	int iWindowHeight = tempPlacement.rcNormalPosition.bottom + m_BeforePlacement.rcNormalPosition.left + 23;
	if ( iWindowWidth < 278 || iWidthValue == 0 || iHeightValue == 0 )
	{
		iWindowWidth = 278;
	}

	if ( iWindowHeight < 95 || iWidthValue == 0 || iHeightValue == 0 )
	{
		iWindowHeight = 95;
	}

	CWnd::GetWindowRect( &tempPlacement.rcNormalPosition );
	tempPlacement.rcNormalPosition.right = tempPlacement.rcNormalPosition.left + iWindowWidth;
	tempPlacement.rcNormalPosition.bottom = tempPlacement.rcNormalPosition.top + iWindowHeight;
	SetWindowPlacement( &tempPlacement );

	RedrawWindow();
}

void CMarioDSFlipPuzzleDlg::UpdateMatchingStatus()
{
	if ( *m_pAfter == *m_pWorking )
	{
		m_cgMatchingArea.SetWindowText( "Matching!" );
	} else
	{
		m_cgMatchingArea.SetWindowText( "Different" );
	}
}

void CMarioDSFlipPuzzleDlg::UpdateStepsCount()
{
	char szBuffer[256];
	sprintf( szBuffer, "Steps: %i", (int)m_vSteps.size() );
	m_csStepsCount.SetWindowText( szBuffer );
}

void CMarioDSFlipPuzzleDlg::DisplayBoards()
{
	DisplayBoard( m_pBefore, m_BeforePlacement.rcNormalPosition.left + IMAGE_LEFT_SPACING, m_BeforePlacement.rcNormalPosition.top + IMAGE_TOP_SPACING );

	DisplayBoard( m_pAfter, m_AfterPlacement.rcNormalPosition.left + IMAGE_LEFT_SPACING, m_AfterPlacement.rcNormalPosition.top + IMAGE_TOP_SPACING );

	DisplayBoard( m_pWorking, m_WorkingPlacement.rcNormalPosition.left + IMAGE_LEFT_SPACING, m_WorkingPlacement.rcNormalPosition.top + IMAGE_TOP_SPACING );
}

void CMarioDSFlipPuzzleDlg::DisplayBoard( MarioDSFlipPuzzleBoard *pDisplay, int iX, int iY )
{
	for ( int iSpaceWidth = 0; iSpaceWidth < pDisplay->GetWidth(); ++iSpaceWidth)
	{
		for ( int iSpaceHeight = 0; iSpaceHeight < pDisplay->GetHeight(); ++iSpaceHeight)
		{
			DisplaySpace( iX, iY, iSpaceWidth, iSpaceHeight, pDisplay->GetFacing( iSpaceWidth, iSpaceHeight ) );
		}
	}
}

void CMarioDSFlipPuzzleDlg::DisplaySpace( int iX, int iY, int iSpaceX, int iSpaceY, bool bFacing )
{
	DisplaySpace( iX + iSpaceX * ( IMAGE_WIDTH + IMAGE_WIDTH_SPACING ), iY + iSpaceY * ( IMAGE_HEIGHT + IMAGE_HEIGHT_SPACING ), bFacing );
}

void CMarioDSFlipPuzzleDlg::DisplaySpace( int iX, int iY, bool bFacing )
{
	CDC *WindowCDC = GetDC();
	for ( int iPixelWidth = 0; iPixelWidth < IMAGE_WIDTH; ++iPixelWidth )
	{
		for( int iPixelHeight = 0; iPixelHeight < IMAGE_HEIGHT; ++iPixelHeight )
		{
			if ( bFacing )
			{
				WindowCDC->SetPixel( iX + iPixelWidth, iY + iPixelHeight, RGB( 255, 0, 255 ) );
			} else
			{
				WindowCDC->SetPixel( iX + iPixelWidth, iY + iPixelHeight, RGB( 0, 255, 255 ) );
			}
		}
	}
}

bool CMarioDSFlipPuzzleDlg::IsWithin( WINDOWPLACEMENT *pArea, CPoint *pPoint )
{
	if ( pArea->rcNormalPosition.left > pPoint->x ||
		 pArea->rcNormalPosition.right < pPoint->x ||
		 pArea->rcNormalPosition.top > pPoint->y ||
		 pArea->rcNormalPosition.bottom < pPoint->y )
	{
		return false;
	}
	return true;
}

bool CMarioDSFlipPuzzleDlg::FindSpace( WINDOWPLACEMENT *pArea, CPoint *pPoint, int &iXSpace, int &iYSpace )
{
	int iRelativeX = pPoint->x - pArea->rcNormalPosition.left - IMAGE_LEFT_SPACING;
	int iRelativeY = pPoint->y - pArea->rcNormalPosition.top - IMAGE_TOP_SPACING;
	iXSpace = iRelativeX / ( IMAGE_WIDTH + IMAGE_WIDTH_SPACING );
	iYSpace = iRelativeY / ( IMAGE_HEIGHT + IMAGE_HEIGHT_SPACING );
	return true;
}
