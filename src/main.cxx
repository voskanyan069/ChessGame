#include "io/Logger.hxx"
#include "io/Query.hxx"
#include "chess/Board.hxx"
#include "player/Player.hxx"
#include "player/PlayerMgr.hxx"
#include "pieces/BasePiece.hxx"
#include "args/ArgsParser.hxx"
#include "args/CMDArgument.hxx"
#include "client/ChessClient.hxx"

#include <iostream>

void initArgsParser(ArgsParser& parser)
{
    parser.AddOption<std::string>("host,H", "host address of the server",
            "localhost");
    parser.AddOption<int>("port,P", "port of the server", 58001);
    if (!parser.ParseArguments())
    {
        std::string helpMsg;
        parser.GetHelpMessage(helpMsg);
        Logger::GetInstance()->PrintHelp(helpMsg);
        std::exit(1);
    }
}

void testBoard()
{
    Pieces::Position pos;
    Pieces::Position newPos;
    Pieces::BasePiece* pBP;
    Chess::Board* pBoard = Chess::Board::GetInstance();
    PlayerMgr* playerMgr = PlayerMgr::GetInstance();
    Player* whitePlayer = new Player();
    Player* blackPlayer = new Player();
    whitePlayer->name = "white";
    blackPlayer->name = "black";
    playerMgr->InitPlayer(Pieces::PieceColor::WHITE, whitePlayer);
    playerMgr->InitPlayer(Pieces::PieceColor::BLACK, blackPlayer);
    Logger::GetInstance()->PrintBoard();
    for (int i = 0; i < 2; ++i)
    {
        Query::GetInstance()->AskPosition("Current position", pos);
        //pos = Pieces::Position(4, 4);
        pBP = pBoard->GetPiece(pos);
        if (nullptr == pBP)
            std::exit(-1);
        Pieces::Positions positions;
        pBP->GetAvailableMoves(positions);
        pBoard->SetAvailableMoves(positions);
        Logger::GetInstance()->PrintBoard();
        Query::GetInstance()->AskPosition("New position", newPos);
        pBP->Move(newPos);
        Logger::GetInstance()->PrintBoard();
    }
    delete whitePlayer;
    delete blackPlayer;
}

void testConnection()
{
    std::string hostname = CMDArguments::GetInstance()->Find("host")->Get<std::string>();
    int port = CMDArguments::GetInstance()->Find("port")->Get<int>();
    hostname += ":" + std::to_string(port);
    Remote::ChessClient client(hostname);
    std::cout << "Connecting to " << hostname << std::endl;
    client.ConnectToServer();
}

int main(int argc, char** argv)
{
    ArgsParser parser(argc, argv);
    initArgsParser(parser);
    testBoard();
    //testConnection();
    return 0;
}
