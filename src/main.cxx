#include "io/Logger.hxx"
#include "io/Query.hxx"
#include "utils/Types.hxx"
#include "utils/Exception.hxx"
#include "chess/Board.hxx"
#include "chess/GameMgr.hxx"
#include "player/PlayerMgr.hxx"
#include "pieces/BasePiece.hxx"
#include "args/ArgsParser.hxx"
#include "args/CMDArgument.hxx"
#include "client/ChessClient.hxx"

#include <iostream>
#include <unistd.h>

bool bGetRooms = false;
bool bSpectatorMode = false;

void initArgsParser(ArgsParser& parser)
{
    parser.AddSwitch("get-rooms,R", "get all exists rooms of the server",
            bGetRooms);
    parser.AddSwitch("spectator-mode,S", "join as spectator", bSpectatorMode);
    parser.AddOption<std::string>("host,H", "host address of the server",
            "localhost");
    parser.AddOption<int>("port,P", "port of the server", 58001);
    parser.AddOption<std::string>("room,r", "create or join to room", "admin");
    parser.AddOption<std::string>("password,p", "password of the room","");
    parser.AddOption<std::string>("username,u", "player username", getlogin());
    try
    {
        parser.ParseArguments();
    }
    catch ( const Utils::Exception& e )
    {
        if ( 0 == strcmp("help", e.what()) )
        {
            std::string helpMsg;
            parser.GetHelpMessage(helpMsg);
            helpMsg += "\n" + Chess::GameMgr::GetCommandsHelp();
            Logger::GetInstance()->PrintHelp(helpMsg);
        }
        else
        {
            Logger::GetInstance()->Print(e);
        }
        std::exit(1);
    }
}

void initGameMgrModel()
{
    Chess::GameMgr::GetInstance()->InitModel();
}

void startGame()
{
    if (bGetRooms)
    {
        Chess::GameMgr::GetInstance()->GetRooms();
    }
    else if (bSpectatorMode)
    {
        Chess::GameMgr::GetInstance()->SpectateGame();
    }
    else
    {
        Chess::GameMgr::GetInstance()->ConnectToServer();
        Chess::GameMgr::GetInstance()->StartGame();
    }
}

int main(int argc, char** argv)
{
    ArgsParser parser(argc, argv);
    initArgsParser(parser);
    initGameMgrModel();
    startGame();
    return 0;
}
