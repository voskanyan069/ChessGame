#include "utils/Logger.hxx"
#include "utils/Query.hxx"
#include "chess/Board.hxx"
#include "player/Player.hxx"
#include "player/PlayerMgr.hxx"
#include "pieces/BasePiece.hxx"

#include <iostream>

int main()
{
    Pieces::Position pos;
    Pieces::Position newPos;
    PlayerMgr* playerMgr = PlayerMgr::GetInstance();
    Player* whitePlayer = new Player();
    Player* blackPlayer = new Player();
    whitePlayer->name = "white";
    blackPlayer->name = "black";
    playerMgr->InitPlayer(Pieces::PieceColor::WHITE, whitePlayer);
    playerMgr->InitPlayer(Pieces::PieceColor::BLACK, blackPlayer);
    Logger::GetInstance()->PrintBoard();
    Query::GetInstance()->AskPosition("Current position", pos);
    Pieces::BasePiece* pBP;
    Chess::Board* pBoard = Chess::Board::GetInstance();
    pBP = pBoard->GetBoard()[pos.x][pos.y];
    if (nullptr == pBP)
        return 1;
    Pieces::Positions positions;
    pBP->GetAvailableMoves(positions);
    pBoard->SetAvailableMoves(positions);
    Logger::GetInstance()->PrintBoard();
    Query::GetInstance()->AskPosition("New position", newPos);
    pBP->Move(newPos);
    Logger::GetInstance()->PrintBoard();
    return 0;
}
