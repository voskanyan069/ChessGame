#ifndef __SERVER_CHESS_SERVICE_IMPL_HXX__
#define __SERVER_CHESS_SERVICE_IMPL_HXX__

#include "utils/Types.hxx"
#include "protogen/ChessServer.pb.h"
#include "protogen/ChessServer.grpc.pb.h"
#include "protogen/ChessServerTypes.pb.h"
#include "protogen/ChessServerTypes.pb.h"

#include <map>

#include <grpcpp/grpcpp.h>

namespace Remote
{
    class ServerRoom;
    class ChessServiceImpl;
};

class Remote::ChessServiceImpl final : public Proto::ChessServer::Service
{
public:
    ChessServiceImpl();
    ~ChessServiceImpl();

public:
    grpc::Status GetRooms(
            grpc::ServerContext* context,
            const Proto::Empty* request,
            Proto::RoomsInfo* response) override;
    grpc::Status IsRoomExists(
            grpc::ServerContext* context,
            const Proto::String* request,
            Proto::Bool* response) override;
    grpc::Status CreateRoom(
            grpc::ServerContext* context,
            const Proto::RoomWithUsername* request,
            Proto::Empty* response) override;
    grpc::Status JoinRoom(
            grpc::ServerContext* context,
            const Proto::RoomWithUsername* request,
            Proto::Empty* response) override;
    grpc::Status LeaveRoom(
            grpc::ServerContext* context,
            const Proto::RoomWithUsername* request,
            Proto::Empty* response) override;
    grpc::Status SpectateRoom(
            grpc::ServerContext* context,
            const Proto::String* request,
            grpc::ServerWriter<Proto::LastMoveInfo>* writer) override;
    grpc::Status LeaveSpectatorRoom(
            grpc::ServerContext* context,
            const Proto::String* request,
            Proto::Empty* response) override;
    grpc::Status GetViewersCount(
            grpc::ServerContext* context,
            const Proto::String* request,
            Proto::Integer* response) override;
    grpc::Status GetUsername(
            grpc::ServerContext* context,
            const Proto::RoomWithUsername* request,
            Proto::String* response) override;
    grpc::Status WaitForReady(
            grpc::ServerContext* context,
            const Proto::RoomSettings* request,
            Proto::Empty* response) override;
    grpc::Status Ready(
            grpc::ServerContext* context,
            const Proto::ReadyRequest* request,
            Proto::Empty* response) override;
    grpc::Status MovePiece(
            grpc::ServerContext* context,
            const Proto::MoveRequest* request,
            Proto::Empty* response) override;
    grpc::Status ReadPieceMove(
            grpc::ServerContext* context,
            const Proto::RoomSettings* request,
            Proto::LastMoveInfo* response) override;

private:
    bool doCheckRoomSettings(const Proto::RoomSettings& settings,
            std::string& message) const;
    void initMutexAndConditionVar(
            std::unique_ptr<boost::mutex>& mutex,
            std::unique_ptr<boost::condition_variable>& condVar) const;

private:
    std::map<std::string, Remote::ServerRoom> m_mapRooms;
};

#endif // __SERVER_CHESS_SERVICE_IMPL_HXX__
