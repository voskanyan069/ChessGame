#include "pieces/BasePiece.hxx"
#include "chess/Board.hxx"

Pieces::BasePiece::BasePiece(const PieceColor& color, const Position& position)
    : m_pieceChar(" ")
    , m_color(color)
    , m_position(position)
{
}

void Pieces::BasePiece::setPieceChar(const Pieces::PieceColor& color,
            const std::string& white, const std::string& black)
{
    switch (color)
    {
        case Pieces::WHITE:
        {
            m_pieceChar = white;
            break;
        }
        case Pieces::BLACK:
        {
            m_pieceChar = black;
            break;
        }
        default:
        {
            m_pieceChar = " ";
        }
    }
}

const std::string& Pieces::BasePiece::GetPieceChar() const
{
    return m_pieceChar;
}

Pieces::PieceColor Pieces::BasePiece::GetColor() const
{
    return m_color;
}

Pieces::Position Pieces::BasePiece::GetPosition() const
{
    return m_position;
}

void Pieces::BasePiece::GetAvailableMoves(Pieces::Positions& positions)
{
}

void Pieces::BasePiece::Move(const Pieces::Position& position)
{
    for (auto& pos : m_vecAvailableMoves)
    {
        if (pos.x != position.x || pos.y != position.y)
        {
            continue;
        }
        Pieces::BasePiece*** board = Chess::Board::GetInstance()->GetBoard();
        board[position.x][position.y] = std::move(
                board[m_position.x][m_position.y]);
        board[m_position.x][m_position.y] = nullptr;
        m_position.x = position.x;
        m_position.y = position.y;
    }
}
