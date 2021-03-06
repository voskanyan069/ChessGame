#include "pieces/BasePiece.hxx"
#include "pieces/EmptyPiece.hxx"

Pieces::EmptyPiece::EmptyPiece(const Pieces::Position& position)
    : Pieces::BasePiece("Empty", Pieces::PieceColor::UNDEF, position)
{
    m_pieceChar = "\033[32m*\033[0m";
}

void Pieces::EmptyPiece::getAvailableMoves(Pieces::Positions& positions) const
{
}
