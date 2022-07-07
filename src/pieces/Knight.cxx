#include "pieces/BasePiece.hxx"
#include "pieces/Knight.hxx"

Pieces::Knight::Knight(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♘", "♞");
}

#include <iostream>

void Pieces::Knight::getAvailableMoves(Pieces::Positions& positions) const
{
    int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    for (int i = 0; i < 8; i++)
    {
        positions.emplace_back(m_position.x + X[i], m_position.y + Y[i]);
    }
}

void Pieces::Knight::GetAvailableMoves(Pieces::Positions& positions)
{
    getAvailableMoves(positions);
    m_vecAvailableMoves.clear();
    m_vecAvailableMoves.insert(m_vecAvailableMoves.end(), positions.begin(),
            positions.end());
}
