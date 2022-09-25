#include "player/PlayerMgr.hxx"
#include "utils/Types.hxx"
#include "utils/Exception.hxx"

#include <string>

PlayerMgr* PlayerMgr::GetInstance()
{
    static PlayerMgr* instance = new PlayerMgr();
    return instance;
}

PlayerMgr::PlayerMgr()
    : m_players(new Player*[2])
{
}

void PlayerMgr::InitPlayer(unsigned int index, Player* player)
{
    if (2 < index)
    {
        throw Utils::Exception("Out of bound");
    }
    m_players[index] = std::move(player);
}

Player* PlayerMgr::Get(int index)
{
    if (2 < index || 0 > index)
    {
        throw Utils::Exception("Out of bound");
    }
    return m_players[index];
}

Player* PlayerMgr::Get(const std::string& username)
{
    for (int i = 0; i < 2; ++i)
    {
        Player* player = m_players[i];
        if (username == player->name)
        {
            return player;
        }
    }
    return nullptr;
}
