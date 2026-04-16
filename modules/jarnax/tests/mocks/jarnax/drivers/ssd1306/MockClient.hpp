/// @file
/// GoogleMock SSD1306 StateMachine Client

#include <gmock/gmock.h>
#include "jarnax/drivers/ssd1306/StateMachine.hpp"

namespace jarnax {
namespace drivers {
namespace ssd1306 {

class MockClient : public Client {
public:
    MOCK_METHOD(bool, IsPresent, (), (const, override));
    MOCK_METHOD(core::Status, PrepareCommand, (Sequence sequence), (override));
    MOCK_METHOD(core::Status, PrepareRender, (Sequence sequence), (override));
    MOCK_METHOD(core::Status, Issue, (), (override));
    MOCK_METHOD(bool, IsComplete, (), (const, override));
    MOCK_METHOD(bool, CompleteCommand, (core::Status & status), (override));
    MOCK_METHOD(void, OnEvent, (Event event, core::Status status), (override));
    MOCK_METHOD(bool, IsReadyForPreparation, (), (const, override));
    virtual ~MockClient() = default;
};

}    // namespace ssd1306
}    // namespace drivers
}    // namespace jarnax
