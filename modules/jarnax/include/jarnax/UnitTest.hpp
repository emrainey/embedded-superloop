#ifndef SYSTEM_UNITTEST_HPP_
#define SYSTEM_UNITTEST_HPP_

/// @file
/// The UniTest Interface

#include "jarnax/system.hpp"
#include "jarnax/Executable.hpp"

namespace jarnax {

/// The UnitTest template class which allows users to create set of tests based on an enumeration and a
/// naming array.
/// @tparam NUM_TESTS The number of tests to statically allocate. Must be a power of two.
template <typename ENUM_TYPE, size_t RESULT_COUNT>
class UnitTest : public Executable {
public:
    // Only enumeration types are allowed
    static_assert(std::is_enum<ENUM_TYPE>::value, "Must be an enumeration type");
    /// @brief The enumeration type
    using EnumType = ENUM_TYPE;
    /// @brief The underlying type of the enumeration
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    // must be an integer
    static_assert(std::is_integral<UnderlyingType>::value, "Must be an integer underlying type");
    // must be in order
    static_assert(EnumType::kMinimum < EnumType::kMaximum, "Must have a minimum and maximum and be in order");
    /// The inclusive test enumeration bottom bound
    constexpr static UnderlyingType kMinimum = to_underlying(EnumType::kMinimum);
    /// The exclusive test enumeration top bound
    constexpr static UnderlyingType kMaximum = to_underlying(EnumType::kMaximum);
    static_assert(to_underlying(EnumType::kStep) > 0U, "Must be a positive step");

    /// The step to move after each test
    constexpr static UnderlyingType kStep = to_underlying(EnumType::kStep);
    /// The number of tests to perform
    constexpr static size_t kNumTests = kMaximum - kMinimum;
    static_assert(kNumTests % kStep == 0, "The number of Tests Must be step-able exactly by kStep");

    /// Used to indicate the state of the test
    enum class State : char {
        NotEvalutated = '?',
        Completed = 'C',
        Skipped = '-',
    };

    /// @brief Used to indicate the result of the test
    enum class Result : char {
        Unknown = '?',
        Passed = 'P',
        Failed = 'X',
    };

    /// @brief Associates a name with a test enumeration
    struct TestName {
        TestName(char const* const n, EnumType const te)
            : name{n}
            , test_enum{te} {}
        char const* const name;
        EnumType const test_enum;
    };

/// Used to define an entry in an array of test names.
/// @see @ref TestName
#define DEFINE_TEST_NAME(name) \
    { #name, name }

    static constexpr size_t NumTestNames = to_underlying(EnumType::kMaximum) - to_underlying(EnumType::kMinimum) + 1U;

    /// Default Constructor
    UnitTest(char const* const name, TestName const (&test_names)[NumTestNames])
        : m_name_{name}
        , m_test_index_{IndexOf(EnumType::kMinimum)}
        , m_test_enum_{EnumType::kMinimum}
        , m_test_names_{test_names} {
        for (size_t i = 0; i < kNumTests; ++i) {
            m_states_[i] = State::NotEvalutated;
        }
        for (size_t i = 0; i < RESULT_COUNT; ++i) {
            m_results_[i].test_enum = EnumType::kMinimum;
            m_results_[i].test_result = Result::Unknown;
        }
    }

    /// Returns the current state of the tests
    /// @return The current state per test (if no test is given index zero is used)
    inline State GetState(EnumType test_enum) const {
        // convert to the index
        UnderlyingType index = to_underlying(test_enum);
        // if bounds checkout, return State
        if (kMinimum <= index and index <= kMaximum) {
            return m_states_[index - kMinimum];
        } else {
            // otherwise, it's never been run
            return State::NotEvalutated;
        }
    }

    bool Execute(LoopInfo const&) override {
        bool continue_tests = true;
        if (m_test_index_ < kMaximum) {
            if (m_states_[m_test_index_] == State::NotEvalutated) {
                jarnax::print(
                    "%s Running Test %s [%lu] ... ",
                    m_name_,
                    m_test_names_[m_test_index_].name,
                    static_cast<unsigned long>(m_test_index_)
                );
                // run it
                m_states_[m_test_index_] = Test(m_test_enum_);
                // print results
                if (m_states_[m_test_index_] == State::Skipped) {
                    jarnax::print("SKIPPED\n");
                } else if (m_states_[m_test_index_] == State::Completed) {
                    jarnax::print("COMPLETED\n");
                    for (size_t i = 0; i < m_result_index_; ++i) {
                        if (m_results_[i].test_enum == m_test_enum_) {
                            jarnax::print("%c", to_underlying(m_results_[i].test_result));
                        }
                    }
                    jarnax::print("\r\n");
                } else {
                    jarnax::print("NOT EVALUTED\n");
                }
            }
            // it has run in some way (if not leave it alone)
            m_test_index_ = (m_test_index_ + kStep);
            // go to next enum
            m_test_enum_ = EnumOf(m_test_index_);
        } else {
            continue_tests = false;
        }
        return continue_tests;
    }

    /// Implemented by unit tests
    /// @param
    virtual State Test(EnumType e) = 0;

protected:
    void Assert(bool condition, char const* const description = nullptr) {
        (void)description;
        record(condition);
    }

    template <typename TYPE>
    void CompareEqual(TYPE const lhs, TYPE const rhs) {
        static_assert(not std::is_floating_point<TYPE>::value, "Can not be a floating point value");
        bool volatile result = (lhs == rhs);
        record(result);
    }

    template <typename TYPE>
    void CompareNotEqual(TYPE const lhs, TYPE const rhs) {
        static_assert(not std::is_floating_point<TYPE>::value, "Can not be a floating point value");
        bool volatile result = (lhs != rhs);
        record(result);
    }

    void CompareFloatEqual(float lhs, float rhs) {
        bool volatile result = (absolute_difference(lhs, rhs) <= std::numeric_limits<float>::epsilon());
        record(result);
    }

    void CompareFloatNotEqual(float lhs, float rhs) {
        bool volatile result = (absolute_difference(lhs, rhs) > std::numeric_limits<float>::epsilon());
        record(result);
    }

    template <typename TYPE>
    void CompareRefEqual(TYPE const& lhs, TYPE const& rhs) {
        static_assert(not std::is_floating_point<TYPE>::value, "Can not be a floating point value");
        bool volatile result = (lhs == rhs);
        record(result);
    }

    template <typename TYPE>
    void CompareRefNotEqual(TYPE const& lhs, TYPE const& rhs) {
        static_assert(not std::is_floating_point<TYPE>::value, "Can not be a floating point value");
        bool volatile result = (lhs != rhs);
        record(result);
    }

    // this should be moved into the "standard" area for float operations
    float absolute_difference(float lhs, float rhs) {
        float difference = rhs - lhs;
        if (lhs > rhs) {
            difference = lhs - rhs;
        }
        return difference;
    }

    inline EnumType GetEnum(void) const { return m_test_enum_; }
    inline UnderlyingType GetIndex(void) const { return m_test_index_; }

private:
    /// Returns the index of the enumerated value
    /// @param value The numerated value
    /// @return The index in the underlying type
    UnderlyingType IndexOf(EnumType value) const { return to_underlying(value) - kMinimum; }

    /// return the enumerated value from an index
    /// @param index The index to enumerate
    /// @return Returns the enum typed value
    EnumType EnumOf(UnderlyingType index) const { return static_cast<EnumType>(index + kMinimum); }

    /// Records the outcome of the active test, does not overwrite previous recordings
    /// if the current tests has not been run, record the outcome.
    /// there it has been run only allow overwrite on previous success.
    /// failures should never be forgotten,
    /// additional failures or successes will be dropped
    void record(bool volatile& evaluation) {
        if (m_result_index_ < RESULT_COUNT) {
            m_result_counts_[m_test_index_]++;    // increment the count
            m_results_[m_result_index_].test_enum = m_test_enum_;
            m_results_[m_result_index_].test_result = evaluation ? Result::Passed : Result::Failed;
        } else {
            jarnax::print(
                "Exceeded Result Count of %" PRIz ". Now at %" PRIz "!\r\n",
                m_result_counts_[m_test_index_],
                m_result_index_
            );
        }
        m_result_index_++;
    }

private:
    char const* const m_name_;                        ///< The string literal name.
    UnderlyingType m_test_index_;                     ///< The active test index
    EnumType m_test_enum_;                            ///< The active enum
    State m_states_[kNumTests];                       ///< The state of the Test
    TestName const (&m_test_names_)[NumTestNames];    ///< The list of the test names
    size_t m_result_counts_[NumTestNames];            ///< The number of results per test enumeration
    size_t m_result_index_{0U};                       ///< The index of the result
    struct ResultCoorelation {
        EnumType test_enum;
        Result test_result;
    };
    ResultCoorelation m_results_[RESULT_COUNT];    ///< The results of each test
};

}    // namespace jarnax

#endif    // SYSTEM_UNITTEST_HPP_