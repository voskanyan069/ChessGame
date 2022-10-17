#ifndef __PLAYER_PLAYER_MGR_HXX__
#define __PLAYER_PLAYER_MGR_HXX__

#include <string>

struct Player;

class PlayerMgr
{
public:
    static PlayerMgr* GetInstance();
    PlayerMgr(PlayerMgr const&) = delete;
    void operator=(PlayerMgr const&) = delete;

private:
    PlayerMgr();

public:
    void InitPlayer(unsigned int index, Player* player);
    Player* Get(int index);
    Player* Get(const std::string& username);

private:
    Player** m_players;
};

#endif // __PLAYER_PLAYER_MGR_HXX__
