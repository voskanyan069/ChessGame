#ifndef __CHESS_BOARD_HXX__
#define __CHESS_BOARD_HXX__

namespace Chess
{
    class Board;
}

namespace Pieces
{
    class BasePiece;
}

class Chess::Board
{
public:
    static Board* GetInstance();
    Board(Board const&) = delete;
    void operator=(Board const&) = delete;

private:
    Board();
    void initEmptyFields();
    void initWhitePieces();
    void initBlackPieces();

public:
    Pieces::BasePiece*** GetBoard() const;

private:
    void initBoard();

private:
    Pieces::BasePiece*** m_board;
};

#endif // __CHESS_BOARD_HXX__
