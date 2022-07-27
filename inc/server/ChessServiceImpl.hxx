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
    grpc::Status IsRoomExists(grpc::ServerContext* context,
            const Proto::String* request,
            Proto::Bool* response) override;
    grpc::Status CreateRoom(grpc::ServerContext* context,
            const Proto::RoomSettings* request,
            Proto::ActionResult* response) override;
    grpc::Status JoinRoom(grpc::ServerContext* context,
            const Proto::RoomSettings* request,
            Proto::ActionResult* response) override;
    grpc::Status MovePiece(grpc::ServerContext* context,
            const Proto::MoveRequest* request,
            Proto::Empty* response) override;
    grpc::Status ReadPieceMove(grpc::ServerContext* context,
            const Proto::RoomSettings* request,
            Proto::LastMoveInfo* response) override;

private:
    std::map<std::string, Remote::ServerRoom> m_mapRooms;
};

#endif // __SERVER_CHESS_SERVICE_IMPL_HXX__
