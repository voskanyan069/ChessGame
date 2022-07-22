#ifndef __UTILS_TYPES_HXX__
#define __UTILS_TYPES_HXX__

#include <string>
#include <vector>

namespace Remote
{
    struct Room;
    struct LastMove;
}

namespace Pieces
{
    struct Position;
    typedef std::vector<Position> Positions;
    typedef enum { WHITE, BLACK, UNDEF } PieceColor;
}

struct Pieces::Position
{
    int x;
    int y;

    Position(int x = 0, int y = 0)
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

struct Remote::Room
{
    std::string name;
    std::string password;

    Room(const std::string& name, const std::string& password)
        : name(name)
        , password(password)
    {
    }
};

struct Remote::LastMove
{
    Pieces::Position oldPos;
    Pieces::Position newPos;

    LastMove(const Pieces::Position& oldPos=(-1, -1),
             const Pieces::Position& newPos=(-1, -1))
        : oldPos(oldPos)
        , newPos(newPos)
    {
    }
};

#endif // __UTILS_TYPES_HXX__
