#ifndef __PIECES_BASE_PIECE_HXX__
#define __PIECES_BASE_PIECE_HXX__

#include <string>
#include <vector>

namespace Pieces
{
    class BasePiece;
    struct Position;
    typedef std::vector<Position> Positions;
    typedef enum { WHITE, BLACK, UNDEF } PieceColor;
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

    inline bool operator==(const Position& other)
    {
        return x == other.x && y == other.y;
    }

    inline bool operator!=(const Position& other)
    {
        return !(*this == other);
    }
};

class Pieces::BasePiece
{
public:
    BasePiece(const PieceColor& color=UNDEF,
            const Position& position=Position(-1, -1));
    virtual ~BasePiece() = default;

public:
    void SetHittable(bool isHittable);
    const std::string& GetPieceChar() const;
    PieceColor GetColor() const;
    Position GetPosition() const;
    void Move(const Pieces::Position& position);
    void GetAvailableMoves(Pieces::Positions& positions);

protected:
    virtual void getAvailableMoves(Pieces::Positions& positions) const;
    void setPieceChar(const Pieces::PieceColor& color,
            const std::string& white, const std::string& black);

protected:
    std::string m_pieceChar;
    std::string m_pieceInitialChar;
    Pieces::PieceColor m_color;
    Pieces::Position m_position;
    Pieces::Positions m_vecAvailableMoves;
};

#endif // __PIECES_BASE_PIECE_HXX__
