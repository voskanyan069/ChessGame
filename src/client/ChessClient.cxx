#include "client/ChessClient.hxx"
#include "utils/Types.hxx"
#include "utils/P2C_Converter.hxx"
#include "utils/C2P_Converter.hxx"
#include "utils/Exception.hxx"
#include "protogen/ChessServer.pb.h"
#include "protogen/ChessServerTypes.pb.h"

#include <iostream>

#include <grpcpp/grpcpp.h>

Remote::ChessClient::ChessClient(const std::string& hostname)
    : m_stub(Proto::ChessServer::NewStub(grpc::CreateChannel(
                    hostname, grpc::InsecureChannelCredentials())))
{
}

void Remote::ChessClient::checkRequestStatus(const grpc::Status& status)
{
    if (!status.ok())
    {
        throw Utils::Exception(status.error_message(), "Request failed");
    }
}

bool Remote::ChessClient::IsRoomExists(const std::string& name)
{
    grpc::ClientContext context;
    Proto::String request;
    Proto::Bool response;
    request.set_value(name);
    grpc::Status status = m_stub->IsRoomExists(&context, request, &response);
    checkRequestStatus(status);
    return response.value();
}

void Remote::ChessClient::CreateRoom(const Remote::Room& room)
{
    grpc::ClientContext context;
    Proto::RoomSettings request;
    Proto::ActionResult response;
    request.set_name(room.name);
    request.set_password(room.password);
    grpc::Status status = m_stub->CreateRoom(&context, request, &response);
    checkRequestStatus(status);
    if (!response.ok())
    {
        throw Utils::Exception(response.msg(), "Server error");
    }
}

void Remote::ChessClient::JoinRoom(const Remote::Room& room)
{
    grpc::ClientContext context;
    Proto::RoomSettings request;
    Proto::ActionResult response;
    request.set_name(room.name);
    request.set_password(room.password);
    grpc::Status status = m_stub->JoinRoom(&context, request, &response);
    checkRequestStatus(status);
    if (!response.ok())
    {
        throw Utils::Exception(response.msg(), "Server error");
    }
}

void Remote::ChessClient::MovePiece(const Remote::Room& room,
        const Pieces::Position& oldPos, const Pieces::Position& newPos)
{
    grpc::ClientContext context;
    Proto::MoveRequest request;
    Proto::Empty response;
    Proto::RoomSettings* reqRoom = request.mutable_room();
    C2P_Converter::ConvertPosition(oldPos, *(request.mutable_oldposition()));
    C2P_Converter::ConvertPosition(newPos, *(request.mutable_newposition()));
    reqRoom->set_name(room.name);
    reqRoom->set_password(room.password);
    grpc::Status status = m_stub->MovePiece(&context, request, &response);
    checkRequestStatus(status);
}

void Remote::ChessClient::ReadLastMove(const Remote::Room& room,
        Remote::LastMove& lastMove)
{
    grpc::ClientContext context;
    Proto::RoomSettings request;
    Proto::LastMoveInfo response;
    request.set_name(room.name);
    request.set_password(room.password);
    grpc::Status status = m_stub->ReadPieceMove(&context, request, &response);
    checkRequestStatus(status);
    P2C_Converter::ConvertLastMoveInfo(response, lastMove);
}
