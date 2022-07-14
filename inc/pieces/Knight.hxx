#ifndef __PIECES_KNIGHT_HXX__
#define __PIECES_KNIGHT_HXX__

#include "pieces/BasePiece.hxx"

namespace Pieces
{
    class Knight;
};

class Pieces::Knight : public Pieces::BasePiece
{
public:
    Knight(const Pieces::PieceColor& color, const Pieces::Position& position);
    ~Knight() = default;

protected:
    void getAvailableMoves(Pieces::Positions& positions) const override;
};

#endif // __PIECES_KNIGHT_HXX__
