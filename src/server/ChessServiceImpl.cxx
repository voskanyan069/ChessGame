#include "server/ChessServiceImpl.hxx"
#include "utils/Types.hxx"
#include "utils/P2C_Converter.hxx"
#include "utils/C2P_Converter.hxx"

#include <iostream>

#include <grpcpp/grpcpp.h>

Remote::ChessServiceImpl::ChessServiceImpl()
    : m_isLastMoveRead(false)
{
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

grpc::Status Remote::ChessServiceImpl::CreateRoom(
        grpc::ServerContext* context,
        const Proto::RoomSettings* request,
        Proto::ActionResult* response)
{
    std::string name = request->name();
    std::string pass = request->password();
    const auto& it = m_mapRooms.find(name);
    if (m_mapRooms.end() != it)
    {
        response->set_ok(false);
        response->set_msg("Room with this name already exists");
        return grpc::Status::OK;
    }
    m_mapRooms[name] = pass;
    response->set_ok(true);
    std::cout << context->peer() << " has created " << name
        << " room" << std::endl;
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::JoinRoom(
        grpc::ServerContext* context,
        const Proto::RoomSettings* request,
        Proto::ActionResult* response)
{
    std::string name = request->name();
    std::string pass = request->password();
    const auto& it = m_mapRooms.find(name);
    if (m_mapRooms.end() == it)
    {
        response->set_ok(false);
        response->set_msg("Room with this name does not exists");
        return grpc::Status::OK;
    }
    if (it->second != pass)
    {
        response->set_ok(false);
        response->set_msg("Incorrect passsword of the room");
        return grpc::Status::OK;
    }
    response->set_ok(true);
    std::cout << context->peer() << " has joined to " << name
        << " room" << std::endl;
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::MovePiece(
        grpc::ServerContext* context,
        const Proto::MoveRequest* request,
        Proto::Empty* response)
{
    std::string room = request->room().name();
    Pieces::Position oldPos;
    Pieces::Position newPos;
    P2C_Converter::ConvertPosition(request->oldposition(), oldPos);
    P2C_Converter::ConvertPosition(request->newposition(), newPos);
    Remote::LastMove lm(oldPos, newPos);
    std::pair<std::string, Remote::LastMove> pair = std::make_pair(room, lm);
    m_mapLastMove.insert(pair);
    boost::mutex::scoped_lock lock(m_mutex);
    m_isLastMoveRead = true;
    m_condition.notify_one();
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::ReadPieceMove(
        grpc::ServerContext* context,
        const Proto::RoomSettings* request,
        Proto::LastMoveInfo* response)
{
    m_isLastMoveRead = false;
    boost::mutex::scoped_lock lock(m_mutex);
    while (!m_isLastMoveRead)
    {
        m_condition.wait(lock);
    }
    std::string room = request->name();
    const auto& it = m_mapLastMove.find(room);
    if (m_mapLastMove.end() == it)
    {
        return grpc::Status::OK;
    }
    C2P_Converter::ConvertLastMoveInfo(it->second, *response);
    m_mapLastMove.erase(room);
    return grpc::Status::OK;
}
