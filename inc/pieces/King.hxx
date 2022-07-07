#ifndef __PIECES_KING_HXX__
#define __PIECES_KING_HXX__

#include "pieces/BasePiece.hxx"

namespace Pieces
{
    class King;
};

class Pieces::King : public Pieces::BasePiece
{
public:
    King(const Pieces::PieceColor& color, const Pieces::Position& position);
    ~King() = default;

public:
    void GetAvailableMoves(Pieces::Positions& positions) override;
};

#endif // __PIECES_KING_HXX__
