#include "pieces/BasePiece.hxx"
#include "pieces/Rook.hxx"

Pieces::Rook::Rook(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♖", "♜");
}

void Pieces::Rook::getAvailableMoves(Pieces::Positions& positions) const
{
}
