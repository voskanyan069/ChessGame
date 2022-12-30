#include "chess/Board.hxx"
#include "pieces/PieceMgr.hxx"
#include "pieces/BasePiece.hxx"
#include "pieces/EmptyPiece.hxx"
#include "pieces/Pawn.hxx"
#include "pieces/Rook.hxx"
#include "pieces/Knight.hxx"
#include "pieces/Bishop.hxx"
#include "pieces/Queen.hxx"
#include "pieces/King.hxx"
#include <iostream>

Chess::Board* Chess::Board::GetInstance()
{
    static Chess::Board* instance = new Chess::Board();
    return instance;
}

Chess::Board::Board()
    : m_board(nullptr)
{
    initBoard();
}

Chess::Board::~Board()
{
    Clean();
}

void Chess::Board::initEmptyFields()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_board[i][j] = nullptr;
        }
    }
}

void Chess::Board::initPawnPieces()
{
    for (int i = 0; i < 8; ++i)
    {
        m_board[1][i] = Pieces::CreatePiece<
            Pieces::Pawn>(Pieces::WHITE, Pieces::Position(1, i));
        m_board[6][i] = Pieces::CreatePiece<
            Pieces::Pawn>(Pieces::BLACK, Pieces::Position(6, i));
    }
}

void Chess::Board::initRookPieces()
{
    m_board[0][0] = Pieces::CreatePiece<
        Pieces::Rook>(Pieces::WHITE, Pieces::Position(0, 0));
    m_board[0][7] = Pieces::CreatePiece<
        Pieces::Rook>(Pieces::WHITE, Pieces::Position(0, 7));
    m_board[7][0] = Pieces::CreatePiece<
        Pieces::Rook>(Pieces::BLACK, Pieces::Position(7, 0));
    m_board[7][7] = Pieces::CreatePiece<
        Pieces::Rook>(Pieces::BLACK, Pieces::Position(7, 7));
}

void Chess::Board::initKnightPieces()
{
    m_board[0][1] = Pieces::CreatePiece<
        Pieces::Knight>(Pieces::WHITE, Pieces::Position(0, 1));
    m_board[0][6] = Pieces::CreatePiece<
        Pieces::Knight>(Pieces::WHITE, Pieces::Position(0, 6));
    m_board[7][1] = Pieces::CreatePiece<
        Pieces::Knight>(Pieces::BLACK, Pieces::Position(7, 1));
    m_board[7][6] = Pieces::CreatePiece<
        Pieces::Knight>(Pieces::BLACK, Pieces::Position(7, 6));
}

void Chess::Board::initBishopPieces()
{
    m_board[0][2] = Pieces::CreatePiece<
        Pieces::Bishop>(Pieces::WHITE, Pieces::Position(0, 2));
    m_board[0][5] = Pieces::CreatePiece<
        Pieces::Bishop>(Pieces::WHITE, Pieces::Position(0, 5));
    m_board[7][2] = Pieces::CreatePiece<
        Pieces::Bishop>(Pieces::BLACK, Pieces::Position(7, 2));
    m_board[7][5] = Pieces::CreatePiece<
        Pieces::Bishop>(Pieces::BLACK, Pieces::Position(7, 5));
}

void Chess::Board::initQueenPieces()
{
    m_board[0][3] = Pieces::CreatePiece<
        Pieces::Queen>(Pieces::WHITE, Pieces::Position(0, 3));
    m_board[7][3] = Pieces::CreatePiece<
        Pieces::Queen>(Pieces::BLACK, Pieces::Position(7, 3));
}

void Chess::Board::initKingPieces()
{
    m_board[0][4] = Pieces::CreatePiece<
        Pieces::King>(Pieces::WHITE, Pieces::Position(0, 4));
    m_board[7][4] = Pieces::CreatePiece<
        Pieces::King>(Pieces::BLACK, Pieces::Position(7, 4));
}

void Chess::Board::initPieces()
{
    initPawnPieces();
    initRookPieces();
    initKnightPieces();
    initBishopPieces();
    initQueenPieces();
    initKingPieces();
}

void Chess::Board::initBoard()
{
    m_board = new Pieces::BasePiece**[8];
    for (int i = 0; i < 8; ++i)
    {
        m_board[i] = new Pieces::BasePiece*[8];
    }
    initEmptyFields();
    initPieces();
//#warning (INIT BOARD COMMENT LINES)
//    m_board[4][4] = Pieces::CreatePiece<
//        Pieces::King>(Pieces::WHITE, Pieces::Position(4, 4));

    //m_board[1][3] = Pieces::CreatePiece<
    //    Pieces::King>(Pieces::BLACK, Pieces::Position(1, 3));
    //m_board[5][5] = Pieces::CreatePiece<
    //    Pieces::Bishop>(Pieces::BLACK, Pieces::Position(5, 5));
    //m_board[5][3] = Pieces::CreatePiece<
    //    Pieces::Rook>(Pieces::WHITE, Pieces::Position(5, 3));
    //m_board[2][3] = Pieces::CreatePiece<
    //    Pieces::Knight>(Pieces::BLACK, Pieces::Position(2, 3));
    //m_board[3][7] = Pieces::CreatePiece<
    //    Pieces::Bishop>(Pieces::BLACK, Pieces::Position(3, 7));
}

bool Chess::Board::IsFree(const Pieces::Position& pos) const
{
    return nullptr == GetPiece(pos);
}

bool Chess::Board::IsEnemy(const Pieces::Position& piecePos,
        const Pieces::Position& newPos) const
{
    if (IsFree(piecePos) || IsFree(newPos))
    {
        return false;
    }
    return GetPiece(piecePos)->GetColor() != GetPiece(newPos)->GetColor();
}

bool Chess::Board::IsKingHittable(const Pieces::PieceColor& color) const
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Pieces::Position pos(i, j);
            if (IsFree(pos))
            {
                continue;
            }
            Pieces::BasePiece* pPiece = GetPiece(pos);
            if ("King" == pPiece->GetPieceName() && color == pPiece->GetColor())
            {
                return pPiece->IsHittable();
            }
        }
    }
}

void Chess::Board::SetKingHittable(const Pieces::PieceColor& color,
        bool status)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Pieces::Position pos(i, j);
            if (IsFree(pos))
            {
                continue;
            }
            Pieces::BasePiece* pPiece = GetPiece(pos);
            if ("King" == pPiece->GetPieceName() && color == pPiece->GetColor())
            {
                return pPiece->SetHittable(status);
            }
        }
    }
}

Pieces::BasePiece* Chess::Board::GetPiece(const Pieces::Position& pos) const
{
    if (8 < pos.x || 0 > pos.x ||
            8 < pos.y || 0 > pos.y)
    {
        return nullptr;
    }
    if (nullptr == m_board[pos.x][pos.y])
    {
        return nullptr;
    }
    return m_board[pos.x][pos.y];
}

void Chess::Board::SetAvailableMoves(const Pieces::Positions& positions) const
{
    for (auto& pos : positions)
    {
        if (IsFree(pos))
        {
            Pieces::BasePiece* available = new Pieces::EmptyPiece(
                    Pieces::Position(pos.x, pos.y));
            m_board[pos.x][pos.y] = std::move(available);
        }
    }
}

Pieces::BasePiece*** Chess::Board::GetBoard() const
{
    return m_board;
}

void Chess::Board::DestroyEmpties()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (IsFree(Pieces::Position(i, j)))
            {
                continue;
            }
            if (Pieces::PieceColor::UNDEF == m_board[i][j]->GetColor())
            {
                delete m_board[i][j];
                m_board[i][j] = nullptr;
            }
        }
    }
}

void Chess::Board::Clean()
{
    for (int i = 0; i < 8; ++i)
    {
        delete[] m_board[i];
    }
    delete[] m_board;
}
