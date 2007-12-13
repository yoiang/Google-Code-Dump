#include "MarioDSFlipPuzzleBoard.h"

MarioDSFlipPuzzleBoard::MarioDSFlipPuzzleBoard( int iSetWidth, int iSetHeight )
: m_iWidth( 0 ), m_iHeight( 0 ), m_ppSpace( 0 )
{
	if ( iSetWidth < 0)
	{
		iSetWidth = 0;
	}
	if ( iSetHeight < 0 )
	{
		iSetHeight = 0;
	}

	CreateBoard( iSetWidth, iSetHeight );
}

MarioDSFlipPuzzleBoard::~MarioDSFlipPuzzleBoard()
{
	DestroyBoard();
}

void MarioDSFlipPuzzleBoard::CreateBoard( int iSetWidth, int iSetHeight )
{
	DestroyBoard();

	m_iWidth = iSetWidth;
	m_iHeight = iSetHeight;

	m_ppSpace = new bool*[ m_iWidth ];
	for ( int iWidthCount = 0; iWidthCount < m_iWidth; ++iWidthCount )
	{
		m_ppSpace[ iWidthCount ] = new bool[ m_iHeight ];
	}
}

void MarioDSFlipPuzzleBoard::DestroyBoard()
{
	for ( int iWidthCount = 0; iWidthCount < m_iWidth; ++iWidthCount )
	{
		delete [] m_ppSpace[ iWidthCount ];
	}
	delete [] m_ppSpace;

	m_ppSpace = 0;
}

void MarioDSFlipPuzzleBoard::ClearBoard( bool bFace )
{
	for (int iWidthCount = 0; iWidthCount < m_iWidth; ++iWidthCount)
	{
		for (int iHeightCount = 0; iHeightCount < m_iHeight; ++iHeightCount)
		{
			SetFacing( iWidthCount, iHeightCount, bFace );
		}
	}
}

bool MarioDSFlipPuzzleBoard::GetFacing( int iX, int iY ) const
{
	if ( iX >= 0 && iX < m_iWidth && iY >= 0 && iY < m_iHeight )
	{
		return m_ppSpace[ iX ][ iY ];
	}
	return false;
}

void MarioDSFlipPuzzleBoard::SetFacing( int iX, int iY, bool bFace )
{
	if ( iX >= 0 && iX < m_iWidth && iY >= 0 && iY < m_iHeight )
	{
		m_ppSpace[ iX ][ iY ] = bFace;
	}
}

void MarioDSFlipPuzzleBoard::FlipSpace( int iX, int iY )
{
	SetFacing( iX, iY, !GetFacing( iX, iY ) );
}

void MarioDSFlipPuzzleBoard::FlipArea( int iX, int iY )
{
	for ( int iWidthCount = iX - 1; iWidthCount <= iX + 1; ++iWidthCount )
	{
		for ( int iHeightCount = iY - 1; iHeightCount <= iY + 1; ++iHeightCount )
		{
			FlipSpace( iWidthCount, iHeightCount );
		}
	}
}

const MarioDSFlipPuzzleBoard& MarioDSFlipPuzzleBoard::operator =( const MarioDSFlipPuzzleBoard& Assign )
{
	for ( int iWidthSlot = 0; iWidthSlot < m_iWidth; ++iWidthSlot )
	{
		for ( int iHeightSlot = 0; iHeightSlot < m_iHeight; ++iHeightSlot )
		{
			SetFacing( iWidthSlot, iHeightSlot, Assign.GetFacing( iWidthSlot, iHeightSlot ) );
		}
	}
	return *this;
}

bool MarioDSFlipPuzzleBoard::operator ==( const MarioDSFlipPuzzleBoard& Compare )
{
	for ( int iWidthSlot = 0; iWidthSlot < m_iWidth; ++iWidthSlot )
	{
		for ( int iHeightSlot = 0; iHeightSlot < m_iHeight; ++iHeightSlot )
		{
			if ( GetFacing( iWidthSlot, iHeightSlot) != Compare.GetFacing( iWidthSlot, iHeightSlot ) )
			{
				return false;
			}
		}
	}
	return true;
}



