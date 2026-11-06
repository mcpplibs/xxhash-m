# Usage and API

`mcpplibs.mwrap.xxhash` 0.8.3 exports xxHash's stable API, upstream's names
unchanged. This page lists what each module holds and the places where a module
and a header differ. [tools/generate.py](../tools/generate.py) writes the lists
from the header, and CI checks them on every target.

## Modules

| Module | Holds |
|---|---|
| `mcpplibs.mwrap.xxhash` | XXH32: `XXH32`, `XXH32_state_t` with `XXH32_createState`, `_freeState`, `_copyState`, `_reset`, `_update`, `_digest`, `XXH32_canonical_t` with `XXH32_canonicalFromHash` and `XXH32_hashFromCanonical`; the same for XXH64; XXH3: `XXH3_64bits`, `XXH3_64bits_withSeed`, `XXH3_64bits_withSecret`, the 128-bit forms `XXH3_128bits*`, `XXH3_state_t` and its streaming functions, `XXH128_hash_t`, `XXH128_isEqual`, `XXH128_cmp`, `XXH128_canonical_t` and its conversions; `XXH32_hash_t`, `XXH64_hash_t`, `XXH_errorcode` with `XXH_OK` and `XXH_ERROR`; `XXH_versionNumber`. Re-exports the macros module |
| `mcpplibs.mwrap.xxhash.macros` | in `mcpplibs::mwrap::xxhash::macros`: `XXH_VERSION_MAJOR`, `_MINOR`, `_RELEASE`, `XXH_VERSION_NUMBER`; `XXH3_SECRET_SIZE_MIN`; the values of `XXH_VECTOR` (`XXH_SCALAR`, `XXH_SSE2`, `XXH_AVX2`, `XXH_AVX512`, `XXH_NEON`, `XXH_VSX`, `XXH_SVE`, `XXH_LSX`) |

## What is not exported

- **The static-linking section.** What `<xxhash.h>` declares only under
  `XXH_STATIC_LINKING_ONLY` (`XXH128`, `XXH3_generateSecret`,
  `XXH3_generateSecret_fromSeed`, the state structures' members, the
  `XXH3_*_withSecretandSeed` forms) may change in any release. A program that
  needs it includes `<xxhash.h>` with the macro and links the same
  `compat.xxhash`, which compiles the whole implementation.
- **Inline mode.** `XXH_INLINE_ALL` compiles a private copy into each unit
  that defines it; through the module, every unit calls the compiled library.
  The SSE2 path is the x86-64 baseline; `compat.xxhash` does not build the
  runtime dispatcher (`xxh_x86dispatch.c`).

## Macros

- **Constants.** Each object-like macro whose expansion is a constant
  expression is an `inline constexpr` of the same name and value;
  tests/macros.cpp compares every one with its macro.
- **Declaration syntax.** `XXH_PUBLIC_API`, `XXH_CONSTF`, `XXH_PUREF`,
  `XXH_MALLOCF`, `XXH_NOESCAPE`, `XXH_FALLTHROUGH`, the attribute probes
  `XXH_HAS_*` and `XXH_C23_VN` are not offered. tools/surface.toml lists them.
- The stable section has no macro with arguments; `<mwrap/xxhash/macros.hpp>`
  is empty in this release and exists so that every mwrap package has one.

## A header beside the module

`#include <xxhash.h>` and `import mcpplibs.mwrap.xxhash;` may appear in one
unit: they declare the same entities. A macro expands even inside a qualified
name, so `mcpplibs::mwrap::xxhash::macros::XXH_VERSION_NUMBER` written after the
header is `...::macros::(0 *100*100 + 8 *100 + 3)`. In such a unit use the
header's macros, or read their values under other names and `#undef` the
macros before naming the constants (tests/macros.cpp does this).

## Linking

The package depends on `compat.xxhash` 0.8.3, which compiles `xxhash.c` with
the target's toolchain. A program that imports the module links that library;
it does not look for a system xxHash.
