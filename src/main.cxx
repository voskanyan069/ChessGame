#include "utils/Logger.hxx"
#include "utils/Query.hxx"
#include "player/Player.hxx"
#include "player/PlayerMgr.hxx"
#include "pieces/BasePiece.hxx"

int main()
{
    Pieces::Position pos;
    PlayerMgr* playerMgr = PlayerMgr::GetInstance();
    Player* whitePlayer = new Player();
    Player* blackPlayer = new Player();
    whitePlayer->name = "white";
    blackPlayer->name = "black";
    playerMgr->InitPlayer(Pieces::PieceColor::WHITE, whitePlayer);
    playerMgr->InitPlayer(Pieces::PieceColor::BLACK, blackPlayer);
    Logger::GetInstance()->PrintBoard();
    Query::GetInstance()->AskPosition("Current position", pos);
    return 0;
}
