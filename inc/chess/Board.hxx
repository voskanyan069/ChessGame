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
    bool IsFree(const Pieces::Position& pos) const;
    bool IsEnemy(const Pieces::Position& piecePos,
            const Pieces::Position& newPos) const;
    Pieces::BasePiece* GetPiece(const Pieces::Position& pos) const;
    Pieces::BasePiece* GetKing(const Pieces::PieceColor& color) const;
    void SetAvailableMoves(const Pieces::Positions& positions) const;
    Pieces::BasePiece*** GetBoard() const;
    void GetPieces(const Pieces::PieceColor& color,
            std::vector<Pieces::BasePiece*>& pieces) const;
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
