// <mwrap/xxhash/macros.hpp> --- the macros of the headers that are neither a constant
// nor a type: they take arguments, or call a function. A named module cannot export a
// macro: include this header before `import mcpplibs.mwrap.xxhash;`. Each definition is
// upstream's (xxHash 0.8.3, BSD 2-Clause license), made only where the upstream header has
// not defined it, with the constants it names read from mcpplibs::mwrap::xxhash::macros
// and NULL written nullptr.
// The upstream header included after this one redefines these macros.
// Written by tools/generate.py.
#ifndef MWRAP_XXHASH_MACROS_HPP
#define MWRAP_XXHASH_MACROS_HPP

// The headers of this release define no such macro.

#endif  // MWRAP_XXHASH_MACROS_HPP
