#ifndef JARNAX_MOCK_TRANSACTOR_HPP_
#define JARNAX_MOCK_TRANSACTOR_HPP_

/// @file
/// GoogleMock Transaction Executor

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "jarnax/Transactable.hpp"
#include "jarnax/Transactor.hpp"

namespace jarnax {

template <typename TRANSACTABLE_TYPE>
class MockTransactor : public Transactor<TRANSACTABLE_TYPE> {
public:
    MOCK_METHOD(core::Status, Verify, (TRANSACTABLE_TYPE & transaction), (override));
    MOCK_METHOD(core::Status, Start, (TRANSACTABLE_TYPE & transaction), (override));
    MOCK_METHOD(core::Status, Check, (TRANSACTABLE_TYPE & transaction), (override));
    MOCK_METHOD(core::Status, Cancel, (TRANSACTABLE_TYPE & transaction), (override));
    virtual ~MockTransactor() = default;
};

}    // namespace jarnax

#endif    // JARNAX_MOCK_TRANSACTOR_HPP_
