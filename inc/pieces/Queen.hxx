#ifndef __PIECES_QUEEN_HXX__
#define __PIECES_QUEEN_HXX__

#include "pieces/BasePiece.hxx"

namespace Pieces
{
    class Queen;
};

class Pieces::Queen : public Pieces::BasePiece
{
public:
    Queen(const Pieces::PieceColor& color, const Pieces::Position& position);
    ~Queen() = default;

public:
    void GetAvailableMoves(Pieces::Positions& positions) override;
};

#endif // __PIECES_QUEEN_HXX__
