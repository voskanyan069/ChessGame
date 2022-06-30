#include "chess/Board.hxx"
#include "pieces/PieceMgr.hxx"
#include "pieces/BasePiece.hxx"
#include "pieces/Pawn.hxx"

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

void Chess::Board::initEmptyFields()
{
    for (int i = 2; i < 6; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_board[i][j] = nullptr;
        }
    }
}

void Chess::Board::initWhitePieces()
{
    for (int i = 0; i < 8; ++i)
    {
        m_board[1][i] = Pieces::PieceMgr::GetInstance()->CreatePiece<
            Pieces::Pawn>(Pieces::WHITE, Pieces::Position(1, i));
    }
}

void Chess::Board::initBlackPieces()
{
    for (int i = 0; i < 8; ++i)
    {
        m_board[6][i] = Pieces::PieceMgr::GetInstance()->CreatePiece<
            Pieces::Pawn>(Pieces::BLACK, Pieces::Position(6, i));
    }
}

void Chess::Board::initBoard()
{
    m_board = new Pieces::BasePiece**[8];
    for (int i = 0; i < 8; ++i)
    {
        m_board[i] = new Pieces::BasePiece*[8];
    }
    initEmptyFields();
    initWhitePieces();
    initBlackPieces();
}

Pieces::BasePiece*** Chess::Board::GetBoard() const
{
    return m_board;
}
