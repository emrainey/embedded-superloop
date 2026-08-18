#ifndef JARNAX_CYPHAL_MOCK_NODE_HELPERS_HPP
#define JARNAX_CYPHAL_MOCK_NODE_HELPERS_HPP

#include <gmock/gmock.h>

#include "core/Status.hpp"
#include "jarnax/cyphal/Node.hpp"

namespace jarnax::cyphal::mock {

class MockClient : public jarnax::cyphal::Client {
public:
    MockClient() = default;
    virtual ~MockClient() = default;
    MOCK_METHOD(void, OnResponse, (ServiceId, NodeId, SerializedMessage), (override));
};

class MockServer : public jarnax::cyphal::Server {
public:
    MockServer() = default;
    virtual ~MockServer() = default;
    MOCK_METHOD(void, OnRequest, (ServiceId, NodeId, SerializedMessage), (override));
    MOCK_METHOD(core::Status, GetResponse, (ServiceId, SerializedMessage&), (override));
};

class MockSubscriber : public jarnax::cyphal::Subscriber {
public:
    MockSubscriber() = default;
    virtual ~MockSubscriber() = default;
    MOCK_METHOD(void, OnBroadcast, (SubjectId, SerializedMessage), (override));
};

class MockPublisher : public jarnax::cyphal::Publisher {
public:
    MockPublisher() = default;
    virtual ~MockPublisher() = default;
    MOCK_METHOD(core::Status, OnPublish, (SubjectId, SerializedMessage&), (override));
};

class MockExecutor : public jarnax::cyphal::Executor {
public:
    MockExecutor() = default;
    virtual ~MockExecutor() = default;
    MOCK_METHOD(ExecuteStatus, OnCommand, (uint16_t, char const[ParamterSize]), (override));
    MOCK_METHOD(ExecuteStatus, GetCommandResult, (uint16_t, char[ResponseSize], size_t&), (override));
};

}    // namespace jarnax::cyphal::mock

#endif    // JARNAX_CYPHAL_MOCK_NODE_HELPERS_HPP
