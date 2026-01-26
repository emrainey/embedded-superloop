#ifndef CORE_HAYES_TOKENIZER_HPP
#define CORE_HAYES_TOKENIZER_HPP

/// @file
/// Hayes Command Tokenizer

#include "core/Span.hpp"
#include "core/Statistician.hpp"
#include "memory.hpp"
#include "strings.hpp"

namespace core {
namespace hayes {

/// The statistics for the Tokenizer
struct TokenStatistics {
    size_t tokens{0U};
    size_t pushed{0U};
    size_t counted{0U};
    size_t dropped{0U};
};

using Token = core::Span<char>;

/// @brief A simple tokenizer that splits input data into tokens based on a separator string.
/// @tparam TOKEN_BUFFER_SIZE The size of the internal buffer to hold incoming data.
template <size_t TOKEN_BUFFER_SIZE>
class Tokenizer_ : public core::Statistician<TokenStatistics> {
public:
    /// The size of the internal token buffer
    constexpr static size_t TokenBufferSize = TOKEN_BUFFER_SIZE;
    /// Constructor with specified separator
    explicit Tokenizer_(char const* const separator)
        : core::Statistician<TokenStatistics>{}
        , separator_{separator}
        , separator_length_{strings::length(separator)}
        , fill_{0u}
        , received_{} {}
    /// Default Destructor
    ~Tokenizer_() = default;

    /// Pushes a string into the tokenizer buffer
    std::size_t Push(char const* const str) {
        std::size_t len = strings::length(str);
        return Push(str, len);
    }

    /// Pushes a buffer of data into the tokenizer buffer
    std::size_t Push(char const data[], size_t len) {
        std::size_t idx = 0;
        for (idx = 0; idx < len; idx++) {
            if (not Push(data[idx])) {
                break;
            }
        }
        return idx;
    }

    /// Retrieves the next token from the buffer
    Token Get() {
        auto* end = Match(separator_);
        if (end == nullptr) {
            return Token{};
        }
        size_t len = static_cast<size_t>((end + separator_length_) - received_);
        statistics_.tokens++;
        statistics_.counted += len;
        return Token{received_, len};
    }

    /// Consuming tokens invalidates all other tokens addresses!
    void Consume(Token token) {
        if (not token.IsEmpty()) {
            auto* end = token.data() + token.size();    // this already accounts for the separator
            size_t used = static_cast<size_t>(end - received_);
            if (fill_ >= used) {
                size_t remaining = fill_ - used;
                size_t dropped = static_cast<size_t>(end - received_);
                statistics_.dropped += dropped;
                memory::copy(received_, end, remaining);
                fill_ = remaining;
                memory::fill(&received_[fill_], 0, sizeof(received_) - remaining);
            }
        }
    }

    /// @return true if the buffer is empty, false otherwise
    bool IsEmpty() const { return (fill_ == 0); }

    /// @return true if the buffer is full, false otherwise
    bool IsFull() const { return (fill_ == sizeof(received_)); }

protected:
    /// Matches the separator in the received buffer
    char const* Match(char const* const prefix) {
        size_t len = strings::length(prefix);
        if (fill_ >= len) {
            size_t matchable = fill_ - len;
            for (size_t i = 0; i <= matchable; i++) {
                if (memory::compare(&received_[i], prefix, len) == 0) {
                    return &received_[i];
                }
            }
        }
        return nullptr;
    }

    /// Pushes a single character into the buffer
    bool Push(char c) {
        if (fill_ < sizeof(received_)) {
            received_[fill_++] = c;
            statistics_.pushed++;
            return true;
        }
        return false;
    }

    char const* const separator_;         ///< The separator string
    size_t separator_length_;             ///< The length of the separator string
    size_t fill_;                         ///< The current fill level of the buffer
    char received_[TOKEN_BUFFER_SIZE];    ///< The internal buffer to hold incoming data
};

}    // namespace hayes
}    // namespace core

#endif    // CORE_HAYES_TOKENIZER_HPP
