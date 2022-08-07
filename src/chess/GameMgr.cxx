#include "chess/GameMgr.hxx"
#include "chess/Board.hxx"
#include "utils/Types.hxx"
#include "io/Query.hxx"
#include "io/Logger.hxx"
#include "args/CMDArgument.hxx"
#include "client/ChessClient.hxx"
#include "pieces/BasePiece.hxx"
#include "player/Player.hxx"
#include "player/PlayerMgr.hxx"

#include <iostream>

Chess::GameMgr* Chess::GameMgr::GetInstance()
{
    static Chess::GameMgr* instance = new Chess::GameMgr();
    return instance;
}

Chess::GameMgr::GameMgr()
    : m_isGameOnline(false)
    , m_isUserGuest(false)
    , m_myUsername("")
    , m_turn(Pieces::PieceColor::WHITE)
    , m_room("", "")
    , m_client(nullptr)
    , m_ownerPlayer(nullptr)
    , m_guestPlayer(nullptr)
    , m_board(Chess::Board::GetInstance())
    , m_playerMgr(PlayerMgr::GetInstance())
    , m_args(CMDArguments::GetInstance())
{
}

Chess::GameMgr::~GameMgr()
{
    delete m_client;
    delete m_ownerPlayer;
    delete m_guestPlayer;
}

bool Chess::GameMgr::askForReady() const
{
    Logger::GetInstance()->PrintEndl();
    bool isReady = Query::GetInstance()->AskForReady();
    if (!isReady)
    {
        std::exit(1);
    }
    Logger::GetInstance()->PrintEndl();
    return isReady;
}

void Chess::GameMgr::readyAndWait(const Remote::Player& player) const
{
    try
    {
        m_client->Ready(m_room, player);
        Logger::GetInstance()->Print(INFO, "Waiting for ready opponent...");
        m_client->WaitForReady(m_room);
    }
    catch (const Utils::Exception& e)
    {
        Logger::GetInstance()->Print(e);
    }
}

void Chess::GameMgr::joinRoom() const
{
    Logger::GetInstance()->Print(INFO, "Trying to join %s...", m_room.name);
    m_client->JoinRoom(m_room);
    Logger::GetInstance()->Print(INFO, "Joined to %s", m_room.name);
    bool isReady = askForReady();
    readyAndWait({Remote::PlayerType::GUEST, isReady});
}

void Chess::GameMgr::createRoom() const
{
    Logger::GetInstance()->Print(INFO, "Trying to create room %s...",
            m_room.name);
    m_client->CreateRoom(m_room);
    Logger::GetInstance()->Print(INFO, "Created and joined to %s", m_room.name);
    bool isReady = askForReady();
    readyAndWait({Remote::PlayerType::OWNER, isReady});
}

bool Chess::GameMgr::checkPiece(Pieces::BasePiece* piece) const
{
    if (nullptr == piece)
    {
        Logger::GetInstance()->PrintEndl();
        Logger::GetInstance()->Print(ERROR,
                "Piece in selected position doesn't exists");
        Logger::GetInstance()->PrintEndl();
        return false;
    }
    return true;
}

void Chess::GameMgr::refreshBoard(Pieces::BasePiece* piece,
        Pieces::Positions& positions)
{
}

void Chess::GameMgr::setPlayersUsername()
{
    std::string owName, guName;
    owName = m_isUserGuest ? m_client->GetOpponentUsername(m_room):m_myUsername;
    guName = m_isUserGuest ? m_myUsername:m_client->GetOpponentUsername(m_room);
    m_ownerPlayer->name = owName;
    m_guestPlayer->name = guName;
}

void Chess::GameMgr::initClient()
{
    std::string hostname = m_args->Find("host")->Get<std::string>();
    int port = m_args->Find("port")->Get<int>();
    hostname += ":" + std::to_string(port);
    m_client = new Remote::ChessClient(hostname, m_myUsername);
    Logger::GetInstance()->Print(INFO, "Connecting to %s...", hostname);
}

void Chess::GameMgr::initRoom()
{
    m_room.name = m_args->Find("room")->Get<std::string>();
    m_room.password = m_args->Find("password")->Get<std::string>();
}

void Chess::GameMgr::initMyUsername()
{
    m_myUsername = m_args->Find("username")->Get<std::string>();
}

void Chess::GameMgr::initPlayers()
{
    m_ownerPlayer = new Player();
    m_guestPlayer = new Player();
    m_playerMgr->InitPlayer(Pieces::PieceColor::WHITE, m_ownerPlayer);
    m_playerMgr->InitPlayer(Pieces::PieceColor::BLACK, m_guestPlayer);
}

void Chess::GameMgr::waitForUpdates(Pieces::Positions& positions) const
{
    Remote::LastMove lastMove;
    Pieces::BasePiece* piece = nullptr;
    positions.clear();
    Logger::GetInstance()->PrintBoard();
    Logger::GetInstance()->Print(INFO, "Waiting for opponent move...");
    m_client->ReadLastMove(m_room, lastMove);
    piece = m_board->GetPiece(lastMove.oldPos);
    piece->GetAvailableMoves(positions);
    piece->Move(lastMove.newPos);
    positions.clear();
}

bool Chess::GameMgr::movePiece(Pieces::BasePiece* piece,
        const Pieces::Position& newPos)
{
    Pieces::Position pos = piece->GetPosition();
    try
    {
        piece->Move(newPos);
        m_client->MovePiece(m_room, pos, newPos);
        return true;
    }
    catch (const Utils::Exception& e)
    {
        Logger::GetInstance()->PrintEndl();
        Logger::GetInstance()->Print(ERROR, "%s", e.GetMessage());
        Logger::GetInstance()->PrintEndl();
        return false;
    }
}

void Chess::GameMgr::askCurrentPosition(Pieces::BasePiece*& piece,
        Pieces::Position& pos, Pieces::Positions& positions)
{
    Query::GetInstance()->AskPosition("Current position", pos);
    piece = m_board->GetPiece(pos);
    if (!checkPiece(piece))
    {
        askCurrentPosition(piece, pos, positions);
        return;
    }
    piece->GetAvailableMoves(positions);
    m_board->SetAvailableMoves(positions);
    Logger::GetInstance()->PrintBoard();
}

void Chess::GameMgr::askNewPosition(Pieces::BasePiece* piece,
        Pieces::Position& newPos)
{
    Query::GetInstance()->AskPosition("New position", newPos);
    if (!movePiece(piece, newPos))
    {
        askNewPosition(piece, newPos);
        return;
    }
}

void Chess::GameMgr::updateFrame(
        Pieces::BasePiece* piece,
        Pieces::Position& pos,
        Pieces::Position& newPos,
        Pieces::Positions& positions)
{
    if (!m_isUserGuest)
        waitForUpdates(positions);
    Logger::GetInstance()->PrintBoard();
    askCurrentPosition(piece, pos, positions);
    askNewPosition(piece, newPos);
    if (m_isUserGuest)
        waitForUpdates(positions);
    Logger::GetInstance()->PrintBoard();
}

void Chess::GameMgr::StartGame()
{
    Pieces::Position pos;
    Pieces::Position newPos;
    Pieces::Positions positions;
    Pieces::BasePiece* piece = nullptr;
    m_isGameOnline = true;
    while (m_isGameOnline)
    {
        updateFrame(piece, pos, newPos, positions);
    }
}

Pieces::PieceColor Chess::GameMgr::GetTurn() const
{
    return m_turn;
}

void Chess::GameMgr::SetRoom(const Remote::Room& room)
{
    m_room = Remote::Room(room.name, room.password);
}

void Chess::GameMgr::InitModel()
{
    initMyUsername();
    initClient();
    initRoom();
    initPlayers();
}

void Chess::GameMgr::ConnectToServer()
{
    try
    {
        if (m_client->IsRoomExists(m_room.name))
        {
            m_isUserGuest = true;
            joinRoom();
        }
        else
        {
            m_isUserGuest = false;
            createRoom();
        }
    }
    catch (const Utils::Exception& e)
    {
        Logger::GetInstance()->Print(e);
        std::exit(1);
    }
    setPlayersUsername();
}
