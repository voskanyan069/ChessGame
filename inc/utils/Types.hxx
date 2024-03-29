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
    struct GetRoomsInfo;
    struct Player;
    struct ServerRoom;
    struct ServerPlayer;
    struct LastMove;
    struct Spectator;
    typedef std::vector<Remote::LastMove> LastMovesVec;
    typedef std::vector<Remote::Spectator*> SpectatorVec;
}

namespace Pieces
{
    struct Position;
    struct PrintableLastMove;
    typedef std::vector<Position> Positions;
    typedef enum { WHITE, BLACK, UNDEF } PieceColor;
    typedef enum { QUEEN, ROOK, BISHOP, KNIGHT } PawnReplacements;
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

struct Pieces::PrintableLastMove
{
    std::string piece;
    std::string time;
    Pieces::Position oldPos;
    Pieces::Position newPos;

    PrintableLastMove(const std::string& p, const std::string& t,
            const Pieces::Position& o, const Pieces::Position& n)
        : piece(p)
        , time(t)
        , oldPos(o)
        , newPos(n)
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

struct Remote::GetRoomsInfo
{
    std::string name;
    bool is_closed;
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

struct Remote::Spectator
{
    bool isOnline;
    bool isLastMoveRead;
    std::string uid;
    BoostMutexUP mutex;
    BoostConditionVariableUP conditionVar;
};

struct Remote::ServerRoom
{
    bool exists;
    bool isLastMoveRead;
    std::string password;
    Remote::ServerPlayer ownerPlayer;
    Remote::ServerPlayer guestPlayer;
    Remote::LastMove lastMove;
    Remote::LastMove spectatorLastMove;
    Remote::LastMovesVec vecMovesHistory;
    Remote::SpectatorVec vecSpectators;
    BoostMutexUP waitMutex;
    BoostConditionVariableUP waitConditionVar;    
    BoostMutexUP moveMutex;
    BoostConditionVariableUP moveConditionVar;    
    BoostMutexUP closeMutex;
    BoostConditionVariableUP closeConditionVar;
};

#endif // __UTILS_TYPES_HXX__
