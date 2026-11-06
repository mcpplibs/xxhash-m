// Each constant and type of mcpplibs.mwrap.xxhash.macros equals its macro. A macro
// expands even in a qualified name, so the values of the headers are taken under other
// names and the macros undefined before the mapped names are used. Written by
// tools/generate.py.
#include <xxhash.h>

namespace header {
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

import std;
import mcpplibs.mwrap.xxhash.macros;

namespace m = mcpplibs::mwrap::xxhash::macros;


template <class A, class B>
bool same(A a, B b)
{
    if constexpr (std::is_convertible_v<A, const char*> && std::is_convertible_v<B, const char*>)
        return std::string_view(a) == std::string_view(b);
    else
        return a == b;
}

int main()
{
    int differ = 0;
    if (!same(m::XXH3_SECRET_SIZE_MIN, header::value_XXH3_SECRET_SIZE_MIN)) { std::println("FAIL XXH3_SECRET_SIZE_MIN"); ++differ; }
    if (!same(m::XXH_AVX2, header::value_XXH_AVX2)) { std::println("FAIL XXH_AVX2"); ++differ; }
    if (!same(m::XXH_AVX512, header::value_XXH_AVX512)) { std::println("FAIL XXH_AVX512"); ++differ; }
    if (!same(m::XXH_LSX, header::value_XXH_LSX)) { std::println("FAIL XXH_LSX"); ++differ; }
    if (!same(m::XXH_NEON, header::value_XXH_NEON)) { std::println("FAIL XXH_NEON"); ++differ; }
    if (!same(m::XXH_SCALAR, header::value_XXH_SCALAR)) { std::println("FAIL XXH_SCALAR"); ++differ; }
    if (!same(m::XXH_SSE2, header::value_XXH_SSE2)) { std::println("FAIL XXH_SSE2"); ++differ; }
    if (!same(m::XXH_SVE, header::value_XXH_SVE)) { std::println("FAIL XXH_SVE"); ++differ; }
    if (!same(m::XXH_VERSION_MAJOR, header::value_XXH_VERSION_MAJOR)) { std::println("FAIL XXH_VERSION_MAJOR"); ++differ; }
    if (!same(m::XXH_VERSION_MINOR, header::value_XXH_VERSION_MINOR)) { std::println("FAIL XXH_VERSION_MINOR"); ++differ; }
    if (!same(m::XXH_VERSION_NUMBER, header::value_XXH_VERSION_NUMBER)) { std::println("FAIL XXH_VERSION_NUMBER"); ++differ; }
    if (!same(m::XXH_VERSION_RELEASE, header::value_XXH_VERSION_RELEASE)) { std::println("FAIL XXH_VERSION_RELEASE"); ++differ; }
    if (!same(m::XXH_VSX, header::value_XXH_VSX)) { std::println("FAIL XXH_VSX"); ++differ; }
    std::println("13 constants and 0 types compared, {} differ", differ);
    return differ != 0;
}
