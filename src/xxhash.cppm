// mcpplibs.mwrap.xxhash --- xxHash 0.8.3 as a C++ module. Every exported name is
// the upstream entity of the headers below, unchanged, in the global namespace where
// upstream declares it; the root also re-exports the macro mapping. The implementation
// is compat.xxhash 0.8.3. Written by tools/generate.py from the headers.
module;
#include <xxhash.h>

export module mcpplibs.mwrap.xxhash;

export import mcpplibs.mwrap.xxhash.macros;

export {
using ::XXH128_canonicalFromHash;
using ::XXH128_canonical_t;
using ::XXH128_cmp;
using ::XXH128_hashFromCanonical;
using ::XXH128_hash_t;
using ::XXH128_isEqual;
using ::XXH32;
using ::XXH32_canonicalFromHash;
using ::XXH32_canonical_t;
using ::XXH32_copyState;
using ::XXH32_createState;
using ::XXH32_digest;
using ::XXH32_freeState;
using ::XXH32_hashFromCanonical;
using ::XXH32_hash_t;
using ::XXH32_reset;
using ::XXH32_state_s;
using ::XXH32_state_t;
using ::XXH32_update;
using ::XXH3_128bits;
using ::XXH3_128bits_digest;
using ::XXH3_128bits_reset;
using ::XXH3_128bits_reset_withSecret;
using ::XXH3_128bits_reset_withSeed;
using ::XXH3_128bits_update;
using ::XXH3_128bits_withSecret;
using ::XXH3_128bits_withSeed;
using ::XXH3_64bits;
using ::XXH3_64bits_digest;
using ::XXH3_64bits_reset;
using ::XXH3_64bits_reset_withSecret;
using ::XXH3_64bits_reset_withSeed;
using ::XXH3_64bits_update;
using ::XXH3_64bits_withSecret;
using ::XXH3_64bits_withSeed;
using ::XXH3_copyState;
using ::XXH3_createState;
using ::XXH3_freeState;
using ::XXH3_state_s;
using ::XXH3_state_t;
using ::XXH64;
using ::XXH64_canonicalFromHash;
using ::XXH64_canonical_t;
using ::XXH64_copyState;
using ::XXH64_createState;
using ::XXH64_digest;
using ::XXH64_freeState;
using ::XXH64_hashFromCanonical;
using ::XXH64_hash_t;
using ::XXH64_reset;
using ::XXH64_state_s;
using ::XXH64_state_t;
using ::XXH64_update;
using ::XXH_ERROR;
using ::XXH_OK;
using ::XXH_errorcode;
using ::XXH_versionNumber;
}
