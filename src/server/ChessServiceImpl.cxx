#include "server/ChessServiceImpl.hxx"
#include "utils/Types.hxx"
#include "utils/P2C_Converter.hxx"
#include "utils/C2P_Converter.hxx"

#include <iostream>

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
        response->add_names(room.first);
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
    room.spectatorsCount = 0;
    room.ownerPlayer.username = request->username();
    room.password = request->room().password();
    room.ownerPlayer.isReady = false;
    room.guestPlayer.isReady = false;
    room.isLastMoveRead = false;
    room.isSpectatorLastMoveRead = false;
    initMutexAndConditionVar(room.waitMutex, room.waitConditionVar);
    initMutexAndConditionVar(room.moveMutex, room.moveConditionVar);
    initMutexAndConditionVar(room.spectatorMutex, room.spectatorConditionVar);
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
    if (request->username() == room.ownerPlayer.username)
    {
        m_mapRooms.erase(request->room().name());
    }
    else if (request->username() == room.guestPlayer.username)
    {
        room.guestPlayer.username = "";
    }
    else
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, "Incorrect username");
    }
    std::cout << context->peer() << " has leaved " << request->room().name()
        << " room" << std::endl;
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
    room.spectatorsCount += 1;
    for (const auto& move : room.vecMovesHistory)
    {
        C2P_Converter::ConvertLastMoveInfo(move, lastMove);
        writer->Write(lastMove);
    }
    while (room.exists)
    {
        room.isSpectatorLastMoveRead = false;
        boost::mutex::scoped_lock lock(*(room.spectatorMutex));
        while (!room.isSpectatorLastMoveRead)
        {
            room.spectatorConditionVar->wait(lock);
        }
        C2P_Converter::ConvertLastMoveInfo(room.spectatorLastMove, lastMove);
        room.spectatorLastMove.Clean();
        writer->Write(lastMove);
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
    int viewers = room.spectatorsCount;
    response->set_value(viewers);
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
    room.lastMove.isKingHittable = false;
    room.isLastMoveRead = true;
    room.isSpectatorLastMoveRead = true;
    room.moveConditionVar->notify_one();
    room.spectatorConditionVar->notify_one();
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

grpc::Status Remote::ChessServiceImpl::SetKingHittable(
        grpc::ServerContext* context,
        const Proto::RoomWithIsKingHittable* request,
        Proto::Empty* response)
{
    std::string errMsg = "";
    if (!doCheckRoomSettings(request->room(), errMsg))
    {
        return grpc::Status(grpc::StatusCode::CANCELLED, errMsg);
    }
    Remote::ServerRoom& room = m_mapRooms[request->room().name()];
    room.lastMove.isKingHittable = request->iskinghittable().status();
    room.lastMove.hittableKingColor = (Pieces::PieceColor)request->iskinghittable().color();
    return grpc::Status::OK;
}
