#ifndef __PIECES_BASE_PIECE_MGR_HXX__
#define __PIECES_BASE_PIECE_MGR_HXX__

#include "pieces/BasePiece.hxx"

#include <vector>

namespace Pieces
{
    class PieceMgr;
};

class Pieces::PieceMgr
{
public:
    static PieceMgr* GetInstance();
    PieceMgr(PieceMgr const&) = delete;
    ~PieceMgr();
    void operator=(PieceMgr const&) = delete;

private:
    PieceMgr();

public:
    void DestroyPieces();
    template <typename T>
    T* CreatePiece(const Pieces::PieceColor& color,
            const Pieces::Position& position)
    {
        T* piece = new T(color, position);
        m_pieces.push_back(piece);
        return piece;
    }

private:
    std::vector<Pieces::BasePiece*> m_pieces;
};

#endif // __PIECES_BASE_PIECE_MGR_HXX__
