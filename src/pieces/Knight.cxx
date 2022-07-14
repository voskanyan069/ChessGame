#include "pieces/BasePiece.hxx"
#include "pieces/Knight.hxx"
#include "chess/Board.hxx"

Pieces::Knight::Knight(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece(color, position)
{
    setPieceChar(color, "♘", "♞");
}

void Pieces::Knight::getAvailableMoves(Pieces::Positions& positions) const
{
    Chess::Board* board = Chess::Board::GetInstance();
    int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    for (int i = 0; i < 8; ++i)
    {
        if (m_position.x + X[i] < 0 || m_position.x + X[i] > 7
                || m_position.y + Y[i] < 0 || m_position.y + Y[i] > 7)
        {
            continue;
        }
        Pieces::Position pos(m_position.x + X[i], m_position.y + Y[i]);
        if (!board->IsFree(pos) && board->IsEnemy(m_position, pos))
        {
            board->GetPiece(pos)->SetHittable(true);
        }
        positions.push_back(pos);
    }
}
