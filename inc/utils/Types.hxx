#ifndef __UTILS_TYPES_HXX__
#define __UTILS_TYPES_HXX__

#include <string>
#include <vector>
#include <memory>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

typedef std::shared_ptr<boost::mutex> BoostMutexSP;
typedef std::shared_ptr<boost::condition_variable> BoostConditionVariableSP;

namespace Remote
{
    struct Room;
    struct ServerRoom;
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

    bool IsNull()
    {
        return oldPos.x == -1;
    }

    void Clean()
    {
        oldPos.x = -1;
        oldPos.y = -1;
        newPos.x = -1;
        newPos.y = -1;
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

struct Remote::ServerRoom
{
    std::string password;
    bool isLastMoveRead;
    Remote::LastMove lastMove;
    BoostMutexSP moveMutex;
    BoostConditionVariableSP moveConditionVar;    
};

#endif // __UTILS_TYPES_HXX__
