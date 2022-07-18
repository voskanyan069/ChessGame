#ifndef __CLIENT_CHESS_CLIENT_HXX__
#define __CLIENT_CHESS_CLIENT_HXX__

#include "protogen/ChessServer.grpc.pb.h"

#include <string>

namespace Remote
{
    class ChessClient;
};

class Remote::ChessClient
{
public:
    ChessClient(const std::string& hostname);
    ~ChessClient() = default;

public:
    void ConnectToServer();

private:
    std::unique_ptr<Proto::ChessServer::Stub> m_stub;
};

#endif // __CLIENT_CHESS_CLIENT_HXX__
