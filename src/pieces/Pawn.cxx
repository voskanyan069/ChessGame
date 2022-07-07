#include "pieces/PieceMgr.hxx"
#include "pieces/BasePiece.hxx"
#include "pieces/Pawn.hxx"
#include "chess/Board.hxx"

#include <algorithm>

Pieces::Pawn::Pawn(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♙", "♟");
}

void Pieces::Pawn::getAvailableMovesWhite(Pieces::Positions& positions) const
{
    if (m_position.x == 1)
    {
        for (int i = 1; i < 3; ++i)
        {
            positions.emplace_back(m_position.x + i, m_position.y);
        }
    }
    else if (m_position.x < 8)
    {
        positions.emplace_back(m_position.x + 1, m_position.y);
    }
}

void Pieces::Pawn::getAvailableMovesBlack(Pieces::Positions& positions) const
{
    if (m_position.x == 6)
    {
        for (int i = 1; i < 3; ++i)
        {
            positions.emplace_back(m_position.x - i, m_position.y);
        }
    }
    else if (m_position.x > 0)
    {
        positions.emplace_back(m_position.x - 1, m_position.y);
    }
}

void Pieces::Pawn::GetAvailableMoves(Pieces::Positions& positions)
{
    if (m_color == Pieces::PieceColor::WHITE)
    {
        getAvailableMovesWhite(positions);
    }
    else
    {
        getAvailableMovesBlack(positions);
    }
    m_vecAvailableMoves.clear();
    m_vecAvailableMoves.insert(m_vecAvailableMoves.end(), positions.begin(),
            positions.end());
}
