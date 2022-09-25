#include "utils/Exception.hxx"
#include "pieces/BasePiece.hxx"
#include "chess/Board.hxx"
#include "chess/GameMgr.hxx"

#include <iostream>

Pieces::BasePiece::BasePiece(const std::string& name,
        const PieceColor& color, const Position& position)
    : m_pieceName(name)
    , m_pieceChar(" ")
    , m_color(color)
    , m_position(position)
    , m_isHittable(false)
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

void Pieces::BasePiece::resetPieceHittableStatus(
        const Pieces::Position& pos) const
{
    Chess::Board* board = Chess::Board::GetInstance();
    if (!board->IsFree(pos))
    {
        board->GetPiece(pos)->SetHittable(false);
    }
}

bool Pieces::BasePiece::comparePositions(const Pieces::Position& pos,
        const Pieces::Position& newPos) const
{
    if (pos.x != newPos.x || pos.y != newPos.y)
    {
        return false;
    }
    return true;
}

bool Pieces::BasePiece::isKingHittable() const
{
    Chess::Board* board = Chess::Board::GetInstance();
    return board->IsKingHittable(board->GetPiece(m_position)->GetColor());
}

bool Pieces::BasePiece::cleanPositionIfEnemy(const Pieces::Position& pos) const
{
    Chess::Board* board = Chess::Board::GetInstance();
    Pieces::BasePiece*** pieces = board->GetBoard();
    if (!board->IsFree(pos))
    {
        if (!board->IsEnemy(m_position, pos))
        {
            return false;
        }
        delete pieces[pos.x][pos.y];
    }
    return true;
}

void Pieces::BasePiece::movePiece(const Pieces::Position& pos)
{
    Chess::Board* board = Chess::Board::GetInstance();
    Pieces::BasePiece*** pieces = board->GetBoard();
    pieces[pos.x][pos.y] = std::move(
            pieces[m_position.x][m_position.y]);
    pieces[m_position.x][m_position.y] = nullptr;
    m_position.x = pos.x;
    m_position.y = pos.y;
}

void Pieces::BasePiece::changeEnemyKingHittableStatus()
{
    Chess::Board* board = Chess::Board::GetInstance();
    Pieces::PieceColor color = Pieces::PieceColor::WHITE;
    if (Pieces::PieceColor::WHITE == GetColor())
    {
        color = Pieces::PieceColor::BLACK;
    }
    //Pieces::Positions positions;
    //GetAvailableMoves(positions);
    bool isHittable = board->IsKingHittable(color);
    //Chess::GameMgr::GetInstance()->SetKingHittable(color, isHittable);
}

bool Pieces::BasePiece::checkMoveResult(bool bResult,
        const std::string& sMsg) const
{
    if (!bResult)
    {
        throw Utils::Exception(sMsg);
    }
}

void Pieces::BasePiece::SetHittable(bool isHittable)
{
    m_isHittable = isHittable;
    if (isHittable)
    {
        m_pieceChar = "\033[31m" + m_pieceChar + "\033[0m";
    }
    else
    {
        m_pieceChar = m_pieceInitialChar;
    }
}

bool Pieces::BasePiece::IsHittable() const
{
    return m_isHittable;
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
        resetPieceHittableStatus(pos);
        if (!comparePositions(pos, position)) continue;
        if (isKingHittable()) checkMoveResult(false, "King is hittable");
        if (!cleanPositionIfEnemy(pos)) continue;
        movePiece(position);
        changeEnemyKingHittableStatus();
        isMoved = true;
    }
    checkMoveResult(isMoved, "Incorrect position");
}
