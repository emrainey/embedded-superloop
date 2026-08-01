#ifndef STRINGS_HPP_
#define STRINGS_HPP_

/// @file
/// A basic re-implementation of the C/C++ string functions.

#include <cstddef>

namespace strings {

size_t length(char const string[]);

/// Finds the last occurrence of a character within a string.
/// @param string The string to search.
/// @param character The character to search for.
/// @return A pointer to the last occurrence of the character, or nullptr if not found.
char const* last_character(char const string[], char character);

}    // namespace strings

#endif    // STRINGS_HPP_
