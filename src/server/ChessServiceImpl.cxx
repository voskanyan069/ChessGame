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
    m_mapRooms[name].password = pass;
    m_mapRooms[name].isLastMoveRead = false;
    m_mapRooms[name].moveMutex.reset(new boost::mutex());
    m_mapRooms[name].moveConditionVar.reset(new boost::condition_variable());
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
    if (it->second.password != pass)
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
    m_mapRooms[room].lastMove = lm;
    boost::mutex::scoped_lock lock(*(m_mapRooms[room].moveMutex));
    m_mapRooms[room].isLastMoveRead = true;
    m_mapRooms[room].moveConditionVar->notify_one();
    return grpc::Status::OK;
}

grpc::Status Remote::ChessServiceImpl::ReadPieceMove(
        grpc::ServerContext* context,
        const Proto::RoomSettings* request,
        Proto::LastMoveInfo* response)
{
    std::string room = request->name();
    m_mapRooms[room].isLastMoveRead = false;
    boost::mutex::scoped_lock lock(*(m_mapRooms[room].moveMutex));
    while (!m_mapRooms[room].isLastMoveRead)
    {
        m_mapRooms[room].moveConditionVar->wait(lock);
    }
    if (m_mapRooms[room].lastMove.IsNull())
    {
        return grpc::Status::OK;
    }
    C2P_Converter::ConvertLastMoveInfo(m_mapRooms[room].lastMove, *response);
    m_mapRooms[room].lastMove.Clean();
    return grpc::Status::OK;
}
