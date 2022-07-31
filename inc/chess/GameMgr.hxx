#ifndef __CHESS_GAME_MGR_HXX__
#define __CHESS_GAME_MGR_HXX__

#include "pieces/BasePiece.hxx"

struct Player;
class PlayerMgr;
class CMDArguments;

namespace Remote
{
    struct Room;
    struct Player;
    class ChessClient;
};

namespace Pieces
{
    class BasePiece;
};

namespace Chess
{
    class Board;
    class GameMgr;
};

class Chess::GameMgr
{
public:
    static GameMgr* GetInstance();
    GameMgr(GameMgr const&) = delete;
    void operator=(GameMgr const&) = delete;
    ~GameMgr();

private:
    GameMgr();

public:
    void InitModel();
    Pieces::PieceColor GetTurn() const;
    void SetRoom(const Remote::Room& room);
    void ConnectToServer();
    void StartGame();

private:
    void initPlayers();
    void initClient();
    void initRoom();
    void initMyUsername();
    void joinRoom() const;
    void setPlayersUsername();
    void createRoom() const;
    bool askForReady() const;
    void readyAndWait(const Remote::Player& player) const;
    bool checkPiece(Pieces::BasePiece* piece) const;
    void refreshBoard(Pieces::BasePiece* piece, Pieces::Positions& positions);
    void waitForUpdates(Pieces::Positions& positions) const;

private:
    bool m_isGameOnline;
    bool m_isUserGuest;
    std::string m_myUsername;
    Remote::Room m_room;
    Remote::ChessClient* m_client;
    Pieces::PieceColor m_turn;
    Chess::Board* m_board;
    Player* m_ownerPlayer;
    Player* m_guestPlayer;
    PlayerMgr* m_playerMgr;
    CMDArguments* m_args;
};

#endif // __CHESS_GAME_MGR_HXX__
