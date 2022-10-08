#ifndef __UTILS_TYPES_HXX__
#define __UTILS_TYPES_HXX__

#include <string>
#include <vector>
#include <memory>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

typedef std::unique_ptr<boost::mutex> BoostMutexUP;
typedef std::unique_ptr<boost::condition_variable> BoostConditionVariableUP;

namespace Remote
{
    typedef enum { OWNER, GUEST } PlayerType;
    struct Room;
    struct Player;
    struct ServerRoom;
    struct ServerPlayer;
    struct LastMove;
    typedef std::vector<Remote::LastMove> LastMovesVec;
}

namespace Pieces
{
    struct Position;
    typedef std::vector<Position> Positions;
    typedef enum { WHITE, BLACK, UNDEF } PieceColor;
}

struct Player
{
    std::string name;
    Pieces::PieceColor color;
};

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
    bool isKingHittable;
    Pieces::PieceColor hittableKingColor;

    LastMove(const Pieces::Position& oldPos=(-1, -1),
             const Pieces::Position& newPos=(-1, -1))
        : oldPos(oldPos)
        , newPos(newPos)
        , isKingHittable(false)
        , hittableKingColor(Pieces::PieceColor::UNDEF)
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
        isKingHittable = false;
        hittableKingColor = Pieces::PieceColor::UNDEF;
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

struct Remote::Player
{
    PlayerType playerType;
    bool isReady;
};

struct Remote::ServerPlayer
{
    std::string username;
    bool isReady;

    inline bool operator==(const ServerPlayer& other)
    {
        return username == other.username;
    }

    inline bool operator!=(const ServerPlayer& other)
    {
        return username != other.username;
    }
};

struct Remote::ServerRoom
{
    bool exists;
    bool isLastMoveRead;
    bool isSpectatorLastMoveRead;
    int spectatorsCount;
    std::string password;
    Remote::ServerPlayer ownerPlayer;
    Remote::ServerPlayer guestPlayer;
    Remote::LastMove lastMove;
    Remote::LastMove spectatorLastMove;
    Remote::LastMovesVec vecMovesHistory;
    BoostMutexUP waitMutex;
    BoostConditionVariableUP waitConditionVar;    
    BoostMutexUP moveMutex;
    BoostConditionVariableUP moveConditionVar;    
    BoostMutexUP spectatorMutex;
    BoostConditionVariableUP spectatorConditionVar;
};

#endif // __UTILS_TYPES_HXX__
