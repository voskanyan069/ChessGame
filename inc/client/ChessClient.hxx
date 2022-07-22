#ifndef __CLIENT_CHESS_CLIENT_HXX__
#define __CLIENT_CHESS_CLIENT_HXX__

#include "protogen/ChessServer.grpc.pb.h"

#include <string>

namespace grpc
{
    class Status;
}

namespace Pieces
{
    struct Position;
}

namespace Remote
{
    struct Room;
    struct LastMove;
    class ChessClient;
};

class Remote::ChessClient
{
public:
    ChessClient(const std::string& hostname);
    ~ChessClient() = default;

public:
    bool IsRoomExists(const std::string& name);
    void CreateRoom(const Remote::Room& room);
    void JoinRoom(const Remote::Room& room);
    void MovePiece(const Remote::Room& room, const Pieces::Position& oldPos,
            const Pieces::Position& newPos);
    void ReadLastMove(const Remote::Room& room, Remote::LastMove& lastMove);

private:
    void checkRequestStatus(const grpc::Status& status);

private:
    std::unique_ptr<Proto::ChessServer::Stub> m_stub;
};

#endif // __CLIENT_CHESS_CLIENT_HXX__
