// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ChessServer.proto

#include "ChessServer.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace Proto {
}  // namespace Proto
namespace protobuf_ChessServer_2eproto {
void InitDefaults() {
}

const ::google::protobuf::uint32 TableStruct::offsets[1] = {};
static const ::google::protobuf::internal::MigrationSchema* schemas = NULL;
static const ::google::protobuf::Message* const* file_default_instances = NULL;

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "ChessServer.proto", schemas, file_default_instances, TableStruct::offsets,
      NULL, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\021ChessServer.proto\022\005Proto\032\026ChessServerT"
      "ypes.proto2\277\003\n\013ChessServer\022,\n\014IsRoomExis"
      "ts\022\r.Proto.String\032\013.Proto.Bool\"\000\022<\n\nCrea"
      "teRoom\022\027.Proto.RoomWithUsername\032\023.Proto."
      "ActionResult\"\000\022:\n\010JoinRoom\022\027.Proto.RoomW"
      "ithUsername\032\023.Proto.ActionResult\"\000\0227\n\013Ge"
      "tUsername\022\027.Proto.RoomWithUsername\032\r.Pro"
      "to.String\"\000\0223\n\014WaitForReady\022\023.Proto.Room"
      "Settings\032\014.Proto.Empty\"\000\022,\n\005Ready\022\023.Prot"
      "o.ReadyRequest\032\014.Proto.Empty\"\000\022/\n\tMovePi"
      "ece\022\022.Proto.MoveRequest\032\014.Proto.Empty\"\000\022"
      ";\n\rReadPieceMove\022\023.Proto.RoomSettings\032\023."
      "Proto.LastMoveInfo\"\000b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 508);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ChessServer.proto", &protobuf_RegisterTypes);
  ::protobuf_ChessServerTypes_2eproto::AddDescriptors();
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_ChessServer_2eproto
namespace Proto {

// @@protoc_insertion_point(namespace_scope)
}  // namespace Proto
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
