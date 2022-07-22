#ifndef __SERVER_CHESS_SERVICE_IMPL_HXX__
#define __SERVER_CHESS_SERVICE_IMPL_HXX__

#include "utils/Types.hxx"
#include "protogen/ChessServer.pb.h"
#include "protogen/ChessServer.grpc.pb.h"
#include "protogen/ChessServerTypes.pb.h"
#include "protogen/ChessServerTypes.pb.h"

#include <map>

#include <grpcpp/grpcpp.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

namespace Remote
{
    class ChessServiceImpl;
};

class Remote::ChessServiceImpl final : public Proto::ChessServer::Service
{
public:
    ChessServiceImpl();
    ~ChessServiceImpl() = default;

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
    bool m_isLastMoveRead;
    boost::mutex m_mutex;
    boost::condition_variable m_condition;
    std::map<std::string, std::string> m_mapRooms;
    std::map<std::string, Remote::LastMove> m_mapLastMove;
};

#endif // __SERVER_CHESS_SERVICE_IMPL_HXX__
