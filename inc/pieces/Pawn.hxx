#ifndef __PIECES_PAWN_HXX__
#define __PIECES_PAWN_HXX__

#include "pieces/BasePiece.hxx"

namespace Pieces
{
    class Pawn;
};

class Pieces::Pawn : public Pieces::BasePiece
{
public:
    Pawn(const Pieces::PieceColor& color, const Pieces::Position& position);
    ~Pawn() = default;

public:
    void GetAvailableMoves(Pieces::Positions& positions) override;

private:
    void getAvailableMovesWhite(Pieces::Positions& positions) const;
    void getAvailableMovesBlack(Pieces::Positions& positions) const;
};

#endif // __PIECES_PAWN_HXX__
