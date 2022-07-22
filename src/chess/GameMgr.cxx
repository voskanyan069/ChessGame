#include "chess/GameMgr.hxx"

Chess::GameMgr* Chess::GameMgr::GetInstance()
{
    static Chess::GameMgr* instance = new Chess::GameMgr();
    return instance;
}

Chess::GameMgr::GameMgr()
    : m_turn(Pieces::PieceColor::WHITE)
    , m_room("", "")
{
}

Pieces::PieceColor Chess::GameMgr::GetTurn()
{
    return m_turn;
}

void Chess::GameMgr::SetRoom(const Remote::Room& room)
{
    m_room = Remote::Room(room.name, room.password);
}
