#include "utils/Exception.hxx"
#include "pieces/BasePiece.hxx"
#include "chess/Board.hxx"

Pieces::BasePiece::BasePiece(const std::string& name,
        const PieceColor& color, const Position& position)
    : m_pieceName(name)
    , m_pieceChar(" ")
    , m_color(color)
    , m_position(position)
{
}

void Pieces::BasePiece::getAvailableMoves(Pieces::Positions& positions) const
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
    m_pieceInitialChar = m_pieceChar;
}

void Pieces::BasePiece::SetHittable(bool isHittable)
{
    if (isHittable)
    {
        m_pieceChar = "\033[31m" + m_pieceChar + "\033[0m";
    }
    else
    {
        m_pieceChar = m_pieceInitialChar;
    }
}

const std::string& Pieces::BasePiece::GetPieceName() const
{
    return m_pieceName;
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
    if (m_color == Pieces::PieceColor::UNDEF)
    {
        throw Utils::Exception("Empty position");
    }
    getAvailableMoves(positions);
    m_vecAvailableMoves.clear();
    m_vecAvailableMoves.insert(m_vecAvailableMoves.end(), positions.begin(),
            positions.end());
}

void Pieces::BasePiece::Move(const Pieces::Position& position)
{
    bool isMoved = false;
    Chess::Board* board = Chess::Board::GetInstance();
    Pieces::BasePiece*** pieces = board->GetBoard();
    for (auto& pos : m_vecAvailableMoves)
    {
        if (!board->IsFree(pos))
        {
            board->GetPiece(pos)->SetHittable(false);
        }
        if (pos.x != position.x || pos.y != position.y)
        {
            continue;
        }
        if (!board->IsFree(pos))
        {
            if (!board->IsEnemy(m_position, pos))
            {
                continue;
            }
            delete pieces[pos.x][pos.y];
        }
        pieces[position.x][position.y] = std::move(
                pieces[m_position.x][m_position.y]);
        pieces[m_position.x][m_position.y] = nullptr;
        m_position.x = position.x;
        m_position.y = position.y;
        isMoved = true;
    }
    if (!isMoved)
    {
        throw Utils::Exception("Incorrect position");
    }
}
