#include "strings.hpp"

namespace strings {
size_t length(char const string[]) {
    size_t length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}
}    // namespace strings