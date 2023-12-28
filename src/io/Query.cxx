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
    boost::to_lower(resInput);
    if (resInput == "y" || resInput == "yes")
    {
        value = true;
        return true;
    }
    else if (resInput == "n" || resInput == "no")
    {
        value = false;
        return true;
    }
    return false;
}

bool Query::processPawnReplacement(const std::string& input, int& value) const
{
    if (input.empty())
    {
        return false;
    }
    try
    {
        std::stringstream ss(input);
        if ((ss >> value).fail() || !(ss >> std::ws).eof())
        {
            throw std::bad_cast();
        }
        return true;
    }
    catch (...)
    {
        return false;
    }
}

void Query::printUsername() const
{
    Pieces::PieceColor turn = Chess::GameMgr::GetInstance()->GetTurn();
    Player* player = PlayerMgr::GetInstance()->Get(turn);
    if (nullptr == player)
    {
        throw Utils::Exception("Not initialized player");
    }
    std::cout << " [" << player->name << "] ";
}

void Query::checkSpectatorCommand(const std::string& input) const
{
    if (input.empty())
    {
        throw Utils::Exception("Empty command");
    }
}

/*
void Query::AskPosition(const std::string& msg, Pieces::Position& pos) const
{
    std::string input;
    printUsername();
    std::cout << msg << ": ";
    std::getline(std::cin, input);
    Pieces::ConvertPosition(input, pos);
}
*/

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
    boost::to_lower(input);
    if ("refresh" == input || "ref" == input)
    {
        throw Utils::Exception("Refresh board", "Signal", 3);
    }
    if ("close" == input || "quit" == input || "exit" == input)
    {
        throw Utils::Exception("Close game", "Signal", 4);
    }
    if ("rev" == input || "reverse" == input)
    {
        throw Utils::Exception("Reverse board", "Signal", 5);
    }
    for (const auto& c : input)
    {
        if (27 == c)
        {
            throw Utils::Exception("Select new piece to move", "Error", 2);
        }
    }
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

Pieces::PawnReplacements Query::AskPawnReplacement() const
{
    int value = -1;
    std::string input;
    std::string msg = "Please select new piece (1:T, 2:N, 3:P, 4:DZ)";
    printUsername();
    std::cout << msg << ": ";
    std::getline(std::cin, input);
    if (!processPawnReplacement(input, value))
    {
        throw Utils::Exception("Incorrect answer");
    }
    return (Pieces::PawnReplacements)value;
}

void Query::AskSpectatorCommand(std::string& command) const
{
    std::string input;
    std::cout << " Command(?) > ";
    std::getline(std::cin, input);
    checkSpectatorCommand(input);
    boost::to_lower(input);
    command = input;
}
