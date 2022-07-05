#include "pieces/BasePiece.hxx"
#include "pieces/Knight.hxx"

Pieces::Knight::Knight(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♘", "♞");
}

Pieces::Position* Pieces::Knight::GetAvailableMoves() const
{
    return nullptr;
}
