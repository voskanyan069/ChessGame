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
    ~Board();

private:
    Board();

public:
    Pieces::BasePiece*** GetBoard() const;
    void Clean();

private:
    void initBoard();
    void initEmptyFields();
    void initPawnPieces();
    void initRookPieces();
    void initKnightPieces();
    void initBishopPieces();
    void initQueenPieces();
    void initKingPieces();
    void initPieces();

private:
    Pieces::BasePiece*** m_board;
};

#endif // __CHESS_BOARD_HXX__
