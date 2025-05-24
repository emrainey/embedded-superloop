#ifndef JARNAX_MOCK_TRANSACTOR_HPP_
#define JARNAX_MOCK_TRANSACTOR_HPP_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "jarnax/Transactor.hpp"
#include "jarnax/Transactable.hpp"

namespace jarnax {

template <typename TRANSACTABLE_TYPE>
class MockTransactor : public Transactor<jarnax::Transactable<TRANSACTABLE_TYPE>> {
public:
    MOCK_METHOD(core::Status, Verify, (jarnax::Transactable<TRANSACTABLE_TYPE> & transaction), (override));
    MOCK_METHOD(core::Status, Start, (jarnax::Transactable<TRANSACTABLE_TYPE> & transaction), (override));
    MOCK_METHOD(core::Status, Check, (jarnax::Transactable<TRANSACTABLE_TYPE> & transaction), (override));
    MOCK_METHOD(core::Status, Cancel, (jarnax::Transactable<TRANSACTABLE_TYPE> & transaction), (override));
};

}    // namespace jarnax

#endif    // JARNAX_MOCK_TRANSACTOR_HPP_