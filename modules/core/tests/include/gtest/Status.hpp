#ifndef GTEST_CORE_STATUS_HPP
#define GTEST_CORE_STATUS_HPP

/// @file
/// GoogleTest Assertions for core::Status

#include <gtest/gtest.h>

// =======================================================
#define ASSERT_STATUS_EQ(__status, __result, __cause)                                               \
    {                                                                                               \
        ASSERT_EQ(__result, __status.GetResult()) << "Was " << GetResultName(__status.GetResult()); \
        ASSERT_EQ(__cause, __status.GetCause()) << "Was " << GetCauseName(__status.GetCause());     \
    }
// =======================================================
#define EXPECT_STATUS_EQ(__status, __result, __cause)                                               \
    {                                                                                               \
        EXPECT_EQ(__result, __status.GetResult()) << "Was " << GetResultName(__status.GetResult()); \
        EXPECT_EQ(__cause, __status.GetCause()) << "Was " << GetCauseName(__status.GetCause());     \
    }
// =======================================================

#endif    // GTEST_CORE_STATUS_HPP
