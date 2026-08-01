#include "strings.hpp"

namespace strings {
char const* last_character(char const string[], char character) {
    char const* result = nullptr;
    for (char const* scan = string; *scan != '\0'; ++scan) {
        asm volatile("" ::: "memory"); // prevent "optimizer" from using strrchr
        if (*scan == character) {
            result = scan;
        }
    }
    return result;
}
}    // namespace strings
