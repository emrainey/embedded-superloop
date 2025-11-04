#ifndef JARNAX_MOCK_CACHE_HPP_
#define JARNAX_MOCK_CACHE_HPP_

/// @file
/// A Mock Cache Control Interface for Jarnax unit tests
#include <jarnax/Cache.hpp>

namespace jarnax {

class MockDataCache : public DataCache {
public:
    MOCK_METHOD(void, Enable, (), (override));
    MOCK_METHOD(void, Disable, (), (override));
    MOCK_METHOD(void, Invalidate, (), (override));
    MOCK_METHOD(void, Invalidate, (std::uintptr_t address, size_t bytes), (override));
    MOCK_METHOD(void, Clean, (), (override));
    MOCK_METHOD(void, Clean, (std::uintptr_t address, size_t bytes), (override));
    MOCK_METHOD(void, Flush, (), (override));
    MOCK_METHOD(void, Flush, (std::uintptr_t address, size_t bytes), (override));
    virtual ~MockDataCache() = default;
};

class MockInstructionCache : public InstructionCache {
public:
    MOCK_METHOD(void, Enable, (), (override));
    MOCK_METHOD(void, Disable, (), (override));
    MOCK_METHOD(void, Invalidate, (), (override));
    MOCK_METHOD(void, Invalidate, (std::uintptr_t address, size_t bytes), (override));
    virtual ~MockInstructionCache() = default;
};

}    // namespace jarnax

#endif
