#ifndef __SERVER_CHESS_SERVER_HXX__
#define __SERVER_CHESS_SERVER_HXX__

namespace Remote
{
    class ChessServer;
};

class Remote::ChessServer
{
public:
    ChessServer();
    ~ChessServer() = default;

public:
    void RunServer(int port);
};

#endif // __SERVER_CHESS_SERVER_HXX__
