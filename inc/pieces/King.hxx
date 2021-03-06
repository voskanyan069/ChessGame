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

protected:
    void getAvailableMoves(Pieces::Positions& positions) const override;
};

#endif // __PIECES_KING_HXX__
