#include "server/ChessServiceImpl.hxx"
#include "utils/Types.hxx"
#include "utils/P2C_Converter.hxx"
#include "utils/C2P_Converter.hxx"

#include <iostream>
#include <thread>
#include <chrono>

#include <grpcpp/grpcpp.h>


Remote::ChessServiceImpl::ChessServiceImpl()
{
}

Remote::ChessServiceImpl::~ChessServiceImpl()
{
    m_mapRooms.clear();
}

bool Remote::ChessServiceImpl::doCheckRoomSettings(
        const Proto::RoomSettings& settings, std::string& message) const
{
    const auto& it = m_mapRooms.find(settings.name());
    if (m_mapRooms.end() == it)
    {
        message = "Room with this name does not exists";
        return false;
    }
    if (settings.password() != it->second.password)
    {
        message = "Incorrect passsword of the room";
        return false;
    }
    return true;
}

grpc::Status Remote::ChessServiceImpl::GetRooms(
        grpc::ServerContext* context,
        const Proto::Empty* request,
        Proto::RoomsInfo* response)
{
    for (const auto& room : m_mapRooms)
    {
        Proto::GetRoomsType* protoRoom = response->add_room();
        bool is_closed = ("" != room.second.password);
        protoRoom->set_name(room.first);
        protoRoom->set_is_closed(is_closed);
    }
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::IsRoomExists(
        grpc::ServerContext* context,
        const Proto::String* request,
        Proto::Bool* response)
{
    std::string name = request->value();
    const auto& it = m_mapRooms.find(name);
    if (m_mapRooms.end() == it)
    {
        response->set_value(false);
    }
    else
    {
        response->set_value(true);
    }
    return grpc::Status::OK;
}

void Remote::ChessServiceImpl::closeRoom(Remote::ServerRoom& room) const
{
    room.exists = false;
    room.closeConditionVar->notify_one();
}

void Remote::ChessServiceImpl::initMutexAndConditionVar(
        std::unique_ptr<boost::mutex>& mutex,
        std::unique_ptr<boost::condition_variable>& condVar) const
{
    mutex.reset(new boost::mutex());
    condVar.reset(new boost::condition_variable());
}

grpc::Status Remote::ChessServiceImpl::CreateRoom(
        grpc::ServerContext* context,
        const Proto::RoomWithUsername* request,
        Proto::Empty* response)
{
    std::string name = request->room().name();
    if (name.empty())
    {
        return grpc::Status(grpc::StatusCode::CANCELLED,
                "Room name is not correct");
    }
    const auto& it = m_mapRooms.find(name);
    if (m_mapRooms.end() != it)
    {
        return grpc::Status(grpc::StatusCode::CANCELLED,
                "Room with this name already exists");
    }
    Remote::ServerRoom& room = m_mapRooms[name];
    room.exists = true;
    room.ownerPlayer.username = request->username();
    room.password = request->room().password();
    room.ownerPlayer.isReady = false;
    room.guestPlayer.isReady = false;
    room.isLastMoveRead = false;
    initMutexAndConditionVar(room.waitMutex, room.waitConditionVar);
    initMutexAndConditionVar(room.moveMutex, room.moveConditionVar);
    initMutexAndConditionVar(room.closeMutex, room.closeConditionVar);
    std::cout << context->peer() << " has created " << name
        << " room" << std::endl;
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::JoinRoom(
        grpc::ServerContext* context,
        const Proto::RoomWithUsername* request,
        Proto::Empty* response)
{
    std::string errMsg = "";
    if (!doCheckRoomSettings(request->room(), errMsg))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, errMsg);
    }
    Remote::ServerRoom& room = m_mapRooms[request->room().name()];
    if (!room.ownerPlayer.username.empty() &&
        !room.guestPlayer.username.empty())
    {
        return grpc::Status(grpc::StatusCode::CANCELLED,"The room is not free");
    }
    room.guestPlayer.username = request->username();
    if (room.ownerPlayer == room.guestPlayer)
    {
        return grpc::Status(grpc::StatusCode::CANCELLED,
                "The username is already busy");
    }
    std::cout << context->peer() << " has joined to " << request->room().name()
        << " room" << std::endl;
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::LeaveRoom(
        grpc::ServerContext* context,
        const Proto::RoomWithUsername* request,
        Proto::Empty* response)
{
    std::string errMsg = "";
    if (!doCheckRoomSettings(request->room(), errMsg))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, errMsg);
    }
    Remote::ServerRoom& room = m_mapRooms[request->room().name()];
    if (request->username() == room.ownerPlayer.username ||
            request->username() == room.guestPlayer.username)
    {
        closeRoom(room);
    }
    else
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, "Incorrect username");
    }
    std::cout << context->peer() << " has leaved " << request->room().name()
        << " room" << std::endl;
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::WaitForClose(
        grpc::ServerContext* context,
        const Proto::RoomSettings* request,
        Proto::Empty* response)
{
    std::string errMsg = "";
    if (!doCheckRoomSettings(*request, errMsg))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, errMsg);
    }
    Remote::ServerRoom& room = m_mapRooms[request->name()];
    boost::mutex::scoped_lock lock(*(room.closeMutex));
    while (room.exists)
    {
        room.closeConditionVar->wait(lock);
    }
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::SpectateRoom(
        grpc::ServerContext* context,
        const Proto::String* request,
        grpc::ServerWriter<Proto::LastMoveInfo>* writer)
{
    Proto::LastMoveInfo lastMove;
    std::string name = request->value();
    if (m_mapRooms.end() == m_mapRooms.find(name))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, "Room doesn't exists");
    }
    Remote::ServerRoom& room = m_mapRooms[name];
    if (room.ownerPlayer.username.empty() || room.guestPlayer.username.empty())
    {
        return grpc::Status(grpc::StatusCode::CANCELLED,
                "The game is not started yet");
    }
    std::cout << context->peer() << " has joined as spectator to "
        << name << " room" << std::endl;
    Remote::Spectator spectator;
    spectator.isOnline = true;
    spectator.isLastMoveRead = false;
    spectator.uid = context->peer();
    initMutexAndConditionVar(spectator.mutex, spectator.conditionVar);
    room.vecSpectators.push_back(&spectator);
    for (const auto& move : room.vecMovesHistory)
    {
        C2P_Converter::ConvertLastMoveInfo(move, lastMove);
        writer->Write(lastMove);
    }
    while (room.exists)
    {
        spectator.isLastMoveRead = false;
        boost::mutex::scoped_lock lock(*(spectator.mutex));
        while (!spectator.isLastMoveRead)
        {
            spectator.conditionVar->wait(lock);
        }
        if (!spectator.isOnline)
        {
            break;
        }
        C2P_Converter::ConvertLastMoveInfo(room.spectatorLastMove, lastMove);
        writer->Write(lastMove);
    }
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::LeaveSpectatorRoom(
        grpc::ServerContext* context,
        const Proto::String* request,
        Proto::Empty* response)
{
    std::string name = request->value();
    if (m_mapRooms.end() == m_mapRooms.find(name))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, "Room doesn't exists");
    }
    Remote::ServerRoom& room = m_mapRooms[name];
    Remote::Spectator* spectator = nullptr;
    for (int i = 0; i < room.vecSpectators.size(); ++i)
    {
        spectator = room.vecSpectators.at(i);
        if (context->peer() == spectator->uid)
        {
            spectator->isOnline = false;
            spectator->conditionVar->notify_all();
            room.vecSpectators.erase(room.vecSpectators.begin() + i);
            break;
        }
    }
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::GetViewersCount(
        grpc::ServerContext* context,
        const Proto::String* request,
        Proto::Integer* response)
{
    response->set_value(0);
    std::string name = request->value();
    if (m_mapRooms.end() == m_mapRooms.find(name))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, "Room doesn't exists");
    }
    Remote::ServerRoom& room = m_mapRooms[name];
    response->set_value(room.vecSpectators.size());
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::GetUsername(
        grpc::ServerContext* context,
        const Proto::RoomWithUsername* request,
        Proto::String* response)
{
    std::string errMsg = "";
    if (!doCheckRoomSettings(request->room(), errMsg))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, errMsg);
    }
    Remote::ServerRoom& room = m_mapRooms[request->room().name()];
    std::string username = request->username();
    if (username == room.ownerPlayer.username)
    {
        response->set_value(room.guestPlayer.username);
    }
    else if (username == room.guestPlayer.username)
    {
        response->set_value(room.ownerPlayer.username);
    }
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::WaitForReady(
        grpc::ServerContext* context,
        const Proto::RoomSettings* request,
        Proto::Empty* response)
{
    std::string errMsg = "";
    if (!doCheckRoomSettings(*request, errMsg))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, errMsg);
    }
    Remote::ServerRoom& room = m_mapRooms[request->name()];
    boost::mutex::scoped_lock lock(*(room.waitMutex));
    while (!room.ownerPlayer.isReady || !room.guestPlayer.isReady)
    {
        room.waitConditionVar->wait(lock);
    }
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::Ready(
        grpc::ServerContext* context,
        const Proto::ReadyRequest* request,
        Proto::Empty* response)
{
    std::string errMsg = "";
    if (!doCheckRoomSettings(request->room(), errMsg))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, errMsg);
    }
    Remote::ServerRoom& room = m_mapRooms[request->room().name()];
    if (Proto::PlayerType::OWNER == request->playertype())
    {
        room.ownerPlayer.isReady = request->isready();
    }
    else if (Proto::PlayerType::GUEST == request->playertype())
    {
        room.guestPlayer.isReady = request->isready();
    }
    room.waitConditionVar->notify_all();
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::MovePiece(
        grpc::ServerContext* context,
        const Proto::MoveRequest* request,
        Proto::Empty* response)
{
    std::string errMsg = "";
    if (!doCheckRoomSettings(request->room(), errMsg))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, errMsg);
    }
    Remote::ServerRoom& room = m_mapRooms[request->room().name()];
    Pieces::Position oldPos;
    Pieces::Position newPos;
    P2C_Converter::ConvertPosition(request->oldposition(), oldPos);
    P2C_Converter::ConvertPosition(request->newposition(), newPos);
    room.lastMove = Remote::LastMove(oldPos, newPos);
    room.spectatorLastMove = Remote::LastMove(oldPos, newPos);
    room.isLastMoveRead = true;
    room.moveConditionVar->notify_one();
    for (auto& spectator : room.vecSpectators)
    {
        spectator->isLastMoveRead = true;
        spectator->conditionVar->notify_all();
    }
    room.vecMovesHistory.push_back(room.spectatorLastMove);
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::ReadPieceMove(
        grpc::ServerContext* context,
        const Proto::RoomSettings* request,
        Proto::LastMoveInfo* response)
{
    std::string errMsg = "";
    if (!doCheckRoomSettings(*request, errMsg))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, errMsg);
    }
    Remote::ServerRoom& room = m_mapRooms[request->name()];
    bool bStopCloseWaiting = false;
    room.isLastMoveRead = false;
    boost::mutex::scoped_lock lock(*(room.moveMutex));
    while (!room.isLastMoveRead)
    {
        room.moveConditionVar->wait(lock);
    }
    if (!room.lastMove.IsNull())
    {
        C2P_Converter::ConvertLastMoveInfo(room.lastMove, *response);
        room.lastMove.Clean();
    }
    return grpc::Status::OK;
}
