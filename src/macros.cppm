// mcpplibs.mwrap.xxhash.macros --- the macros of the headers that are a constant or a
// type, under their original names in mcpplibs::mwrap::xxhash::macros, each equal to
// the macro where the module is built (a named module cannot export a macro). The
// other macros are in <mwrap/xxhash/macros.hpp>. Written by tools/generate.py.
module;
#include <xxhash.h>

// The values, taken under other names while the macros are defined.
namespace mwrap_xxhash_capture {
inline constexpr auto value_XXH3_SECRET_SIZE_MIN = (XXH3_SECRET_SIZE_MIN);
inline constexpr auto value_XXH_AVX2 = (XXH_AVX2);
inline constexpr auto value_XXH_AVX512 = (XXH_AVX512);
inline constexpr auto value_XXH_LSX = (XXH_LSX);
inline constexpr auto value_XXH_NEON = (XXH_NEON);
inline constexpr auto value_XXH_SCALAR = (XXH_SCALAR);
inline constexpr auto value_XXH_SSE2 = (XXH_SSE2);
inline constexpr auto value_XXH_SVE = (XXH_SVE);
inline constexpr auto value_XXH_VERSION_MAJOR = (XXH_VERSION_MAJOR);
inline constexpr auto value_XXH_VERSION_MINOR = (XXH_VERSION_MINOR);
inline constexpr auto value_XXH_VERSION_NUMBER = (XXH_VERSION_NUMBER);
inline constexpr auto value_XXH_VERSION_RELEASE = (XXH_VERSION_RELEASE);
inline constexpr auto value_XXH_VSX = (XXH_VSX);
}
#undef XXH3_SECRET_SIZE_MIN
#undef XXH_AVX2
#undef XXH_AVX512
#undef XXH_LSX
#undef XXH_NEON
#undef XXH_SCALAR
#undef XXH_SSE2
#undef XXH_SVE
#undef XXH_VERSION_MAJOR
#undef XXH_VERSION_MINOR
#undef XXH_VERSION_NUMBER
#undef XXH_VERSION_RELEASE
#undef XXH_VSX

export module mcpplibs.mwrap.xxhash.macros;

export namespace mcpplibs::mwrap::xxhash::macros {
inline constexpr auto XXH3_SECRET_SIZE_MIN = mwrap_xxhash_capture::value_XXH3_SECRET_SIZE_MIN;
inline constexpr auto XXH_AVX2 = mwrap_xxhash_capture::value_XXH_AVX2;
inline constexpr auto XXH_AVX512 = mwrap_xxhash_capture::value_XXH_AVX512;
inline constexpr auto XXH_LSX = mwrap_xxhash_capture::value_XXH_LSX;
inline constexpr auto XXH_NEON = mwrap_xxhash_capture::value_XXH_NEON;
inline constexpr auto XXH_SCALAR = mwrap_xxhash_capture::value_XXH_SCALAR;
inline constexpr auto XXH_SSE2 = mwrap_xxhash_capture::value_XXH_SSE2;
inline constexpr auto XXH_SVE = mwrap_xxhash_capture::value_XXH_SVE;
inline constexpr auto XXH_VERSION_MAJOR = mwrap_xxhash_capture::value_XXH_VERSION_MAJOR;
inline constexpr auto XXH_VERSION_MINOR = mwrap_xxhash_capture::value_XXH_VERSION_MINOR;
inline constexpr auto XXH_VERSION_NUMBER = mwrap_xxhash_capture::value_XXH_VERSION_NUMBER;
inline constexpr auto XXH_VERSION_RELEASE = mwrap_xxhash_capture::value_XXH_VERSION_RELEASE;
inline constexpr auto XXH_VSX = mwrap_xxhash_capture::value_XXH_VSX;
}
