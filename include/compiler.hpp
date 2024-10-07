#ifndef COMPILER_HPP_
#define COMPILER_HPP_

/// @file
/// Contains compiler specific attributes and macros. These should be the only MACROS in the system

#if defined(UNITTEST)
#define ATTRIBUTE(x)
#define LINKER_SECTION(x)
#define NAKED
#define USED
#define ALWAYS_INLINE
#else
#define ATTRIBUTE(x) __attribute__(x)
#define LINKER_SECTION(x) __attribute__((used, section(x)))
#define NAKED __attribute__((used, naked))
#define USED __attribute__((used))
#define ALWAYS_INLINE __attribute__((always_inline))
#endif

#endif    // COMPILER_HPP_