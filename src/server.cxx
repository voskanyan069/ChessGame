#include "server/ChessServer.hxx"
#include "args/ArgsParser.hxx"
#include "args/CMDArgument.hxx"

#include <iostream>

void initArgsParser(ArgsParser& parser)
{
    parser.AddOption<int>("port,P", "port of the server", 58001);
    if (!parser.ParseArguments())
    {
        std::string helpMsg;
        parser.GetHelpMessage(helpMsg);
        std::cout << helpMsg;
        std::exit(1);
    }
}

void runServer()
{
    int port = CMDArguments::GetInstance()->Find("port")->Get<int>();
    Remote::ChessServer server;
    server.RunServer(port);
}

int main(int argc, char** argv)
{
    ArgsParser parser(argc, argv);
    initArgsParser(parser);
    runServer();
    return 0;
}
