#include "pieces/BasePiece.hxx"
#include "pieces/EmptyPiece.hxx"
#include "utils/Defines.hxx"

Pieces::EmptyPiece::EmptyPiece(const Pieces::Position& position)
    : Pieces::BasePiece("Empty", Pieces::PieceColor::UNDEF, position)
{
    m_pieceChar = GREEN_CONSOLE;
    m_pieceChar += BLINK_TEXT;
    m_pieceChar += "*";
}

void Pieces::EmptyPiece::getAvailableMoves(Pieces::Positions& positions) const
{
}
