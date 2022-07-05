#ifndef __PLAYER_PLAYER_MGR_HXX__
#define __PLAYER_PLAYER_MGR_HXX__

class Player;

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
    Player* Get(unsigned int index);

private:
    Player** m_players;
};

#endif // __PLAYER_PLAYER_MGR_HXX__
