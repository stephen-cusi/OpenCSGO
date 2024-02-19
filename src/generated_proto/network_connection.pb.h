// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: network_connection.proto

#ifndef PROTOBUF_network_5fconnection_2eproto__INCLUDED
#define PROTOBUF_network_5fconnection_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include "google/protobuf/descriptor.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_network_5fconnection_2eproto();
void protobuf_AssignDesc_network_5fconnection_2eproto();
void protobuf_ShutdownFile_network_5fconnection_2eproto();


enum ENetworkDisconnectionReason {
  NETWORK_DISCONNECT_INVALID = 0,
  NETWORK_DISCONNECT_SHUTDOWN = 1,
  NETWORK_DISCONNECT_DISCONNECT_BY_USER = 2,
  NETWORK_DISCONNECT_DISCONNECT_BY_SERVER = 3,
  NETWORK_DISCONNECT_LOST = 4,
  NETWORK_DISCONNECT_OVERFLOW = 5,
  NETWORK_DISCONNECT_STEAM_BANNED = 6,
  NETWORK_DISCONNECT_STEAM_INUSE = 7,
  NETWORK_DISCONNECT_STEAM_TICKET = 8,
  NETWORK_DISCONNECT_STEAM_LOGON = 9,
  NETWORK_DISCONNECT_STEAM_AUTHCANCELLED = 10,
  NETWORK_DISCONNECT_STEAM_AUTHALREADYUSED = 11,
  NETWORK_DISCONNECT_STEAM_AUTHINVALID = 12,
  NETWORK_DISCONNECT_STEAM_VACBANSTATE = 13,
  NETWORK_DISCONNECT_STEAM_LOGGED_IN_ELSEWHERE = 14,
  NETWORK_DISCONNECT_STEAM_VAC_CHECK_TIMEDOUT = 15,
  NETWORK_DISCONNECT_STEAM_DROPPED = 16,
  NETWORK_DISCONNECT_STEAM_OWNERSHIP = 17,
  NETWORK_DISCONNECT_SERVERINFO_OVERFLOW = 18,
  NETWORK_DISCONNECT_TICKMSG_OVERFLOW = 19,
  NETWORK_DISCONNECT_STRINGTABLEMSG_OVERFLOW = 20,
  NETWORK_DISCONNECT_DELTAENTMSG_OVERFLOW = 21,
  NETWORK_DISCONNECT_TEMPENTMSG_OVERFLOW = 22,
  NETWORK_DISCONNECT_SOUNDSMSG_OVERFLOW = 23,
  NETWORK_DISCONNECT_SNAPSHOTOVERFLOW = 24,
  NETWORK_DISCONNECT_SNAPSHOTERROR = 25,
  NETWORK_DISCONNECT_RELIABLEOVERFLOW = 26,
  NETWORK_DISCONNECT_BADDELTATICK = 27,
  NETWORK_DISCONNECT_NOMORESPLITS = 28,
  NETWORK_DISCONNECT_TIMEDOUT = 29,
  NETWORK_DISCONNECT_DISCONNECTED = 30,
  NETWORK_DISCONNECT_LEAVINGSPLIT = 31,
  NETWORK_DISCONNECT_DIFFERENTCLASSTABLES = 32,
  NETWORK_DISCONNECT_BADRELAYPASSWORD = 33,
  NETWORK_DISCONNECT_BADSPECTATORPASSWORD = 34,
  NETWORK_DISCONNECT_HLTVRESTRICTED = 35,
  NETWORK_DISCONNECT_NOSPECTATORS = 36,
  NETWORK_DISCONNECT_HLTVUNAVAILABLE = 37,
  NETWORK_DISCONNECT_HLTVSTOP = 38,
  NETWORK_DISCONNECT_KICKED = 39,
  NETWORK_DISCONNECT_BANADDED = 40,
  NETWORK_DISCONNECT_KICKBANADDED = 41,
  NETWORK_DISCONNECT_HLTVDIRECT = 42,
  NETWORK_DISCONNECT_PURESERVER_CLIENTEXTRA = 43,
  NETWORK_DISCONNECT_PURESERVER_MISMATCH = 44,
  NETWORK_DISCONNECT_USERCMD = 45,
  NETWORK_DISCONNECT_REJECTED_BY_GAME = 46,
  NETWORK_DISCONNECT_MESSAGE_PARSE_ERROR = 47,
  NETWORK_DISCONNECT_INVALID_MESSAGE_ERROR = 48,
  NETWORK_DISCONNECT_BAD_SERVER_PASSWORD = 49,
  NETWORK_DISCONNECT_DIRECT_CONNECT_RESERVATION = 50,
  NETWORK_DISCONNECT_CONNECTION_FAILURE = 51,
  NETWORK_DISCONNECT_NO_PEER_GROUP_HANDLERS = 52,
  NETWORK_DISCONNECT_RECONNECTION = 53,
  NETWORK_DISCONNECT_CONNECTION_CLOSING = 54,
  NETWORK_DISCONNECT_NO_GOTV_RELAYS_AVAILABLE = 55,
  NETWORK_DISCONNECT_SESSION_MIGRATED = 56,
  NETWORK_DISCONNECT_VERYLARGETRANSFEROVERFLOW = 57,
  NETWORK_DISCONNECT_SENDNETOVERFLOW = 58,
  NETWORK_DISCONNECT_PLAYER_REMOVED_FROM_HOST_SESSION = 59,
  NETWORK_DISCONNECT_SERVER_DOS = 61
};
bool ENetworkDisconnectionReason_IsValid(int value);
const ENetworkDisconnectionReason ENetworkDisconnectionReason_MIN = NETWORK_DISCONNECT_INVALID;
const ENetworkDisconnectionReason ENetworkDisconnectionReason_MAX = NETWORK_DISCONNECT_SERVER_DOS;
const int ENetworkDisconnectionReason_ARRAYSIZE = ENetworkDisconnectionReason_MAX + 1;

const ::google::protobuf::EnumDescriptor* ENetworkDisconnectionReason_descriptor();
inline const ::std::string& ENetworkDisconnectionReason_Name(ENetworkDisconnectionReason value) {
  return ::google::protobuf::internal::NameOfEnum(
    ENetworkDisconnectionReason_descriptor(), value);
}
inline bool ENetworkDisconnectionReason_Parse(
    const ::std::string& name, ENetworkDisconnectionReason* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ENetworkDisconnectionReason>(
    ENetworkDisconnectionReason_descriptor(), name, value);
}
// ===================================================================


// ===================================================================

static const int kNetworkConnectionTokenFieldNumber = 50500;
extern ::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::StringTypeTraits, 9, false >
  network_connection_token;

// ===================================================================


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::ENetworkDisconnectionReason> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ENetworkDisconnectionReason>() {
  return ::ENetworkDisconnectionReason_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_network_5fconnection_2eproto__INCLUDED
