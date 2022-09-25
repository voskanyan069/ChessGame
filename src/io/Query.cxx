#include "io/Query.hxx"
#include "utils/Types.hxx"
#include "utils/Exception.hxx"
#include "chess/GameMgr.hxx"
#include "player/PlayerMgr.hxx"
#include "pieces/PieceMgr.hxx"
#include "pieces/BasePiece.hxx"

#include <iostream>

#include <boost/algorithm/string.hpp>

Query* Query::GetInstance()
{
    static Query* instance = new Query();
    return instance;
}

Query::Query()
{
}

std::string Query::createMsgBool(const std::string& msg, bool defaultVal) const
{
    std::string resMsg = " " + msg + "? [";
    if (defaultVal)
    {
        resMsg += "Y/n";
    }
    else
    {
        resMsg += "y/N";
    }
    resMsg += "]: ";
    return resMsg;
}

bool Query::processMsgBool(const std::string& input, bool& value) const
{
    std::string resInput = input;
    boost::to_upper(resInput);
    if (resInput == "Y" || resInput == "YES")
    {
        value = true;
        return true;
    }
    else if (resInput == "N" || resInput == "NO")
    {
        value = false;
        return true;
    }
    return false;
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

bool Query::AskForReady() const
{
    bool value = false;
    std::string input;
    std::string msg = createMsgBool("Are you ready", true);
    std::cout << msg;
    std::getline(std::cin, input);
    if (input.empty())
    {
        return true;
    }
    if (!processMsgBool(input, value))
    {
        throw Utils::Exception("Incorrect answer");
    }
    return value;
}
