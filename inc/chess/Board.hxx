#ifndef __CHESS_BOARD_HXX__
#define __CHESS_BOARD_HXX__

#include "pieces/BasePiece.hxx"

namespace Chess
{
    class Board;
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
    void SetAvailableMoves(const Pieces::Positions& positions) const;
    Pieces::BasePiece*** GetBoard() const;
    void DestroyEmpties();
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
