#include "pieces/BasePiece.hxx"
#include "pieces/Rook.hxx"
#include "chess/Board.hxx"

Pieces::Rook::Rook(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece("Rook", color, position)
{
    setPieceChar(color, "♖", "♜");
}

void Pieces::Rook::getAvailableMoves(Pieces::Positions& positions) const
{
    Chess::Board* board = Chess::Board::GetInstance();
    int DELTA[2] = {1, -1};
    for (int d = 0; d < 2; ++d)
    {
        for (int i = 0; i < 2; ++i)
        {
            int delta = DELTA[i];
            for (int j = 0; j < 8; ++j)
            {
                int row = (d == 0) ? m_position.x + delta * j : m_position.x;
                int col = (d == 1) ? m_position.y + delta * j : m_position.y;
                Pieces::Position pos(row, col);
                if (pos == m_position)
                {
                    continue;
                }
                if (row < 0 || row > 7 || col < 0 || col > 7)
                {
                    break;
                }
                if (!board->IsFree(pos))
                {
                    if (board->IsEnemy(m_position, pos))
                    {
                        positions.push_back(pos);
                        board->GetPiece(pos)->SetHittable(true);
                    }
                    break;
                }
                positions.push_back(pos);
            }
        }
    }
}
