#ifndef JARNAX_CONSOLE_HPP
#define JARNAX_CONSOLE_HPP

#include <core/Ring.hpp>
#include <cstdint>
#include <jarnax/Loopable.hpp>

namespace jarnax {
namespace console {
/// @brief The Console Interface
class Service : public Loopable {
public:
    static constexpr size_t OutputLength{1024U};
    static constexpr size_t InputLength{16U};

    /// @brief The Console Level
    enum class Level : std::uint8_t {
        Critical = 0U,    ///< Critical level (always printed)
        Error,            ///< Error level
        Warning,          ///< Warning level
        Info,             ///< Info level
        Debug,            ///< Debug level (rarely printed, often too verbose)
    };
    virtual void Print(Level level, char const* format, ...) = 0;

    /// @brief Sets the level of the console
    /// @param level
    inline void SetLevel(Level level) { level_ = level; }

    /// @brief Gets the level of the console
    /// @return
    inline Level GetLevel() const { return level_; }

protected:
    ~Service() = default;

    Level level_{Level::Warning};              ///< The current level of the console.
    core::Ring<char, OutputLength> output_;    ///< The output of the console
};
}    // namespace console
}    // namespace jarnax

#endif    // JARNAX_CONSOLE_HPP
