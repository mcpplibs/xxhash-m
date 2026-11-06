# xxhash

> xxHash, the extremely fast non-cryptographic hash, through C++23 modules.

**English** · [简体中文](README.zh.md) · [Upstream](https://github.com/Cyan4973/xxHash) · [Releases](https://github.com/mcpplibs/xxhash-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [Index](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/xxhash-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/xxhash-m/actions/workflows/ci.yml)

The upstream API is unchanged. `XXH32`, `XXH64`, `XXH3_64bits`,
`XXH3_128bits`, their streaming states, `XXH128_hash_t` and the canonical
forms are the upstream entities of `<xxhash.h>`, in the global namespace where
upstream declares them. The library is `compat.xxhash` 0.8.3, compiled rather
than inlined. The constant macros are C++ constants. Upstream's own sanity
test passes its 49948 vectors on every CI run over the same library.

## Modules

- `import mcpplibs.mwrap.xxhash;`: the stable API of `<xxhash.h>`, re-exporting the macros module
- `import mcpplibs.mwrap.xxhash.macros;`: `XXH_VERSION_NUMBER`, `XXH3_SECRET_SIZE_MIN`, the vector selectors `XXH_SCALAR` … `XXH_AVX512` … in `mcpplibs::mwrap::xxhash::macros`

> More Modules API -> [Usage and API](docs/usage.md)

## Getting started

```sh
mcpp new digest --template mcpplibs.mwrap.xxhash@0.8.3
cd digest
mcpp run
```

The default template prints the XXH3-64, XXH3-128 and XXH64 of a text or a
file, and checks that streaming gives the same XXH3-64.

```toml
[dependencies]
"mcpplibs.mwrap.xxhash" = "0.8.3"
```

```cpp
import std;
import mcpplibs.mwrap.xxhash;

int main() {
    std::string_view text = "hello";
    std::println("{:016x}", XXH3_64bits(text.data(), text.size()));
}
```

## Scope and macros

The module exports the stable API: what `<xxhash.h>` declares without
`XXH_STATIC_LINKING_ONLY`. The static-linking section (`XXH128`, the
`XXH3_generateSecret` functions, the state structures' fields, inline mode)
may change between releases and is not exported. Upstream's header-only mode
(`XXH_INLINE_ALL`) is a property of each including unit; through the module,
every unit calls the one compiled library.

A named module cannot export a macro. The constants are `inline constexpr`
of the same names in `mcpplibs::mwrap::xxhash::macros`. The stable section
defines no macro with arguments, so `<mwrap/xxhash/macros.hpp>` is empty in
this release. The attribute and linkage macros only spell the declarations.

## Build and testing

Linux, macOS and Windows CI build the modules with GCC and LLVM and run the
tests: the four hashes of the empty input as upstream publishes them,
streaming in uneven pieces and from a copied state equal to one call, a
secret, the canonical big-endian forms, the 128-bit comparisons, the version
against its macro, every constant against its macro, every exported function
linked, and header mixing. CI also runs:

- the export audit ([tools/generate.py](tools/generate.py) `--check`): the
  module, the macro mapping, the macro header and the generated tests are
  regenerated from the header as clang reads it and compared, and on macOS and
  Windows every name the header declares there is exported;
- upstream's `tests/sanity_test.c` over the same library
  ([tools/run_conformance.py](tools/run_conformance.py)).

A separate job scaffolds the default template as an installed package and runs
it.

## License

[Apache-2.0](LICENSE) for the wrapper, by mcpp-community ([NOTICE](NOTICE)).
xxHash remains under the BSD 2-Clause license
([upstream/xxhash/LICENSE](upstream/xxhash/LICENSE),
[README](upstream/xxhash/README.md)).
