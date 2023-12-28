#include "chess/GameMgr.hxx"
#include "chess/Board.hxx"
#include "sys/SignalHandler.hxx"
#include "utils/Types.hxx"
#include "io/Query.hxx"
#include "io/Logger.hxx"
#include "args/CMDArgument.hxx"
#include "client/ChessClient.hxx"
#include "pieces/BasePiece.hxx"
#include "player/PlayerMgr.hxx"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <thread>

Chess::GameMgr* Chess::GameMgr::GetInstance()
{
    static Chess::GameMgr* instance = new Chess::GameMgr();
    return instance;
}

Chess::GameMgr::GameMgr()
    : m_isGameOnline(false)
    , m_isUserGuest(false)
    , m_isSignalRegistered(false)
    , m_isSkipWait(false)
    , m_myUsername("")
    , m_turn(Pieces::PieceColor::WHITE)
    , m_room("", "")
    , m_client(nullptr)
    , m_thisPlayer(nullptr)
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
    delete m_thisPlayer;
    delete m_ownerPlayer;
    delete m_guestPlayer;
}

bool Chess::GameMgr::askForReady() const
{
    Logger::GetInstance()->PrintEndl();
    bool isReady = Query::GetInstance()->AskForReady();
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

void Chess::GameMgr::waitOrLeaveRoom(const Remote::PlayerType& playerType) const
{
    bool isReady = askForReady();
    if (isReady)
    {
        readyAndWait({playerType, isReady});
    }
    else
    {
        m_client->LeaveRoom(m_room);
        Logger::GetInstance()->Print(INFO, "Room has been left, Bye...");
        std::exit(-1);
    }
}

void Chess::GameMgr::joinRoom() const
{
    Logger::GetInstance()->Print(INFO, "Trying to join %s...", m_room.name);
    m_client->JoinRoom(m_room);
    Logger::GetInstance()->Print(INFO, "Joined to %s", m_room.name);
    waitOrLeaveRoom(Remote::PlayerType::GUEST);
}

void Chess::GameMgr::createRoom() const
{
    Logger::GetInstance()->Print(INFO, "Trying to create room %s...",
            m_room.name);
    m_client->CreateRoom(m_room);
    Logger::GetInstance()->Print(INFO, "Created and joined to %s", m_room.name);
    waitOrLeaveRoom(Remote::PlayerType::OWNER);
}

bool Chess::GameMgr::checkPiece(Pieces::BasePiece* piece) const
{
    if (nullptr == piece)
    {
        Logger::GetInstance()->PrintEndl();
        Logger::GetInstance()->Print(ERROR,
                "Error: Piece in selected position doesn't exists");
        Logger::GetInstance()->PrintEndl();
        return false;
    }
    if (piece->GetColor() != m_turn)
    {
        Logger::GetInstance()->PrintEndl();
        Logger::GetInstance()->Print(ERROR,
                "Error: The color of the piece is not correct");
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
    m_ownerPlayer->color = Pieces::PieceColor::WHITE;
    m_guestPlayer->color = Pieces::PieceColor::BLACK;
}

void Chess::GameMgr::switchPlayerOrder()
{
    m_turn = (m_turn == Pieces::WHITE) ? Pieces::BLACK : Pieces::WHITE;
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

std::string Chess::GameMgr::currentTime()
{
    auto now = std::chrono::system_clock::now();
    time_t time_now = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(localtime(&time_now), "%T");
    return ss.str();
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

Chess::GameMgr::MoveStatus Chess::GameMgr::movePiece(Pieces::BasePiece* piece,
        const Pieces::Position& newPos)
{
    Pieces::Position pos = piece->GetPosition();
    try
    {
        piece->Move(newPos);
        m_client->MovePiece(m_room, pos, newPos);
        return MoveStatus::Moved;
    }
    catch (const Utils::Exception& e)
    {
        Logger::GetInstance()->PrintEndl();
        Logger::GetInstance()->Print(e);
        if ( e.GetErrorCode() == 2 )
        {
            return MoveStatus::KingHittable;
        }
        return MoveStatus::Fail;
    }
}

void Chess::GameMgr::askCurrentPosition(Pieces::BasePiece*& piece)
{
    Pieces::Position pos;
    Pieces::Positions positions;
    try
    {
        Query::GetInstance()->AskPosition("Current position", pos);
    }
    catch (const Utils::Exception& e)
    {
        switch (e.GetErrorCode())
        {
        case 3:
            {
                Logger::GetInstance()->PrintBoard();
                break;
            }
        case 4:
            {
                CloseEngine();
                break;
            }
        case 5:
            {
                Logger::GetInstance()->ReverseBoard();
                Logger::GetInstance()->PrintBoard();
                break;
            }
        default:
            {
                Logger::GetInstance()->PrintEndl();
                Logger::GetInstance()->Print(e);
                Logger::GetInstance()->PrintEndl();
            }
        }
        askCurrentPosition(piece);
        return;
    }
    piece = m_board->GetPiece(pos);
    if (!checkPiece(piece))
    {
        askCurrentPosition(piece);
        return;
    }
    piece->GetAvailableMoves(positions);
    m_board->SetAvailableMoves(positions);
    Logger::GetInstance()->PrintBoard();
}

void Chess::GameMgr::askNewPosition(Pieces::BasePiece*& piece)
{
    Pieces::Position newPos;
    try
    {
        Query::GetInstance()->AskPosition("New position", newPos);
    }
    catch (const Utils::Exception& e)
    {
        switch (e.GetErrorCode())
        {
        case 2:
            {
                Logger::GetInstance()->PrintBoard();
                askCurrentPosition(piece);
                break;
            }
        case 3:
            {
                Pieces::Positions positions;
                piece->GetAvailableMoves(positions);
                m_board->SetAvailableMoves(positions);
                Logger::GetInstance()->PrintBoard();
                break;
            }
        case 4:
            {
                CloseEngine();
                break;
            }
        case 5:
            {
                Logger::GetInstance()->ReverseBoard();
                Pieces::Positions positions;
                piece->GetAvailableMoves(positions);
                m_board->SetAvailableMoves(positions);
                Logger::GetInstance()->PrintBoard();
                break;
            }
        default:
            {
                Logger::GetInstance()->PrintEndl();
                Logger::GetInstance()->Print(e);
                Logger::GetInstance()->PrintEndl();
            }
        }
        askNewPosition(piece);
        return;
    }
    Chess::GameMgr::MoveStatus moveStatus = movePiece(piece, newPos);
    if ( moveStatus == Chess::GameMgr::KingHittable )
    {
        m_board->DestroyEmpties();
        Logger::GetInstance()->PrintBoard();
        askCurrentPosition(piece);
        askNewPosition(piece);
        return;
    }
    else if ( moveStatus == Chess::GameMgr::Fail )
    {
        askNewPosition(piece);
        return;
    }
    switchPlayerOrder();
}

void Chess::GameMgr::updateFrame()
{
    Pieces::Positions positions;
    Pieces::BasePiece* piece = nullptr;
    if (!m_isSkipWait && m_turn != m_thisPlayer->color)
    {
        waitForUpdates(positions);
        switchPlayerOrder();
    }
    Logger::GetInstance()->PrintBoard();
    askCurrentPosition(piece);
    askNewPosition(piece);
    m_isSkipWait = false;
}

void Chess::GameMgr::updateFrame(const Remote::LastMove& lastMove)
{
    Pieces::Positions positions;
    Pieces::BasePiece* piece = m_board->GetPiece(lastMove.oldPos);
    piece->GetAvailableMoves(positions);
    m_board->SetAvailableMoves(positions);
    piece->Move(lastMove.newPos);
    m_board->DestroyEmpties();
    Logger::GetInstance()->PrintBoard();
}

void Chess::GameMgr::processSpectatorCommand(const std::string& sCmd)
{
    if ("?" == sCmd || "help" == sCmd)
    {
        Logger::GetInstance()->PrintEndl();
        Logger::GetInstance()->PrintHelp(GetCommandsHelp());
        Logger::GetInstance()->PrintEndl();
    }
    else if ("ref" == sCmd || "refresh" == sCmd)
    {
        Logger::GetInstance()->PrintBoard();
    }
    else if ("rev" == sCmd || "reverse" == sCmd)
    {
        Logger::GetInstance()->ReverseBoard();
        Logger::GetInstance()->PrintBoard();
    }
    else if ("close" == sCmd || "quit" == sCmd || "exit" == sCmd)
    {
        LeaveSpectatorRoom();
        CloseEngine();
    }
    else
    {
        std::string msg = "Unknown command \"" + sCmd +
            "\", enter \"?\" or \"help\" to see available commands";
        Logger::GetInstance()->PrintEndl();
        Logger::GetInstance()->Print(ERROR, msg);
        Logger::GetInstance()->PrintEndl();
    }
}

void Chess::GameMgr::spectatorCommandsInput()
{
    std::thread thObj([&] {
            std::string cmd;
            try
            {
                Query::GetInstance()->AskSpectatorCommand(cmd);
            }
            catch (const Utils::Exception& e)
            {
                Logger::GetInstance()->PrintEndl();
                Logger::GetInstance()->Print(e);
                Logger::GetInstance()->PrintEndl();
            }
            processSpectatorCommand(cmd);
            spectatorCommandsInput();
    });
    thObj.detach();
}

void Chess::GameMgr::StartGame()
{
    m_isGameOnline = true;
    while (m_isGameOnline)
    {
        updateFrame();
    }
}

void Chess::GameMgr::SpectateGame()
{
    std::function<void(int)> fHandler = [this] (int signal) {
        LeaveSpectatorRoom();
    };
    Sys::SignalHandler::SetCtrlCHandler(fHandler);
    Logger::GetInstance()->PrintBoard();
    try
    {
        Remote::MoveCallback fCallback = [this] (const Remote::LastMove& lm) {
            updateFrame(lm);
            spectatorCommandsInput();
        };
        m_client->SpectateRoom(m_room.name, fCallback);
    }
    catch (const Utils::Exception& e)
    {
        Logger::GetInstance()->Print(e);
        std::exit(1);
    }
}

void Chess::GameMgr::LeaveSpectatorRoom()
{
    Logger::GetInstance()->PrintEndl();
    Logger::GetInstance()->Print(INFO, "Leaving spectator room...");
    Logger::GetInstance()->PrintEndl();
    m_client->LeaveSpectatorRoom(m_room.name);
    std::exit(1);
}

void Chess::GameMgr::CloseEngine()
{
    m_isGameOnline = false;
    Logger::GetInstance()->PrintEndl();
    Logger::GetInstance()->Print(INFO, "Closing game...");
    Logger::GetInstance()->PrintEndl();
    DisconnectFromServer();
    std::exit(1);
}

Pieces::PieceColor Chess::GameMgr::GetTurn() const
{
    return m_turn;
}

Player* Chess::GameMgr::GetThisPlayer() const
{
    return m_thisPlayer;
}

int Chess::GameMgr::GetViewersCount() const
{
    return m_client->GetViewersCount(m_room.name);
}

std::string Chess::GameMgr::GetDestroyedWhitePieces() const
{
    return m_whiteDestroyed;
}

std::string Chess::GameMgr::GetDestroyedBlackPieces() const
{
    return m_blackDestroyed;
}

void Chess::GameMgr::AddNewLastMove(const std::string& pieceChar,
        const Pieces::Position& oldPos, const Pieces::Position& newPos)
{
    if ( m_lastMoves.size() > 7 )
    {
        m_lastMoves.pop_front();
    }
    std::string time = currentTime();
    m_lastMoves.emplace_back(pieceChar, time, oldPos, newPos);
}

Pieces::PrintableLastMove* Chess::GameMgr::GetLastMove(int idx) const
{
    if (idx >= m_lastMoves.size())
    {
        return nullptr;
    }
    return const_cast<Pieces::PrintableLastMove*>(&m_lastMoves[idx]);
}

void Chess::GameMgr::AddDestroyedPiece(const Pieces::BasePiece* piece)
{
    if (0 == (int)piece->GetColor())
    {
        addDestroyedWhitePiece(piece);
    }
    else
    {
        addDestroyedBlackPiece(piece);
    }
}

void Chess::GameMgr::addDestroyedWhitePiece(const Pieces::BasePiece* piece)
{
    m_whiteDestroyed += piece->GetPieceChar();
}

void Chess::GameMgr::addDestroyedBlackPiece(const Pieces::BasePiece* piece)
{
    m_blackDestroyed += piece->GetPieceChar();
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

void Chess::GameMgr::GetRooms()
{
    std::vector<std::string> vRoomNames;
    m_client->GetRooms(vRoomNames);
    Logger::GetInstance()->PrintEndl();
    Logger::GetInstance()->Print(INFO, "Available rooms in the server:");
    Logger::GetInstance()->PrintEndl();
    for (int i = 0; i < vRoomNames.size(); ++i)
    {
        Logger::GetInstance()->Print(INFO, "%d: %s", 1 + i, vRoomNames.at(i));
    }
    Logger::GetInstance()->PrintEndl();
}

void Chess::GameMgr::ConnectToServer()
{
    std::function<void(int)> fHandler = [this] (int signal) {
        CloseEngine();
    };
    Sys::SignalHandler::SetCtrlCHandler(fHandler);
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
    m_thisPlayer = m_playerMgr->Get(m_myUsername);
}

void Chess::GameMgr::DisconnectFromServer()
{
}

std::string Chess::GameMgr::GetCommandsHelp()
{
    static std::string msg = "Commands list (Should be written in position "
                             "input)\nref/refresh:\t\tPrints current state of "
                             "the board\nrev/reverse:\t\tReverse the board\n"
                             "ESC:\t\t\tReturns from new position to the "
                             "current position input\nclose/quit/exit:"
                             "\tClose game\n";
    return msg;
}
