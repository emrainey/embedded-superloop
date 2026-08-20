#ifndef JARNAX_CYPHAL_MOCK_INTERFACE_HPP
#define JARNAX_CYPHAL_MOCK_INTERFACE_HPP

#include <gmock/gmock.h>

#include "jarnax/cyphal/Interface.hpp"

namespace jarnax {
namespace cyphal {

class MockInterface : public Interface {
public:
    MOCK_METHOD(core::Status, RegisterListener, (NodeId id, Listener& listener), (override));
    MOCK_METHOD(core::Status, Listen, (PortId port_id), (override));
    MOCK_METHOD(core::Status, Remove, (PortId port_id), (override));
    MOCK_METHOD(bool, IsListening, (PortId port_id), (const, override));
    MOCK_METHOD(core::Status, Send, (Metadata & metadata, SerializedMessage msg), (override));
    MOCK_METHOD(core::Status, GetStatistics, (TransportStatistics & statistics), (override));

    virtual ~MockInterface() = default;
};

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_CYPHAL_MOCK_INTERFACE_HPP
