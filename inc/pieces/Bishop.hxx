#ifndef __PIECES_BISHOP_HXX__
#define __PIECES_BISHOP_HXX__

#include "pieces/BasePiece.hxx"

namespace Pieces
{
    class Bishop;
};

class Pieces::Bishop : public Pieces::BasePiece
{
public:
    Bishop(const Pieces::PieceColor& color, const Pieces::Position& position);
    ~Bishop() = default;

protected:
    void getAvailableMoves(Pieces::Positions& positions) const override;
};

#endif // __PIECES_BISHOP_HXX__
