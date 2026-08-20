#ifndef JARNAX_CYPHAL_NODE_HPP
#define JARNAX_CYPHAL_NODE_HPP

#include "core/Array.hpp"
#include "core/Status.hpp"
#include "core/units/MicroSeconds.hpp"

#include "jarnax/Loopable.hpp"
#include "jarnax/Timer.hpp"

#include "jarnax/cyphal/Interface.hpp"
#include "jarnax/cyphal/Types.hpp"

namespace jarnax {
namespace cyphal {

/// The server interface for handling incoming service requests and providing responses.
class Server {
public:
    /// Called when a new request has been received.
    virtual void OnRequest(ServiceId id, NodeId sender, SerializedMessage msg) = 0;
    /// Called each cycle after OnRequest until either the response is ready or an error occurs.
    virtual core::Status GetResponse(ServiceId id, SerializedMessage& msg) = 0;

protected:
    ~Server() = default;
};

/// The client interface for handling responses to service requests.
class Client {
public:
    /// Called when the response from the Request returns.
    virtual void OnResponse(ServiceId id, NodeId responder, SerializedMessage msg) = 0;

protected:
    ~Client() = default;
};

/// The publisher interface for providing messages to be published.
class Publisher {
public:
    /// Called to see if a message is ready in the case of no period.
    /// Called to obtain a message after the period expired in the case of a timed message.
    /// @param msg Set this to your storage of the output message.
    virtual core::Status OnPublish(SubjectId id, SerializedMessage& msg) = 0;

protected:
    ~Publisher() = default;
};

/// The subscriber interface for handling incoming messages.
class Subscriber {
public:
    /// Called when a message has been received.
    /// @param id The subject ID of the received message.
    /// @param msg The serialized message received.
    /// @note This function is called by the Node when a message matching the subscribed subject ID is received.
    virtual void OnBroadcast(SubjectId id, SerializedMessage msg) = 0;

protected:
    ~Subscriber() = default;
};

/// The interface an object implements to be callable by the Node when an unhandled command is received.
class Executor {
public:
    constexpr static size_t ParamterSize{ExecuteCommandRequestCommandStringSize};
    /// Called when an unhandled command is received.
    /// @param command The command ID.
    /// @param parameters The parameters associated with the command.
    /// @return True if the command was successfully handled, false otherwise.
    virtual ExecuteStatus OnCommand(uint16_t command, char const parameters[ParamterSize]) = 0;

    constexpr static size_t ResponseSize{ExecuteCommandResponseStringSize};
    /// Called to obtain the result of a previously handled command.
    /// @param command The command ID.
    /// @param response The response associated with the command.
    /// @param out_response_size The size of the response buffer.
    /// @return The result of the command handling.
    virtual ExecuteStatus GetCommandResult(uint16_t command, char response[ResponseSize], size_t& out_response_size) = 0;

protected:
    ~Executor() = default;
};

//======================================================
// These should be moved to a configuration header
constexpr static std::size_t MaxNumberOfPublishers{8U};
constexpr static std::size_t MaxNumberOfSubscribers{8U};
constexpr static std::size_t MaxNumberOfRequests{8U};
constexpr static std::size_t MaxNumberOfResponses{8U};
//======================================================

/// The Node implements basic functionality for the Cyphal Network.
/// The Heartbeat, GetInfo, GetTransportStatistics, diagnostic Records, and Register Access are implemented here.
class Node : protected cyphal::Interface::Listener,
             protected cyphal::Server,
             protected cyphal::Client,
             protected cyphal::Subscriber,
             protected cyphal::Publisher,
             protected cyphal::Executor {
public:
    /// The constructor for the Node class without a Node ID
    Node(jarnax::Timer const& timer, cyphal::Interface& interface, cyphal::UniqueId const& uid);
    /// The constructor for the Node class with a Node ID.
    Node(jarnax::Timer const& timer, cyphal::Interface& interface, cyphal::NodeId const id, cyphal::UniqueId const& uid);

    virtual ~Node() = default;

    /// Subscribes to a message for future delivery (duplicates allowed)
    core::Status Subscribe(SubjectId id, Subscriber&);
    /// Publishes a serialized message right now (no callback)
    core::Status Publish(SubjectId id, SerializedMessage msg);
    /// Publishes a message when available (publisher is queried later)
    core::Status Publish(SubjectId id, Publisher&);
    /// Publishes a message on a certain period (publisher is called on period expired)
    core::Status Publish(SubjectId id, Publisher&, core::units::MicroSeconds period);
    /// Publishes a Request to a Server
    core::Status Request(ServiceId id, NodeId recipient, Client&, SerializedMessage msg);
    /// Directly responds to the request from a Client
    core::Status Respond(ServiceId id, NodeId recipient, SerializedMessage msg);
    /// Registers a Server for a specific Id.
    core::Status Serve(ServiceId id, Server&);

    /// Dismisses a subscription, publication, or service registration.
    core::Status Dismiss(SubjectId id, Subscriber&);
    /// Dismisses a subscription, publication, or service registration.
    core::Status Dismiss(SubjectId id, Publisher&);
    /// Dismisses a subscription, publication, or service registration.
    core::Status Dismiss(ServiceId id, Client&);
    /// Dismisses a subscription, publication, or service registration.
    core::Status Dismiss(ServiceId id, Server&);

    /// Executes one iteration of the Node's main loop.
    bool RunOnce(void);

    /// Gets the Node ID for this Node.
    cyphal::NodeId const& GetId() const { return id_; }

    /// Gets the Unique Id for this Node.
    cyphal::UniqueId const& GetUniqueId() const { return uid_; }

    /// Informs the Node that an Executor is available to handle unhandled commands.
    core::Status SetExecutor(Executor& executor);

protected:
    //+=== Interface Callbacks ===+
    void OnReceive(Metadata const& metadata, SerializedMessage msg) override;
    //+=== Listener Callbacks ===+
    void OnRequest(ServiceId id, NodeId sender, SerializedMessage msg) override;
    core::Status GetResponse(ServiceId id, SerializedMessage& msg) override;
    void OnResponse(ServiceId id, NodeId responder, SerializedMessage msg) override;
    core::Status OnPublish(SubjectId id, SerializedMessage& msg) override;
    void OnBroadcast(SubjectId id, SerializedMessage msg) override;
    //+=== Executor ===+
    ExecuteStatus OnCommand(uint16_t command, char const parameters[Executor::ParamterSize]) override;
    ExecuteStatus GetCommandResult(uint16_t command, char response[Executor::ResponseSize], size_t& out_response_size) override;

    struct Statistics {
        size_t count{0u};      ///< The total number of operations attempted.
        size_t passed{0u};     ///< The number of successful operations.
        size_t dropped{0u};    ///< The number of dropped operations.
        size_t failed{0u};     ///< The number of failed operations.

        inline void Reset() {
            count = 0u;
            passed = 0u;
            dropped = 0u;
            failed = 0u;
        }
    };

    /// Holds information relevant to a published message in the Cyphal network
    struct PublishRecord {
        Publisher* publisher{nullptr};
        // TODO replace with a CountDown?
        core::units::MicroSeconds period{0u};
        core::units::MicroSeconds release{0u};    ///< The time when the message should be released
        SubjectId id{0U};
        Statistics statistics{};                  ///< The statistics for this publisher.
    };

    /// Holds information relevant to a subscribed message in the Cyphal network
    struct SubscriberRecord {
        Subscriber* subscriber{nullptr};
        SubjectId id{0U};
        Statistics statistics{};    ///< The statistics for this subscriber.
    };

    /// Holds information relevant to a service request in the Cyphal network
    struct RequestRecord {
        Client* client{nullptr};
        ServiceId id{0U};
        NodeId recipient{anonymous};               ///< The Node Id of the recipient
        Statistics statistics{};                   ///< The statistics for this request.
        core::units::MicroSeconds deadline{0u};    ///< The time when a response should be received to be considered on time.
    };

    /// Holds information relevant to a service response in the Cyphal network
    struct ResponseRecord {
        Server* server{nullptr};
        ServiceId id{0U};
        NodeId requester{anonymous};               ///< The Node Id of the requester
        Statistics statistics{};                   ///< The statistics for this response.
        bool responded{false};                     ///< Whether the server has responded to the request yet.
        core::units::MicroSeconds deadline{0u};    ///< The time when it has to respond by
    };

    /// The timer used by this Node.
    jarnax::Timer const& timer_;

    /// The Cyphal interface used by this Node for communication.
    cyphal::Interface& interface_;

    /// The Cyphal Node Id for this Node
    cyphal::NodeId id_;

    /// The Unique Id for this Node listed in GetInfo
    cyphal::UniqueId uid_;

    /// The Cyphal Health value of the Node
    cyphal::Health health_;

    /// The Cyphal Mode value of the Node
    cyphal::Mode mode_;

    /// The records of published messages for this Node.
    core::Array<PublishRecord, MaxNumberOfPublishers> publishers_;
    /// The records of subscribed messages for this Node.
    core::Array<SubscriberRecord, MaxNumberOfSubscribers> subscribers_;
    /// The records of service requests made by this Node.
    core::Array<RequestRecord, MaxNumberOfRequests> requesters_;
    /// The records of service responses handled by this Node.
    core::Array<ResponseRecord, MaxNumberOfResponses> responders_;

    size_t GetActiveSubscribers() const;
    size_t GetActivePublishers() const;
    size_t GetActiveRequesters() const;
    size_t GetActiveResponders() const;

    /// The executor responsible for handling unhandled commands.
    Executor* executor_;

    /// Tracks if the internal registration of this Node has been completed.
    bool internal_registered_;

    /// The location to store the serialized message data
    core::Array<uint8_t, MaxExtent> blob_;

    /// Executor
    bool outstanding_command_;
    uint16_t command_value_;
    char command_parameters_[ExecuteCommandRequestCommandStringSize];
    ExecuteStatus command_status_;

    /// We statically allocate a message blob for the maximum number of bytes that a message we send might need.
    core::Array<uint8_t, HeartbeatExtent> heartbeat_blob_;                  ///< The statically allocated message blob for Heartbeat messages.
    uavcan_node_port_List_1_0 port_list_{};                                 ///< The working Port List object.
    core::Array<uint8_t, PortListExtent> port_list_blob_;                   ///< The statically allocated message blob for PortList messages.
    core::Array<uint8_t, GetInfoResponseExtent> get_info_response_blob_;    ///< The statically allocated message blob for GetInfo response messages.
    core::Array<uint8_t, ExecuteCommandResponseExtent>
        execute_command_response_blob_;    ///< The statically allocated message blob for ExecuteCommand response messages.
    core::Array<uint8_t, GetTransportStatisticsExtent>
        get_transport_statistics_response_blob_;    ///< The statically allocated message blob for GetTransportStatistics response messages.
};

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_CYPHAL_NODE_HPP
