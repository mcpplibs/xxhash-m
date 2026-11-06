// Every function that mcpplibs.mwrap.xxhash exports, by address: the program links only
// where compat.xxhash defines each one. Written by tools/generate.py.
import std;
import mcpplibs.mwrap.xxhash;

int main()
{
    // volatile: an optimiser may not drop a reference, so each one reaches the link.
    const void* volatile functions[] = {
        reinterpret_cast<const void*>(&XXH128_canonicalFromHash),
        reinterpret_cast<const void*>(&XXH128_cmp),
        reinterpret_cast<const void*>(&XXH128_hashFromCanonical),
        reinterpret_cast<const void*>(&XXH128_isEqual),
        reinterpret_cast<const void*>(&XXH32),
        reinterpret_cast<const void*>(&XXH32_canonicalFromHash),
        reinterpret_cast<const void*>(&XXH32_copyState),
        reinterpret_cast<const void*>(&XXH32_createState),
        reinterpret_cast<const void*>(&XXH32_digest),
        reinterpret_cast<const void*>(&XXH32_freeState),
        reinterpret_cast<const void*>(&XXH32_hashFromCanonical),
        reinterpret_cast<const void*>(&XXH32_reset),
        reinterpret_cast<const void*>(&XXH32_update),
        reinterpret_cast<const void*>(&XXH3_128bits),
        reinterpret_cast<const void*>(&XXH3_128bits_digest),
        reinterpret_cast<const void*>(&XXH3_128bits_reset),
        reinterpret_cast<const void*>(&XXH3_128bits_reset_withSecret),
        reinterpret_cast<const void*>(&XXH3_128bits_reset_withSeed),
        reinterpret_cast<const void*>(&XXH3_128bits_update),
        reinterpret_cast<const void*>(&XXH3_128bits_withSecret),
        reinterpret_cast<const void*>(&XXH3_128bits_withSeed),
        reinterpret_cast<const void*>(&XXH3_64bits),
        reinterpret_cast<const void*>(&XXH3_64bits_digest),
        reinterpret_cast<const void*>(&XXH3_64bits_reset),
        reinterpret_cast<const void*>(&XXH3_64bits_reset_withSecret),
        reinterpret_cast<const void*>(&XXH3_64bits_reset_withSeed),
        reinterpret_cast<const void*>(&XXH3_64bits_update),
        reinterpret_cast<const void*>(&XXH3_64bits_withSecret),
        reinterpret_cast<const void*>(&XXH3_64bits_withSeed),
        reinterpret_cast<const void*>(&XXH3_copyState),
        reinterpret_cast<const void*>(&XXH3_createState),
        reinterpret_cast<const void*>(&XXH3_freeState),
        reinterpret_cast<const void*>(&XXH64),
        reinterpret_cast<const void*>(&XXH64_canonicalFromHash),
        reinterpret_cast<const void*>(&XXH64_copyState),
        reinterpret_cast<const void*>(&XXH64_createState),
        reinterpret_cast<const void*>(&XXH64_digest),
        reinterpret_cast<const void*>(&XXH64_freeState),
        reinterpret_cast<const void*>(&XXH64_hashFromCanonical),
        reinterpret_cast<const void*>(&XXH64_reset),
        reinterpret_cast<const void*>(&XXH64_update),
        reinterpret_cast<const void*>(&XXH_versionNumber),
    };
    int missing = 0;
    for (const void* f : functions) missing += f == nullptr;
    std::println("42 functions linked, {} null", missing);
    return missing != 0;
}
