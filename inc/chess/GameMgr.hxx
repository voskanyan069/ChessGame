#ifndef __CHESS_GAME_MGR_HXX__
#define __CHESS_GAME_MGR_HXX__

#include "pieces/BasePiece.hxx"

#include <deque>

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
    struct PrintableLastMove;
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
    Player* GetThisPlayer() const;
    int GetViewersCount() const;
    std::string GetDestroyedWhitePieces() const;
    std::string GetDestroyedBlackPieces() const;
    void AddNewLastMove(const std::string& pieceChar,
            const Pieces::Position& oldPos, const Pieces::Position& newPos);
    Pieces::PrintableLastMove* GetLastMove(int idx) const;
    void AddDestroyedPiece(const Pieces::BasePiece* piece);
    void SetRoom(const Remote::Room& room);
    void SetKingHittable(const Pieces::PieceColor& color, bool status) const;
    void GetRooms();
    void ConnectToServer();
    void DisconnectFromServer();
    void StartGame();
    void SpectateGame();
    void LeaveSpectatorRoom();
    void CloseEngine();
    static std::string GetCommandsHelp();

private:
    void initPlayers();
    void initClient();
    void initRoom();
    void initMyUsername();
    std::string currentTime();
    void setPlayersUsername();
    void switchPlayerOrder();
    void joinRoom() const;
    void createRoom() const;
    bool askForReady() const;
    void waitOrLeaveRoom(const Remote::PlayerType& playerType) const;
    void readyAndWait(const Remote::Player& player) const;
    void addDestroyedWhitePiece(const Pieces::BasePiece* piece);
    void addDestroyedBlackPiece(const Pieces::BasePiece* piece);
    bool checkPiece(Pieces::BasePiece* piece) const;
    void refreshBoard(Pieces::BasePiece* piece, Pieces::Positions& positions);
    void waitForUpdates(Pieces::Positions& positions) const;
    bool movePiece(Pieces::BasePiece* piece, const Pieces::Position& newPos);
    void askCurrentPosition(Pieces::BasePiece*& piece);
    void askNewPosition(Pieces::BasePiece*& piece);
    void updateFrame();
    void updateFrame(const Remote::LastMove& lastMove);
    void closeHandler(int signal);

private:
    bool m_isGameOnline;
    bool m_isSkipWait;
    bool m_isUserGuest;
    bool m_isSignalRegistered;
    std::string m_myUsername;
    std::string m_whiteDestroyed;
    std::string m_blackDestroyed;
    Remote::Room m_room;
    Remote::ChessClient* m_client;
    Pieces::PieceColor m_turn;
    Chess::Board* m_board;
    Player* m_thisPlayer;
    Player* m_ownerPlayer;
    Player* m_guestPlayer;
    std::deque<Pieces::PrintableLastMove> m_lastMoves;
    PlayerMgr* m_playerMgr;
    CMDArguments* m_args;
};

#endif // __CHESS_GAME_MGR_HXX__
