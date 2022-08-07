#include "client/ChessClient.hxx"
#include "io/Logger.hxx"
#include "utils/Types.hxx"
#include "utils/P2C_Converter.hxx"
#include "utils/C2P_Converter.hxx"
#include "utils/Exception.hxx"
#include "protogen/ChessServer.pb.h"
#include "protogen/ChessServerTypes.pb.h"

#include <iostream>

#include <grpcpp/grpcpp.h>

Remote::ChessClient::ChessClient(const std::string& hostname,
        const std::string& username)
    : m_username(username)
    , m_stub(Proto::ChessServer::NewStub(grpc::CreateChannel(
                      hostname, grpc::InsecureChannelCredentials())))
{
}

void Remote::ChessClient::checkRequestStatus(const grpc::Status& status,
        const std::string& errorType) const
{
    if (!status.ok())
    {
        std::string errorMsg = status.error_message();
        if (grpc::StatusCode::UNAVAILABLE == status.error_code())
        {
            Logger::GetInstance()->Print(ERROR, "Request failed: %s", errorMsg);
            std::exit(-1);
        }
        throw Utils::Exception(status.error_message(), errorType);
    }
}

bool Remote::ChessClient::IsRoomExists(const std::string& name) const
{
    grpc::ClientContext context;
    Proto::String request;
    Proto::Bool response;
    request.set_value(name);
    grpc::Status status = m_stub->IsRoomExists(&context, request, &response);
    checkRequestStatus(status);
    return response.value();
}

void Remote::ChessClient::CreateRoom(const Remote::Room& room) const
{
    grpc::ClientContext context;
    Proto::RoomWithUsername request;
    Proto::Empty response;
    request.set_username(m_username);
    request.mutable_room()->set_name(room.name);
    request.mutable_room()->set_password(room.password);
    grpc::Status status = m_stub->CreateRoom(&context, request, &response);
    checkRequestStatus(status);
}

void Remote::ChessClient::JoinRoom(const Remote::Room& room) const
{
    grpc::ClientContext context;
    Proto::RoomWithUsername request;
    Proto::Empty response;
    request.set_username(m_username);
    request.mutable_room()->set_name(room.name);
    request.mutable_room()->set_password(room.password);
    grpc::Status status = m_stub->JoinRoom(&context, request, &response);
    checkRequestStatus(status);
}

void Remote::ChessClient::WaitForReady(const Remote::Room& room) const
{
    grpc::ClientContext context;
    Proto::RoomSettings request;
    Proto::Empty response;
    request.set_name(room.name);
    request.set_password(room.password);
    grpc::Status status = m_stub->WaitForReady(&context, request, &response);
    checkRequestStatus(status);
}

void Remote::ChessClient::Ready(const Remote::Room& room,
        const Remote::Player& player) const
{
    grpc::ClientContext context;
    Proto::ReadyRequest request;
    Proto::Empty response;
    request.set_isready(player.isReady);
    request.set_playertype((player.playerType == Remote::PlayerType::OWNER) ?
            Proto::PlayerType::OWNER : Proto::PlayerType::GUEST);
    request.mutable_room()->set_name(room.name);
    request.mutable_room()->set_password(room.password);
    grpc::Status status = m_stub->Ready(&context, request, &response);
    checkRequestStatus(status);
}

void Remote::ChessClient::MovePiece(const Remote::Room& room,
        const Pieces::Position& oldPos, const Pieces::Position& newPos) const
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
        Remote::LastMove& lastMove) const
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

std::string Remote::ChessClient::GetOpponentUsername(
        const Remote::Room& room) const
{
    grpc::ClientContext context;
    Proto::RoomWithUsername request;
    Proto::String response;
    request.set_username(m_username);
    request.mutable_room()->set_name(room.name);
    request.mutable_room()->set_password(room.password);
    grpc::Status status = m_stub->GetUsername(&context, request, &response);
    checkRequestStatus(status);
    return response.value();
}
