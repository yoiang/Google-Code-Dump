#ifndef INCLUDED_MarioDSFlipPuzzleBoard
#define INCLUDED_MarioDSFlipPuzzleBoard

class MarioDSFlipPuzzleBoard
{
public:
	MarioDSFlipPuzzleBoard( int iSetWidth = 0, int iSetHeight = 0 );
	~MarioDSFlipPuzzleBoard();

	void CreateBoard( int iSetWidth, int iSetHeight );
	void DestroyBoard();
	void ClearBoard( bool bFace = false );

	int GetWidth() const { return m_iWidth; }
	int GetHeight() const { return m_iHeight; }

	bool GetFacing( int iX, int iY ) const;
	void SetFacing( int iX, int iY, bool bFace );
	void FlipSpace( int iX, int iY );
	void FlipArea( int iX, int iY );

	const MarioDSFlipPuzzleBoard& operator =( const MarioDSFlipPuzzleBoard& Assign );
	bool operator ==( const MarioDSFlipPuzzleBoard& Compare );

protected:
	int m_iWidth, m_iHeight;
	bool** m_ppSpace;
};

#endif