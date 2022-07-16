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
    Pieces::BasePiece* pBP;
    Chess::Board* pBoard = Chess::Board::GetInstance();
    PlayerMgr* playerMgr = PlayerMgr::GetInstance();
    Player* whitePlayer = new Player();
    Player* blackPlayer = new Player();
    whitePlayer->name = "white";
    blackPlayer->name = "black";
    playerMgr->InitPlayer(Pieces::PieceColor::WHITE, whitePlayer);
    playerMgr->InitPlayer(Pieces::PieceColor::BLACK, blackPlayer);
    for (int i = 0; i < 2; ++i)
    {
        Logger::GetInstance()->PrintBoard();
        Query::GetInstance()->AskPosition("Current position", pos);
        //pos = Pieces::Position(4, 4);
        pBP = pBoard->GetPiece(pos);
        if (nullptr == pBP)
            return 1;
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
    return 0;
}
