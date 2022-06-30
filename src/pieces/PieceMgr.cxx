#include "pieces/PieceMgr.hxx"
#include "pieces/BasePiece.hxx"

Pieces::PieceMgr* Pieces::PieceMgr::GetInstance()
{
    static Pieces::PieceMgr* instance = new Pieces::PieceMgr();
    return instance;
}

Pieces::PieceMgr::PieceMgr()
{
}

Pieces::PieceMgr::~PieceMgr()
{
    DestroyPieces();
}

void Pieces::PieceMgr::DestroyPieces()
{
    for (int i = 0; i < m_pieces.size(); ++i)
    {
        delete m_pieces[i];
    }
}
