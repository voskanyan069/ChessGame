#include "pieces/BasePiece.hxx"
#include "pieces/Knight.hxx"

Pieces::Knight::Knight(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♘", "♞");
}

void Pieces::Knight::GetAvailableMoves(Pieces::Positions& positions)
{
}
