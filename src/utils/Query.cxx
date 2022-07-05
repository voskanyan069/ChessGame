#include "utils/Query.hxx"
#include "utils/Exception.hxx"
#include "chess/GameMgr.hxx"
#include "player/Player.hxx"
#include "player/PlayerMgr.hxx"
#include "pieces/PieceMgr.hxx"
#include "pieces/BasePiece.hxx"

#include <iostream>

Query* Query::GetInstance()
{
    static Query* instance = new Query();
    return instance;
}

Query::Query()
{
}

void Query::AskPosition(const std::string& msg, Pieces::Position& pos) const
{
    std::string input;
    Pieces::PieceColor turn = Chess::GameMgr::GetInstance()->GetTurn();
    Player* player = PlayerMgr::GetInstance()->Get(turn);
    if (nullptr == player)
    {
        throw Utils::Exception("Not initialized player");
    }
    std::cout << " [" << player->name << "] " << msg << ": ";
    std::getline(std::cin, input);
    Pieces::ConvertPosition(input, pos);
}
