#include "pieces/BasePiece.hxx"
#include "pieces/King.hxx"

Pieces::King::King(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♔", "♚");
}

Pieces::Position* Pieces::King::GetAvailableMoves() const
{
    return nullptr;
}
