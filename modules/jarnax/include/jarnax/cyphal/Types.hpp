#ifndef JARNAX_CYPHAL_TYPES_HPP
#define JARNAX_CYPHAL_TYPES_HPP

#include "core/units/MicroSeconds.hpp"
#include "polyfill.hpp"

#include <core/Array.hpp>
#include <core/Span.hpp>
#include <core/Uint.hpp>
#include <type_traits>

#include "uavcan/diagnostic/Record_1_1.h"
#include "uavcan/node/ExecuteCommand_1_3.h"
#include "uavcan/node/GetInfo_1_0.h"
#include "uavcan/node/GetTransportStatistics_0_1.h"
#include "uavcan/node/Heartbeat_1_0.h"
#include "uavcan/node/port/List_1_0.h"

namespace jarnax {
namespace cyphal {

/// The unique identifier for a subject in the Cyphal network from 0 to 8191 (13 bits).
using SubjectId = core::uint16_<13>;

/// The unique identifier for a service in the Cyphal network from 0 to 511 (9 bits).
using ServiceId = core::uint16_<9>;

/// The serialized representation of a message in the Cyphal network.
using SerializedMessage = core::Span<std::uint8_t>;

/// The unique identifier for a node in the Cyphal network (16 bytes).
using UniqueId = core::Array<std::uint8_t, 16>;

/// The default timeout for service requests in the Cyphal network.
constexpr static core::units::MicroSeconds ServiceTimeout{1000000u};    // 1 second timeout for services

/// The default publish timeout for broadcast messages in the Cyphal network. If they aren't published within this time,
/// they are considered stale and dropped.
constexpr static core::units::MicroSeconds BroadcastTimeout{1000000u};    // 1 second timeout for broadcast messages

namespace can {
/// The unique identifier for a node in the Cyphal network from 0 to 127 (7 bits).
using NodeId = core::uint16_<7>;

/// The NodeId used to represent an anonymous node in the Cyphal network for CAN
constexpr static NodeId anonymous{static_cast<uint16_t>(0U)};
}    // namespace can

namespace udp {
/// The unique identifier for a node in the Cyphal network from 0 to 65535 (16 bits).
using NodeId = uint16_t;

/// The NodeId used to represent an anonymous node in the Cyphal network for UDP
constexpr static NodeId anonymous{static_cast<uint16_t>(0xFFFFU)};
}    // namespace udp

#if defined(JARNAX_CYPHAL_USE_CAN)
using can::anonymous;
using NodeId = can::NodeId;
#endif    // JARNAX_CYPHAL_USE_CAN

#if defined(JARNAX_CYPHAL_USE_UDP)
using udp::anonymous;
using NodeId = udp::NodeId;
#endif    // JARNAX_CYPHAL_USE_UDP

#if not defined(JARNAX_CYPHAL_USE_CAN) && not defined(JARNAX_CYPHAL_USE_UDP)
#error "No Cyphal transport protocol defined. Please define JARNAX_CYPHAL_USE_CAN or JARNAX_CYPHAL_USE_UDP."
#endif    // not defined(JARNAX_CYPHAL_USE_CAN) && not defined(JARNAX_CYPHAL_USE_UDP)

//+=====================================================================================+
// These convert common cyphal types from C to C++ values for easier usage in C++ code.

constexpr static SubjectId HeartbeatSubjectId{uavcan_node_Heartbeat_1_0_FIXED_PORT_ID_};              // Heartbeat subject ID
constexpr static ServiceId GetInfoServiceId{uavcan_node_GetInfo_1_0_FIXED_PORT_ID_};                  // GetInfo service ID
constexpr static ServiceId ExecuteCommandServiceId{uavcan_node_ExecuteCommand_1_3_FIXED_PORT_ID_};    // ExecuteCommand service ID (restart, etc)
constexpr static SubjectId PortListSubjectId{uavcan_node_port_List_1_0_FIXED_PORT_ID_};               // PortList subject ID
constexpr static SubjectId DiagnosticRecordSubjectId{uavcan_diagnostic_Record_1_1_FIXED_PORT_ID_};    // Diagnostic Record subject ID
constexpr static ServiceId GetTransportStatisticsServiceId{
    uavcan_node_GetTransportStatistics_0_1_FIXED_PORT_ID_
};    // GetTransportStatistics service ID

constexpr static size_t HeartbeatExtent{uavcan_node_Heartbeat_1_0_EXTENT_BYTES_};
constexpr static size_t GetInfoResponseExtent{uavcan_node_GetInfo_Response_1_0_EXTENT_BYTES_};
constexpr static size_t ExecuteCommandRequestExtent{uavcan_node_ExecuteCommand_Request_1_3_EXTENT_BYTES_};
constexpr static size_t ExecuteCommandResponseExtent{uavcan_node_ExecuteCommand_Response_1_3_EXTENT_BYTES_};
constexpr static size_t PortListExtent{uavcan_node_port_List_1_0_EXTENT_BYTES_};
constexpr static size_t DiagnosticRecordExtent{uavcan_diagnostic_Record_1_1_EXTENT_BYTES_};
constexpr static size_t GetTransportStatisticsExtent{uavcan_node_GetTransportStatistics_Response_0_1_EXTENT_BYTES_};

constexpr static size_t Extents[] = {
    HeartbeatExtent,
    GetInfoResponseExtent,
    ExecuteCommandRequestExtent,
    ExecuteCommandResponseExtent,
    PortListExtent,
    DiagnosticRecordExtent,
    GetTransportStatisticsExtent,
};
constexpr static size_t NumExtents{dimof(Extents)};

constexpr static size_t FindMaxValue(size_t const* values, size_t count) {
    size_t max_value = 0;
    for (size_t i = 0; i < count; ++i) {
        if (values[i] > max_value) {
            max_value = values[i];
        }
    }
    return max_value;
}

/// Find the largest serialization buffer size among all message types by putting all the types in a constexpr array, then searching it at compile
/// time.
constexpr static size_t MaxExtent{FindMaxValue(Extents, NumExtents)};

constexpr static size_t ExecuteCommandRequestCommandStringSize{uavcan_node_ExecuteCommand_Request_1_3_parameter_ARRAY_CAPACITY_};
constexpr static size_t ExecuteCommandResponseStringSize{uavcan_node_ExecuteCommand_Response_1_3_output_ARRAY_CAPACITY_};

enum class Health : uint8_t {
    Nominal = uavcan_node_Health_1_0_NOMINAL,
    Advisory = uavcan_node_Health_1_0_ADVISORY,
    Caution = uavcan_node_Health_1_0_CAUTION,
    Warning = uavcan_node_Health_1_0_WARNING
};

enum class Mode : uint8_t {
    Operational = uavcan_node_Mode_1_0_OPERATIONAL,
    Initialization = uavcan_node_Mode_1_0_INITIALIZATION,
    Maintenance = uavcan_node_Mode_1_0_MAINTENANCE,
    SoftwareUpdate = uavcan_node_Mode_1_0_SOFTWARE_UPDATE
};

enum class ExecuteStatus : uint8_t {
    Success = uavcan_node_ExecuteCommand_Response_1_3_STATUS_SUCCESS,
    Failure = uavcan_node_ExecuteCommand_Response_1_3_STATUS_FAILURE,
    NotAuthorized = uavcan_node_ExecuteCommand_Response_1_3_STATUS_NOT_AUTHORIZED,
    BadCommand = uavcan_node_ExecuteCommand_Response_1_3_STATUS_BAD_COMMAND,
    BadParameter = uavcan_node_ExecuteCommand_Response_1_3_STATUS_BAD_PARAMETER,
    BadState = uavcan_node_ExecuteCommand_Response_1_3_STATUS_BAD_STATE,
    InternalError = uavcan_node_ExecuteCommand_Response_1_3_STATUS_INTERNAL_ERROR
};

using Heartbeat = uavcan_node_Heartbeat_1_0;
using GetInfoResponse = uavcan_node_GetInfo_Response_1_0;
using ExecuteCommandRequest = uavcan_node_ExecuteCommand_Request_1_3;
using ExecuteCommandResponse = uavcan_node_ExecuteCommand_Response_1_3;
using PortList = uavcan_node_port_List_1_0;
using GetTransportStatisticsResponse = uavcan_node_GetTransportStatistics_Response_0_1;

constexpr static core::units::MicroSeconds HeartbeatPeriod{1000000u};    // Example period of 1 second
constexpr static core::units::MicroSeconds PortListPeriod{10000000u};    // Example period of 10 seconds

//+=====================================================================================+

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_CYPHAL_TYPES_HPP
