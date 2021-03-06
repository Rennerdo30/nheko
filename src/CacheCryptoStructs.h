#pragma once

#include <map>
#include <mutex>

//#include <nlohmann/json.hpp>

#include <mtx/responses.hpp>
#include <mtxclient/crypto/client.hpp>

// Extra information associated with an outbound megolm session.
struct OutboundGroupSessionData
{
        std::string session_id;
        std::string session_key;
        uint64_t message_index = 0;
};

void
to_json(nlohmann::json &obj, const OutboundGroupSessionData &msg);
void
from_json(const nlohmann::json &obj, OutboundGroupSessionData &msg);

struct OutboundGroupSessionDataRef
{
        OlmOutboundGroupSession *session;
        OutboundGroupSessionData data;
};

struct DevicePublicKeys
{
        std::string ed25519;
        std::string curve25519;
};

void
to_json(nlohmann::json &obj, const DevicePublicKeys &msg);
void
from_json(const nlohmann::json &obj, DevicePublicKeys &msg);

//! Represents a unique megolm session identifier.
struct MegolmSessionIndex
{
        //! The room in which this session exists.
        std::string room_id;
        //! The session_id of the megolm session.
        std::string session_id;
        //! The curve25519 public key of the sender.
        std::string sender_key;
};

void
to_json(nlohmann::json &obj, const MegolmSessionIndex &msg);
void
from_json(const nlohmann::json &obj, MegolmSessionIndex &msg);

struct OlmSessionStorage
{
        // Megolm sessions
        std::map<std::string, mtx::crypto::InboundGroupSessionPtr> group_inbound_sessions;
        std::map<std::string, mtx::crypto::OutboundGroupSessionPtr> group_outbound_sessions;
        std::map<std::string, OutboundGroupSessionData> group_outbound_session_data;

        // Guards for accessing megolm sessions.
        std::mutex group_outbound_mtx;
        std::mutex group_inbound_mtx;
};
