#ifndef __CHESS_GAME_MGR_HXX__
#define __CHESS_GAME_MGR_HXX__

#include "pieces/BasePiece.hxx"

namespace Chess
{
    class GameMgr;
};

class Chess::GameMgr
{
public:
    static GameMgr* GetInstance();
    GameMgr(GameMgr const&) = delete;
    void operator=(GameMgr const&) = delete;

private:
    GameMgr();

public:
    Pieces::PieceColor GetTurn();

private:
    Pieces::PieceColor m_turn;
};

#endif // __CHESS_GAME_MGR_HXX__
