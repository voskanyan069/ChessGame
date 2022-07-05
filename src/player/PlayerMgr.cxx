#include "player/PlayerMgr.hxx"
#include "player/Player.hxx"
#include "utils/Exception.hxx"

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

Player* PlayerMgr::Get(unsigned int index)
{
    if (2 < index)
    {
        throw Utils::Exception("Out of bound");
    }
    return m_players[index];
}
