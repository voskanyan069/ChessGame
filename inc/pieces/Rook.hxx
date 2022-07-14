#ifndef __PIECES_ROOK_HXX__
#define __PIECES_ROOK_HXX__

#include "pieces/BasePiece.hxx"

namespace Pieces
{
    class Rook;
};

class Pieces::Rook : public Pieces::BasePiece
{
public:
    Rook(const Pieces::PieceColor& color, const Pieces::Position& position);
    ~Rook() = default;

protected:
    void getAvailableMoves(Pieces::Positions& positions) const override;
};

#endif // __PIECES_ROOK_HXX__
