#include "pieces/BasePiece.hxx"
#include "pieces/Bishop.hxx"

Pieces::Bishop::Bishop(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♗", "♝");
}

Pieces::Position* Pieces::Bishop::GetAvailableMoves() const
{
    return nullptr;
}
