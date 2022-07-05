#include "chess/GameMgr.hxx"

Chess::GameMgr* Chess::GameMgr::GetInstance()
{
    static Chess::GameMgr* instance = new Chess::GameMgr();
    return instance;
}

Chess::GameMgr::GameMgr()
    : m_turn(Pieces::PieceColor::WHITE)
{
}

Pieces::PieceColor Chess::GameMgr::GetTurn()
{
    return m_turn;
}
