// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: ChessServer.proto
#ifndef GRPC_ChessServer_2eproto__INCLUDED
#define GRPC_ChessServer_2eproto__INCLUDED

#include "ChessServer.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace Proto {

class ChessServer final {
 public:
  static constexpr char const* service_full_name() {
    return "Proto.ChessServer";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status IsRoomExists(::grpc::ClientContext* context, const ::Proto::String& request, ::Proto::Bool* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Bool>> AsyncIsRoomExists(::grpc::ClientContext* context, const ::Proto::String& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Bool>>(AsyncIsRoomExistsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Bool>> PrepareAsyncIsRoomExists(::grpc::ClientContext* context, const ::Proto::String& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Bool>>(PrepareAsyncIsRoomExistsRaw(context, request, cq));
    }
    virtual ::grpc::Status CreateRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::Proto::ActionResult* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>> AsyncCreateRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>>(AsyncCreateRoomRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>> PrepareAsyncCreateRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>>(PrepareAsyncCreateRoomRaw(context, request, cq));
    }
    virtual ::grpc::Status JoinRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::Proto::ActionResult* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>> AsyncJoinRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>>(AsyncJoinRoomRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>> PrepareAsyncJoinRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>>(PrepareAsyncJoinRoomRaw(context, request, cq));
    }
    virtual ::grpc::Status MovePiece(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::Proto::Empty* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Empty>> AsyncMovePiece(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Empty>>(AsyncMovePieceRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Empty>> PrepareAsyncMovePiece(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Empty>>(PrepareAsyncMovePieceRaw(context, request, cq));
    }
    virtual ::grpc::Status ReadPieceMove(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::Proto::LastMoveInfo* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::LastMoveInfo>> AsyncReadPieceMove(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::LastMoveInfo>>(AsyncReadPieceMoveRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::LastMoveInfo>> PrepareAsyncReadPieceMove(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Proto::LastMoveInfo>>(PrepareAsyncReadPieceMoveRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void IsRoomExists(::grpc::ClientContext* context, const ::Proto::String* request, ::Proto::Bool* response, std::function<void(::grpc::Status)>) = 0;
      virtual void CreateRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response, std::function<void(::grpc::Status)>) = 0;
      virtual void JoinRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response, std::function<void(::grpc::Status)>) = 0;
      virtual void MovePiece(::grpc::ClientContext* context, const ::Proto::MoveRequest* request, ::Proto::Empty* response, std::function<void(::grpc::Status)>) = 0;
      virtual void ReadPieceMove(::grpc::ClientContext* context, const ::Proto::RoomSettings* request, ::Proto::LastMoveInfo* response, std::function<void(::grpc::Status)>) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Bool>* AsyncIsRoomExistsRaw(::grpc::ClientContext* context, const ::Proto::String& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Bool>* PrepareAsyncIsRoomExistsRaw(::grpc::ClientContext* context, const ::Proto::String& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>* AsyncCreateRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>* PrepareAsyncCreateRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>* AsyncJoinRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Proto::ActionResult>* PrepareAsyncJoinRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Empty>* AsyncMovePieceRaw(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Proto::Empty>* PrepareAsyncMovePieceRaw(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Proto::LastMoveInfo>* AsyncReadPieceMoveRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Proto::LastMoveInfo>* PrepareAsyncReadPieceMoveRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status IsRoomExists(::grpc::ClientContext* context, const ::Proto::String& request, ::Proto::Bool* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::Bool>> AsyncIsRoomExists(::grpc::ClientContext* context, const ::Proto::String& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::Bool>>(AsyncIsRoomExistsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::Bool>> PrepareAsyncIsRoomExists(::grpc::ClientContext* context, const ::Proto::String& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::Bool>>(PrepareAsyncIsRoomExistsRaw(context, request, cq));
    }
    ::grpc::Status CreateRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::Proto::ActionResult* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>> AsyncCreateRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>>(AsyncCreateRoomRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>> PrepareAsyncCreateRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>>(PrepareAsyncCreateRoomRaw(context, request, cq));
    }
    ::grpc::Status JoinRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::Proto::ActionResult* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>> AsyncJoinRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>>(AsyncJoinRoomRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>> PrepareAsyncJoinRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>>(PrepareAsyncJoinRoomRaw(context, request, cq));
    }
    ::grpc::Status MovePiece(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::Proto::Empty* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::Empty>> AsyncMovePiece(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::Empty>>(AsyncMovePieceRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::Empty>> PrepareAsyncMovePiece(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::Empty>>(PrepareAsyncMovePieceRaw(context, request, cq));
    }
    ::grpc::Status ReadPieceMove(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::Proto::LastMoveInfo* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::LastMoveInfo>> AsyncReadPieceMove(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::LastMoveInfo>>(AsyncReadPieceMoveRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::LastMoveInfo>> PrepareAsyncReadPieceMove(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Proto::LastMoveInfo>>(PrepareAsyncReadPieceMoveRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void IsRoomExists(::grpc::ClientContext* context, const ::Proto::String* request, ::Proto::Bool* response, std::function<void(::grpc::Status)>) override;
      void CreateRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response, std::function<void(::grpc::Status)>) override;
      void JoinRoom(::grpc::ClientContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response, std::function<void(::grpc::Status)>) override;
      void MovePiece(::grpc::ClientContext* context, const ::Proto::MoveRequest* request, ::Proto::Empty* response, std::function<void(::grpc::Status)>) override;
      void ReadPieceMove(::grpc::ClientContext* context, const ::Proto::RoomSettings* request, ::Proto::LastMoveInfo* response, std::function<void(::grpc::Status)>) override;
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::Proto::Bool>* AsyncIsRoomExistsRaw(::grpc::ClientContext* context, const ::Proto::String& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Proto::Bool>* PrepareAsyncIsRoomExistsRaw(::grpc::ClientContext* context, const ::Proto::String& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>* AsyncCreateRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>* PrepareAsyncCreateRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>* AsyncJoinRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Proto::ActionResult>* PrepareAsyncJoinRoomRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Proto::Empty>* AsyncMovePieceRaw(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Proto::Empty>* PrepareAsyncMovePieceRaw(::grpc::ClientContext* context, const ::Proto::MoveRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Proto::LastMoveInfo>* AsyncReadPieceMoveRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Proto::LastMoveInfo>* PrepareAsyncReadPieceMoveRaw(::grpc::ClientContext* context, const ::Proto::RoomSettings& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_IsRoomExists_;
    const ::grpc::internal::RpcMethod rpcmethod_CreateRoom_;
    const ::grpc::internal::RpcMethod rpcmethod_JoinRoom_;
    const ::grpc::internal::RpcMethod rpcmethod_MovePiece_;
    const ::grpc::internal::RpcMethod rpcmethod_ReadPieceMove_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status IsRoomExists(::grpc::ServerContext* context, const ::Proto::String* request, ::Proto::Bool* response);
    virtual ::grpc::Status CreateRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response);
    virtual ::grpc::Status JoinRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response);
    virtual ::grpc::Status MovePiece(::grpc::ServerContext* context, const ::Proto::MoveRequest* request, ::Proto::Empty* response);
    virtual ::grpc::Status ReadPieceMove(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::LastMoveInfo* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_IsRoomExists : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_IsRoomExists() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_IsRoomExists() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status IsRoomExists(::grpc::ServerContext* context, const ::Proto::String* request, ::Proto::Bool* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestIsRoomExists(::grpc::ServerContext* context, ::Proto::String* request, ::grpc::ServerAsyncResponseWriter< ::Proto::Bool>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_CreateRoom : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_CreateRoom() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_CreateRoom() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestCreateRoom(::grpc::ServerContext* context, ::Proto::RoomSettings* request, ::grpc::ServerAsyncResponseWriter< ::Proto::ActionResult>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_JoinRoom : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_JoinRoom() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_JoinRoom() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status JoinRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestJoinRoom(::grpc::ServerContext* context, ::Proto::RoomSettings* request, ::grpc::ServerAsyncResponseWriter< ::Proto::ActionResult>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_MovePiece : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_MovePiece() {
      ::grpc::Service::MarkMethodAsync(3);
    }
    ~WithAsyncMethod_MovePiece() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status MovePiece(::grpc::ServerContext* context, const ::Proto::MoveRequest* request, ::Proto::Empty* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestMovePiece(::grpc::ServerContext* context, ::Proto::MoveRequest* request, ::grpc::ServerAsyncResponseWriter< ::Proto::Empty>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(3, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_ReadPieceMove : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_ReadPieceMove() {
      ::grpc::Service::MarkMethodAsync(4);
    }
    ~WithAsyncMethod_ReadPieceMove() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ReadPieceMove(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::LastMoveInfo* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestReadPieceMove(::grpc::ServerContext* context, ::Proto::RoomSettings* request, ::grpc::ServerAsyncResponseWriter< ::Proto::LastMoveInfo>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(4, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_IsRoomExists<WithAsyncMethod_CreateRoom<WithAsyncMethod_JoinRoom<WithAsyncMethod_MovePiece<WithAsyncMethod_ReadPieceMove<Service > > > > > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_IsRoomExists : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_IsRoomExists() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_IsRoomExists() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status IsRoomExists(::grpc::ServerContext* context, const ::Proto::String* request, ::Proto::Bool* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_CreateRoom : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_CreateRoom() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_CreateRoom() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_JoinRoom : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_JoinRoom() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_JoinRoom() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status JoinRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_MovePiece : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_MovePiece() {
      ::grpc::Service::MarkMethodGeneric(3);
    }
    ~WithGenericMethod_MovePiece() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status MovePiece(::grpc::ServerContext* context, const ::Proto::MoveRequest* request, ::Proto::Empty* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_ReadPieceMove : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_ReadPieceMove() {
      ::grpc::Service::MarkMethodGeneric(4);
    }
    ~WithGenericMethod_ReadPieceMove() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ReadPieceMove(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::LastMoveInfo* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_IsRoomExists : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_IsRoomExists() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_IsRoomExists() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status IsRoomExists(::grpc::ServerContext* context, const ::Proto::String* request, ::Proto::Bool* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestIsRoomExists(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_CreateRoom : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_CreateRoom() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_CreateRoom() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestCreateRoom(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_JoinRoom : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_JoinRoom() {
      ::grpc::Service::MarkMethodRaw(2);
    }
    ~WithRawMethod_JoinRoom() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status JoinRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestJoinRoom(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_MovePiece : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_MovePiece() {
      ::grpc::Service::MarkMethodRaw(3);
    }
    ~WithRawMethod_MovePiece() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status MovePiece(::grpc::ServerContext* context, const ::Proto::MoveRequest* request, ::Proto::Empty* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestMovePiece(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(3, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_ReadPieceMove : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_ReadPieceMove() {
      ::grpc::Service::MarkMethodRaw(4);
    }
    ~WithRawMethod_ReadPieceMove() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ReadPieceMove(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::LastMoveInfo* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestReadPieceMove(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(4, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_IsRoomExists : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_IsRoomExists() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::Proto::String, ::Proto::Bool>(std::bind(&WithStreamedUnaryMethod_IsRoomExists<BaseClass>::StreamedIsRoomExists, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_IsRoomExists() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status IsRoomExists(::grpc::ServerContext* context, const ::Proto::String* request, ::Proto::Bool* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedIsRoomExists(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::Proto::String,::Proto::Bool>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_CreateRoom : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_CreateRoom() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler< ::Proto::RoomSettings, ::Proto::ActionResult>(std::bind(&WithStreamedUnaryMethod_CreateRoom<BaseClass>::StreamedCreateRoom, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_CreateRoom() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status CreateRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedCreateRoom(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::Proto::RoomSettings,::Proto::ActionResult>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_JoinRoom : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_JoinRoom() {
      ::grpc::Service::MarkMethodStreamed(2,
        new ::grpc::internal::StreamedUnaryHandler< ::Proto::RoomSettings, ::Proto::ActionResult>(std::bind(&WithStreamedUnaryMethod_JoinRoom<BaseClass>::StreamedJoinRoom, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_JoinRoom() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status JoinRoom(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::ActionResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedJoinRoom(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::Proto::RoomSettings,::Proto::ActionResult>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_MovePiece : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_MovePiece() {
      ::grpc::Service::MarkMethodStreamed(3,
        new ::grpc::internal::StreamedUnaryHandler< ::Proto::MoveRequest, ::Proto::Empty>(std::bind(&WithStreamedUnaryMethod_MovePiece<BaseClass>::StreamedMovePiece, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_MovePiece() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status MovePiece(::grpc::ServerContext* context, const ::Proto::MoveRequest* request, ::Proto::Empty* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedMovePiece(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::Proto::MoveRequest,::Proto::Empty>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_ReadPieceMove : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_ReadPieceMove() {
      ::grpc::Service::MarkMethodStreamed(4,
        new ::grpc::internal::StreamedUnaryHandler< ::Proto::RoomSettings, ::Proto::LastMoveInfo>(std::bind(&WithStreamedUnaryMethod_ReadPieceMove<BaseClass>::StreamedReadPieceMove, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_ReadPieceMove() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status ReadPieceMove(::grpc::ServerContext* context, const ::Proto::RoomSettings* request, ::Proto::LastMoveInfo* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedReadPieceMove(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::Proto::RoomSettings,::Proto::LastMoveInfo>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_IsRoomExists<WithStreamedUnaryMethod_CreateRoom<WithStreamedUnaryMethod_JoinRoom<WithStreamedUnaryMethod_MovePiece<WithStreamedUnaryMethod_ReadPieceMove<Service > > > > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_IsRoomExists<WithStreamedUnaryMethod_CreateRoom<WithStreamedUnaryMethod_JoinRoom<WithStreamedUnaryMethod_MovePiece<WithStreamedUnaryMethod_ReadPieceMove<Service > > > > > StreamedService;
};

}  // namespace Proto


#endif  // GRPC_ChessServer_2eproto__INCLUDED