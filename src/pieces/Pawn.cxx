#include "pieces/BasePiece.hxx"
#include "pieces/Pawn.hxx"

Pieces::Pawn::Pawn(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♙", "♟");
}

Pieces::Position* Pieces::Pawn::GetAvailableMoves() const
{
    return nullptr;
}
