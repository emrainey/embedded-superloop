#ifndef GIT_HPP_
#define GIT_HPP_

/// The Git Namespace used to define several aspects of the project, such as the commit hash and tag. This allows us to have a single source of truth
/// for this information, which can be used throughout the codebase without having to hardcode it in multiple places. The Git variables are replaced
/// with their actual values at compile time, so we can use them to create constexpr variables that hold this information.
namespace git {

/// The short hash string used to identify the current state of the codebase, which can be useful for debugging and tracking changes. We can create a
/// constexpr string that holds this information at compile time.
using ShortHash = char[8U];

/// The Git Commit Hash is a unique identifier. Supports up to 64 chars plus null.
using FullHash = char[65U];

#if not defined(GIT_SHORT_HASH)
#define GIT_SHORT_HASH "unknown"
#endif

/// The Git Short Commit Hash is a unique identifier for the current state of the codebase, which can be useful for debugging and tracking changes. We
/// can create a constexpr string that holds this information at compile time.
constexpr static ShortHash const short_hash = GIT_SHORT_HASH;

#if not defined(GIT_FULL_HASH)
#define GIT_FULL_HASH "unknown"
#endif

/// The Git Full Commit Hash is a unique identifier for the current state of the codebase, which can be useful for debugging and tracking changes. We
/// can create a constexpr string that holds this information at compile time.
constexpr static FullHash const full_hash = GIT_FULL_HASH;

#if not defined(GIT_TAG)
#define GIT_TAG "unknown"
#endif

using Tag = char[64U];

/// The Git Tag is a human-readable identifier for a specific version of the codebase, which can be useful for logging or displaying the version
/// information in the application. We can create a constexpr string that holds this information at compile time.
constexpr static Tag const tag = GIT_TAG;

}    // namespace git

#endif    // GIT_HPP_
