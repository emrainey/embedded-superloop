#ifndef CORE_HAYES_TOKENIZER_HPP
#define CORE_HAYES_TOKENIZER_HPP

#include "core/Span.hpp"
#include "core/Statistician.hpp"
#include "memory.hpp"
#include "strings.hpp"

namespace core {
namespace hayes {

struct TokenStatistics {
    size_t tokens{0U};
    size_t pushed{0U};
    size_t counted{0U};
    size_t dropped{0U};
};

using Token = core::Span<char>;

template <size_t TOKEN_BUFFER_SIZE>
class Tokenizer_ : public core::Statistician<TokenStatistics> {
public:
    constexpr static size_t TokenBufferSize = TOKEN_BUFFER_SIZE;
    Tokenizer_(char const* const separator)
        : core::Statistician<TokenStatistics>{}
        , separator_{separator}
        , separator_length_{strings::length(separator)}
        , fill_{0u}
        , received_{} {}

    std::size_t Push(char const* const str) {
        std::size_t len = strings::length(str);
        return Push(str, len);
    }

    std::size_t Push(char const data[], size_t len) {
        std::size_t idx = 0;
        for (idx = 0; idx < len; idx++) {
            if (not Push(data[idx])) {
                break;
            }
        }
        return idx;
    }

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

    bool IsEmpty() const { return (fill_ == 0); }
    bool IsFull() const { return (fill_ == sizeof(received_)); }

protected:
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

    bool Push(char c) {
        if (fill_ < sizeof(received_)) {
            received_[fill_++] = c;
            statistics_.pushed++;
            return true;
        }
        return false;
    }

    char const* const separator_;
    size_t separator_length_;
    size_t fill_;
    char received_[TOKEN_BUFFER_SIZE];
};

}    // namespace hayes
}    // namespace core

#endif    // CORE_HAYES_TOKENIZER_HPP
