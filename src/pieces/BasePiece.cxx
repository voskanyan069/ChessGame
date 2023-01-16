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

bool Pieces::BasePiece::cleanPositionIfEnemy(const Pieces::Position& pos) const
{
    Chess::Board* board = Chess::Board::GetInstance();
    Chess::GameMgr* gameMgr = Chess::GameMgr::GetInstance();
    Pieces::BasePiece*** pieces = board->GetBoard();
    Pieces::BasePiece* piece = board->GetPiece(pos);
    if (!board->IsFree(pos))
    {
        if (!board->IsEnemy(m_position, pos))
        {
            return false;
        }
        gameMgr->AddDestroyedPiece(piece);
        delete pieces[pos.x][pos.y];
    }
    return true;
}

bool Pieces::BasePiece::findKingInPositions(const Pieces::Position& kingPos,
        const Pieces::Positions& positions) const
{
    bool ret = false;
    for ( auto pos : positions )
    {
        if ( pos == kingPos )
        {
            ret = true;
        }
        resetPieceHittableStatus(pos);
    }
    return ret;
}

bool Pieces::BasePiece::findKingInEnemyMoves(
        const Pieces::PieceColor& kingColor,
        const Pieces::PieceColor& enemyColor) const
{
    bool ret = false;
    std::vector<Pieces::BasePiece*> pieces;
    Chess::Board* board = Chess::Board::GetInstance();
    Pieces::BasePiece* king = board->GetKing(kingColor);
    Pieces::Position kingPos = king->GetPosition();
    board->GetPieces(enemyColor, pieces);
    for ( Pieces::BasePiece* piece : pieces )
    {
        Pieces::Positions positions;
        piece->getAvailableMoves(positions);
        if ( findKingInPositions(kingPos, positions) )
        {
            ret = true;
        }
    }
    return ret;
}

bool Pieces::BasePiece::isMyKingHittable(Pieces::BasePiece* pPiece) const
{
    if ( nullptr == pPiece )
    {
        throw Utils::Exception("Oops, something went wrong...");
    }
    Pieces::PieceColor color = pPiece->GetColor();
    Pieces::PieceColor enemyColor = Pieces::PieceColor::BLACK;
    if ( Pieces::PieceColor::BLACK == color )
    {
        enemyColor = Pieces::PieceColor::WHITE;
    }
    return findKingInEnemyMoves(color, enemyColor);
}

void Pieces::BasePiece::movePiece(const Pieces::Position& pos)
{
    Chess::Board* board = Chess::Board::GetInstance();
    Chess::GameMgr* gameMgr = Chess::GameMgr::GetInstance();
    Pieces::BasePiece*** pieces = board->GetBoard();
    Pieces::BasePiece* prevPiece = pieces[pos.x][pos.y];
    pieces[pos.x][pos.y] = std::move(pieces[m_position.x][m_position.y]);
    pieces[m_position.x][m_position.y] = nullptr;
    bool bIsKingHittable = isMyKingHittable(pieces[pos.x][pos.y]);
    if ( bIsKingHittable )
    {
        pieces[m_position.x][m_position.y] = std::move(pieces[pos.x][pos.y]);
        pieces[pos.x][pos.y] = prevPiece;
        throw Utils::Exception("Your king is under the attack!", "Signal", 2);
    }
    m_position.x = pos.x;
    m_position.y = pos.y;
    gameMgr->AddNewLastMove(pieces[m_position.x][m_position.y]->GetPieceChar(),
            m_position, pos);
}

void Pieces::BasePiece::SetHittable(bool isHittable)
{
    m_isHittable = isHittable;
    if (isHittable)
    {
        m_pieceChar = "\033[31m" + m_pieceChar;
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
        if (!cleanPositionIfEnemy(pos)) continue;
        movePiece(position);
        isMoved = true;
    }
    if ( !isMoved )
    {
        throw Utils::Exception("Incorrect position");
    }
}
