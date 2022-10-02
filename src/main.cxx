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

void initArgsParser(ArgsParser& parser)
{
    parser.AddSwitch("get-rooms,R", "get all exists rooms of the server",
            bGetRooms);
    parser.AddOption<std::string>("host,H", "host address of the server",
            "localhost");
    parser.AddOption<int>("port,P", "port of the server", 58001);
    parser.AddOption<std::string>("room,r", "create or join to room", "admin");
    parser.AddOption<std::string>("password,p", "password of the room","");
    parser.AddOption<std::string>("username,u", "player username", getlogin());
    if (!parser.ParseArguments())
    {
        std::string helpMsg;
        parser.GetHelpMessage(helpMsg);
        helpMsg += "\n" + Chess::GameMgr::GetCommandsHelp();
        Logger::GetInstance()->PrintHelp(helpMsg);
        std::exit(1);
    }
    Logger::GetInstance()->Print(INFO, "rooms : %b", bGetRooms);
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
    else
    {
        Chess::GameMgr::GetInstance()->ConnectToServer();
        Chess::GameMgr::GetInstance()->StartGame();
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

//void testConnection()
//{
//    CMDArguments* args = CMDArguments::GetInstance();
//    std::string hostname = args->Find("host")->Get<std::string>();
//    int port = args->Find("port")->Get<int>();
//    Remote::Room room(args->Find("room")->Get<std::string>(),
//            args->Find("password")->Get<std::string>());
//    hostname += ":" + std::to_string(port);
//    Remote::ChessClient client(hostname);
//    Logger::GetInstance()->Print(INFO, "Connecting to %s...", hostname);
//    try
//    {
//        if (client.IsRoomExists(room.name))
//        {
//            Logger::GetInstance()->Print(INFO, "Trying to join %s...",
//                    room.name);
//            client.JoinRoom(room);
//            Logger::GetInstance()->Print(INFO, "Joined to %s", room.name);
//            bool isReady = Query::GetInstance()->AskForReady();
//            if (!isReady)
//            {
//                std::exit(1);
//            }
//            Logger::GetInstance()->PrintEndl();
//            client.Ready(room, { Remote::PlayerType::GUEST, isReady });
//            Logger::GetInstance()->Print(INFO, "Waiting for ready opponent...");
//            client.WaitForReady(room);
//
//            Pieces::Position pos;
//            Pieces::Position newPos;
//            Pieces::BasePiece* pBP;
//            Chess::Board* pBoard = Chess::Board::GetInstance();
//            PlayerMgr* playerMgr = PlayerMgr::GetInstance();
//            Player* whitePlayer = new Player();
//            Player* blackPlayer = new Player();
//            whitePlayer->name = "white";
//            blackPlayer->name = "black";
//            playerMgr->InitPlayer(Pieces::PieceColor::WHITE, whitePlayer);
//            playerMgr->InitPlayer(Pieces::PieceColor::BLACK, blackPlayer);
//            Logger::GetInstance()->PrintBoard();
//            Query::GetInstance()->AskPosition("Current position", pos);
//            pBP = pBoard->GetPiece(pos);
//            if (nullptr == pBP)
//                std::exit(-1);
//            Pieces::Positions positions;
//            pBP->GetAvailableMoves(positions);
//            pBoard->SetAvailableMoves(positions);
//            Logger::GetInstance()->PrintBoard();
//            Query::GetInstance()->AskPosition("New position", newPos);
//            pBP->Move(newPos);
//            client.MovePiece(room, pos, newPos);
//            Logger::GetInstance()->PrintBoard();
//        }
//        else
//        {
//            Logger::GetInstance()->Print(INFO, "Trying to create room %s...",
//                    room.name);
//            client.CreateRoom(room);
//            Logger::GetInstance()->Print(INFO, "Created and joined to %s",
//                    room.name);
//            bool isReady = Query::GetInstance()->AskForReady();
//            Logger::GetInstance()->PrintEndl();
//            if (!isReady)
//            {
//                std::exit(1);
//            }
//            client.Ready(room, { Remote::PlayerType::OWNER, isReady });
//            Logger::GetInstance()->Print(INFO, "Waiting for ready opponent\n");
//            client.WaitForReady(room);
//
//            Pieces::Position pos;
//            Pieces::Position newPos;
//            Pieces::BasePiece* pBP;
//            Chess::Board* pBoard = Chess::Board::GetInstance();
//            PlayerMgr* playerMgr = PlayerMgr::GetInstance();
//            Player* whitePlayer = new Player();
//            Player* blackPlayer = new Player();
//            whitePlayer->name = "white";
//            blackPlayer->name = "black";
//            playerMgr->InitPlayer(Pieces::PieceColor::WHITE, whitePlayer);
//            playerMgr->InitPlayer(Pieces::PieceColor::BLACK, blackPlayer);
//            Logger::GetInstance()->PrintBoard();
//            Logger::GetInstance()->Print(INFO, "Waiting for opponent move...");
//            Logger::GetInstance()->PrintEndl();
//            Remote::LastMove lastMove;
//            client.ReadLastMove(room, lastMove);
//            Pieces::Positions positions;
//            pBP = pBoard->GetPiece(lastMove.oldPos);
//            pBP->GetAvailableMoves(positions);
//            pBP->Move(lastMove.newPos);
//            Logger::GetInstance()->PrintBoard();
//            Query::GetInstance()->AskPosition("Current position", pos);
//            pBP = pBoard->GetPiece(pos);
//            if (nullptr == pBP)
//                std::exit(-1);
//            positions.clear();
//            pBP->GetAvailableMoves(positions);
//            pBoard->SetAvailableMoves(positions);
//            Logger::GetInstance()->PrintBoard();
//            Query::GetInstance()->AskPosition("New position", newPos);
//            pBP->Move(newPos);
//            client.MovePiece(room, pos, newPos);
//            Logger::GetInstance()->PrintBoard();
//        }
//    }
//    catch (const Utils::Exception& e)
//    {
//        Logger::GetInstance()->Print(e);
//        std::exit(1);
//    }
//}

int main(int argc, char** argv)
{
    ArgsParser parser(argc, argv);
    initArgsParser(parser);
    initGameMgrModel();
    startGame();
    //testBoard();
    //testConnection();
    return 0;
}
