#include "pieces/BasePiece.hxx"
#include "pieces/King.hxx"

Pieces::King::King(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♔", "♚");
}

void Pieces::King::getAvailableMoves(Pieces::Positions& positions) const
{
}
