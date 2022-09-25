#ifndef __CLIENT_CHESS_CLIENT_HXX__
#define __CLIENT_CHESS_CLIENT_HXX__

#include "utils/Types.hxx"
#include "protogen/ChessServer.grpc.pb.h"

#include <string>

namespace grpc
{
    class Status;
}

namespace Remote
{
    class ChessClient;
};

class Remote::ChessClient
{
public:
    ChessClient(const std::string& hostname, const std::string& username);
    ~ChessClient() = default;

public:
    bool IsRoomExists(const std::string& name) const;
    void CreateRoom(const Remote::Room& room) const;
    void JoinRoom(const Remote::Room& room) const;
    void WaitForReady(const Remote::Room& room) const;
    void Ready(const Remote::Room& room, const Remote::Player& player) const;
    void MovePiece(const Remote::Room& room, const Pieces::Position& oldPos,
            const Pieces::Position& newPos) const;
    void ReadLastMove(const Remote::Room& room,
            Remote::LastMove& lastMove) const;
    std::string GetOpponentUsername(const Remote::Room& room) const;
    void SetKingHittable(const Remote::Room& room,
            const Pieces::PieceColor& color, bool status) const;

private:
    void convertPieceColor(const Pieces::PieceColor& color,
            Proto::PieceColor& pieceColor) const;
    void checkRequestStatus(const grpc::Status& status,
            const std::string& errorType="Request failed") const;

private:
    std::string m_username;
    std::unique_ptr<Proto::ChessServer::Stub> m_stub;
};

#endif // __CLIENT_CHESS_CLIENT_HXX__
