#include "pieces/BasePiece.hxx"

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
            m_pieceChar = ' ';
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

Pieces::Position* Pieces::BasePiece::GetAvailableMoves() const
{
    return nullptr;
}
