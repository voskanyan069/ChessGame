#ifndef __SERVER_CHESS_SERVICE_IMPL_HXX__
#define __SERVER_CHESS_SERVICE_IMPL_HXX__

#include "protogen/ChessServer.pb.h"
#include "protogen/ChessServer.grpc.pb.h"
#include "protogen/ChessServerTypes.pb.h"
#include "protogen/ChessServerTypes.pb.h"

#include <grpcpp/grpcpp.h>

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
    grpc::Status ConnectToServer(grpc::ServerContext* context,
                                 const Proto::Empty* request,
                                 Proto::ActionResult* response) override;
};

#endif // __SERVER_CHESS_SERVICE_IMPL_HXX__
