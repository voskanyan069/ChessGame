#include "pieces/BasePiece.hxx"
#include "pieces/Bishop.hxx"
#include "chess/Board.hxx"

Pieces::Bishop::Bishop(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece("Bishop", color, position)
{
    setPieceChar(color, "♗", "♝");
}

void Pieces::Bishop::getAvailableMoves(Pieces::Positions& positions) const
{
    Chess::Board* board = Chess::Board::GetInstance();
    int X[4] = {-1, 1, 1, -1};
    int Y[4] = {-1, -1, 1, 1};
    for (int i = 0; i < 4; ++i)
    {
        int rowDelta = X[i];
        int colDelta = Y[i];
        for (int j = 0; j < 8; ++j)
        {
            int row = m_position.x + rowDelta * j;
            int col = m_position.y + colDelta * j;
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
