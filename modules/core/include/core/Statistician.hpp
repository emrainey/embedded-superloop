#ifndef CORE_STATISTICIAN_HPP
#define CORE_STATISTICIAN_HPP

/// @file
/// Statistics Tracking Mixin Class

#include <cstdint>
#include <type_traits>

namespace core {

/// @brief A mixin class to provide statistics tracking for derived classes
/// @tparam TYPE The statistics structure type
template <typename TYPE>
class Statistician {
public:
    static_assert(std::is_trivially_copyable_v<TYPE>, "Statistician can only be used with trivially copyable types, such as structs or POD types.");

    /// The type of the statistics structure
    using StatisticsType = TYPE;

    /// @brief Constructor
    Statistician()
        : statistics_{} {}

    /// @brief Returns a const reference to the statistics structure
    inline StatisticsType const& GetStatistics(void) const { return statistics_; }

    /// @brief Clears the Statistics to default values
    inline void ClearStatistics(void) { statistics_ = StatisticsType{}; }

protected:
    ~Statistician() = default;

    /// @brief The statistics structure
    StatisticsType statistics_;
};

}    // namespace core

#endif    // CORE_STATISTICIAN_HPP
