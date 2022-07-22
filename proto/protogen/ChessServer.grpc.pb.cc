// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: ChessServer.proto

#include "ChessServer.pb.h"
#include "ChessServer.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace Proto {

static const char* ChessServer_method_names[] = {
  "/Proto.ChessServer/IsRoomExists",
  "/Proto.ChessServer/CreateRoom",
  "/Proto.ChessServer/JoinRoom",
  "/Proto.ChessServer/MovePiece",
  "/Proto.ChessServer/ReadPieceMove",
};

std::unique_ptr< ChessServer::Stub> ChessServer::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ChessServer::Stub> stub(new ChessServer::Stub(channel));
  return stub;
}

ChessServer::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_IsRoomExists_(ChessServer_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CreateRoom_(ChessServer_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_JoinRoom_(ChessServer_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_MovePiece_(ChessServer_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ReadPieceMove_(ChessServer_method_names[4], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ChessServer::Stub::IsRoomExists(::grpc::ClientContext* context, const ::Proto::String& request, ::Proto::Bool* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_IsRoomExists_, context, request, response);
}

void ChessServer::Stub::experimental_async::IsRoomExists(::grpc::ClientContext* context, const ::Proto::String* request, ::Proto::Bool* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_IsRoomExists_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::Proto::Bool>* ChessServer::Stub::AsyncIsRoomExistsRaw(::grpc::ClientContext* context, const ::Proto::String& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Proto::Bool>::Create(channel_.get(), cq, rpcmethod_IsRoomExists_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::Proto::Bool>* ChessServer::Stub::PrepareAsyncIsRoomExistsRaw(::grpc::ClientContext* context, const ::Proto::String& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Proto::Bool>::Create(channel_.get(), cq, rpcmethod_IsRoomExists_, context, request, false);
}

::grpc::Status ChessServer::Stub::CreateRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::Proto::ActionResult* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_CreateRoom_, context, request, response);
}

void ChessServer::Stub::experimental_async::CreateRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_CreateRoom_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>* ChessServer::Stub::AsyncCreateRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Proto::ActionResult>::Create(channel_.get(), cq, rpcmethod_CreateRoom_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>* ChessServer::Stub::PrepareAsyncCreateRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Proto::ActionResult>::Create(channel_.get(), cq, rpcmethod_CreateRoom_, context, request, false);
}

::grpc::Status ChessServer::Stub::JoinRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::Proto::ActionResult* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_JoinRoom_, context, request, response);
}

void ChessServer::Stub::experimental_async::JoinRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_JoinRoom_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>* ChessServer::Stub::AsyncJoinRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Proto::ActionResult>::Create(channel_.get(), cq, rpcmethod_JoinRoom_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>* ChessServer::Stub::PrepareAsyncJoinRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Proto::ActionResult>::Create(channel_.get(), cq, rpcmethod_JoinRoom_, context, request, false);
}

::grpc::Status ChessServer::Stub::MovePiece(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::Proto::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_MovePiece_, context, request, response);
}

void ChessServer::Stub::experimental_async::MovePiece(::grpc::ClientContext* context, const ::Proto::MoveRequest* request, ::Proto::Empty* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_MovePiece_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::Proto::Empty>* ChessServer::Stub::AsyncMovePieceRaw(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Proto::Empty>::Create(channel_.get(), cq, rpcmethod_MovePiece_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::Proto::Empty>* ChessServer::Stub::PrepareAsyncMovePieceRaw(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Proto::Empty>::Create(channel_.get(), cq, rpcmethod_MovePiece_, context, request, false);
}

::grpc::Status ChessServer::Stub::ReadPieceMove(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::Proto::LastMoveInfo* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_ReadPieceMove_, context, request, response);
}

void ChessServer::Stub::experimental_async::ReadPieceMove(::grpc::ClientContext* context, const ::Proto::RoomSettings* request, ::Proto::LastMoveInfo* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ReadPieceMove_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::Proto::LastMoveInfo>* ChessServer::Stub::AsyncReadPieceMoveRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Proto::LastMoveInfo>::Create(channel_.get(), cq, rpcmethod_ReadPieceMove_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::Proto::LastMoveInfo>* ChessServer::Stub::PrepareAsyncReadPieceMoveRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Proto::LastMoveInfo>::Create(channel_.get(), cq, rpcmethod_ReadPieceMove_, context, request, false);
}

ChessServer::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChessServer_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChessServer::Service, ::Proto::String, ::Proto::Bool>(
          std::mem_fn(&ChessServer::Service::IsRoomExists), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChessServer_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChessServer::Service, ::Proto::RoomSettings, ::Proto::ActionResult>(
          std::mem_fn(&ChessServer::Service::CreateRoom), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChessServer_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChessServer::Service, ::Proto::RoomSettings, ::Proto::ActionResult>(
          std::mem_fn(&ChessServer::Service::JoinRoom), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChessServer_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChessServer::Service, ::Proto::MoveRequest, ::Proto::Empty>(
          std::mem_fn(&ChessServer::Service::MovePiece), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChessServer_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChessServer::Service, ::Proto::RoomSettings, ::Proto::LastMoveInfo>(
          std::mem_fn(&ChessServer::Service::ReadPieceMove), this)));
}

ChessServer::Service::~Service() {
}

::grpc::Status ChessServer::Service::IsRoomExists(::grpc::ServerContext* context, const ::Proto::String* request, ::Proto::Bool* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChessServer::Service::CreateRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChessServer::Service::JoinRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChessServer::Service::MovePiece(::grpc::ServerContext* context, const ::Proto::MoveRequest* request, ::Proto::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChessServer::Service::ReadPieceMove(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::LastMoveInfo* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace Proto
