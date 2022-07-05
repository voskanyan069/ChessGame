#ifndef __PIECES_BASE_PIECE_HXX__
#define __PIECES_BASE_PIECE_HXX__

#include <string>

namespace Pieces
{
    class BasePiece;
    struct Position;
    typedef enum { WHITE = 0, BLACK = 1, UNDEF = 2 } PieceColor;
}

struct Pieces::Position
{
    int x;
    int y;

    Position(int x=0, int y=0)
        : x(x)
        , y(y)
    {
    }
};

class Pieces::BasePiece
{
public:
    BasePiece(const PieceColor& color=UNDEF,
            const Position& position=Position(-1, -1));
    virtual ~BasePiece() = default;

public:
    const std::string& GetPieceChar() const;
    PieceColor GetColor() const;
    Position GetPosition() const;
    virtual Position* GetAvailableMoves() const;

protected:
    void setPieceChar(const Pieces::PieceColor& color,
            const std::string& white, const std::string& black);

protected:
    std::string m_pieceChar;
    PieceColor m_color;
    Position m_position;
};

#endif // __PIECES_BASE_PIECE_HXX__
