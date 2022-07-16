#include "pieces/BasePiece.hxx"
#include "pieces/Queen.hxx"
#include "pieces/Bishop.hxx"
#include "pieces/Rook.hxx"

Pieces::Queen::Queen(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece("Queen", color, position)
{
    setPieceChar(color, "♕", "♛");
}

void Pieces::Queen::getAvailableMoves(Pieces::Positions& positions) const
{
    Pieces::Bishop bishop(m_color, m_position);
    Pieces::Rook rook(m_color, m_position);
    bishop.GetAvailableMoves(positions);
    rook.GetAvailableMoves(positions);
}
