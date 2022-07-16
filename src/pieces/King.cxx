#include "pieces/BasePiece.hxx"
#include "pieces/King.hxx"
#include "chess/Board.hxx"

Pieces::King::King(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece("King", color, position)
{
    setPieceChar(color, "♔", "♚");
}

void Pieces::King::getAvailableMoves(Pieces::Positions& positions) const
{
    Chess::Board* board = Chess::Board::GetInstance();
    for (int row = m_position.x - 1; row <= m_position.x + 1; ++row)
    {
        for (int col = m_position.y - 1; col <= m_position.y + 1; ++col)
        {
            Pieces::Position pos(row, col);
            if (row < 0 || row > 7 || col < 0 || col > 7 || pos == m_position)
            {
                continue;
            }
            if (!board->IsFree(pos))
            {
                if (board->IsEnemy(m_position, pos))
                {
                    positions.push_back(pos);
                    board->GetPiece(pos)->SetHittable(true);
                }
            }
            positions.push_back(pos);
        }
    }
}
