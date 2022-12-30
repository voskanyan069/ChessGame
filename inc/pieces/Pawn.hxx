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

protected:
    void getAvailableMoves(Pieces::Positions& positions) const override;

private:
    void getAvailableMovesWhite(Pieces::Positions& positions) const;
    void getAvailableMovesBlack(Pieces::Positions& positions) const;
    void checkForNextMoves(Pieces::Positions& positions) const;
    void setHittableEnemies(Pieces::Positions& positions,
            Pieces::Position& rightPos, Pieces::Position& leftPos) const;

private:
    int m_startLine;
    int m_endLine;
};

#endif // __PIECES_PAWN_HXX__
