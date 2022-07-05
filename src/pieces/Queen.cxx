#include "pieces/BasePiece.hxx"
#include "pieces/Queen.hxx"

Pieces::Queen::Queen(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♕", "♛");
}

Pieces::Position* Pieces::Queen::GetAvailableMoves() const
{
    return nullptr;
}
