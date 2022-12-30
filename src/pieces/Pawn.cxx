/*
#include "pieces/PieceMgr.hxx"
#include "pieces/BasePiece.hxx"
#include "pieces/Pawn.hxx"
#include "chess/Board.hxx"

#include <algorithm>

Pieces::Pawn::Pawn(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece("Pawn", color, position)
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

void Pieces::Pawn::getAvailableMoves(Pieces::Positions& positions) const
{
    if (m_color == Pieces::PieceColor::WHITE)
    {
        getAvailableMovesWhite(positions);
    }
    else
    {
        getAvailableMovesBlack(positions);
    }
}
*/


#include "pieces/PieceMgr.hxx"
#include "pieces/BasePiece.hxx"
#include "pieces/Pawn.hxx"
#include "chess/Board.hxx"
#include "io/Query.hxx"

#include <algorithm>

Pieces::Pawn::Pawn(const Pieces::PieceColor& color,
        const Pieces::Position& position)
    : Pieces::BasePiece("Pawn", color, position)
    , m_startLine((color == Pieces::PieceColor::WHITE) ? 1 : 6)
    , m_endLine((color == Pieces::PieceColor::WHITE) ? 7 : 0)
{
    setPieceChar(color, "♙", "♟");
}

void Pieces::Pawn::checkForNextMoves(Pieces::Positions& positions) const
{
    int module = (m_color == Pieces::PieceColor::WHITE) ? 1 : -1;
    Pieces::Position nextPos(m_position.x + (1 * module), m_position.y);
    Pieces::Position next2Pos(m_position.x + (2 * module), m_position.y);
    Chess::Board* board = Chess::Board::GetInstance();
    Query* query = Query::GetInstance();
    if (board->IsFree(nextPos))
    {
        positions.push_back(nextPos);
        if (m_startLine == m_position.x && board->IsFree(next2Pos))
        {
            positions.push_back(next2Pos);
        }
    }
    else if (m_endLine == m_position.x)
    {
        query->AskPawnReplacement();
    }
}

void Pieces::Pawn::setHittableEnemies(Pieces::Positions& positions,
        Pieces::Position& rightPos, Pieces::Position& leftPos) const
{
    Chess::Board* board = Chess::Board::GetInstance();
    Pieces::BasePiece* rightPiece = board->GetPiece(rightPos);
    Pieces::BasePiece* leftPiece = board->GetPiece(leftPos);
    if (rightPiece != nullptr && board->IsEnemy(m_position, rightPos))
    {
        positions.push_back(rightPos);
        rightPiece->SetHittable(true);
    }
    if (leftPiece != nullptr && board->IsEnemy(m_position, leftPos))
    {
        positions.push_back(leftPos);
        leftPiece->SetHittable(true);
    }
}

void Pieces::Pawn::getAvailableMoves(Pieces::Positions& positions) const
{
    int module = (m_color == Pieces::PieceColor::WHITE) ? 1 : -1;
    Pieces::Position nextRightPos(m_position.x + (1*module), m_position.y + 1);
    Pieces::Position nextLeftPos(m_position.x + (1*module), m_position.y - 1);
    checkForNextMoves(positions);
    setHittableEnemies(positions, nextRightPos, nextLeftPos);
}
