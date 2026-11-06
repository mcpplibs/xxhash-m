// The module's functions over compat.xxhash: the four hashes of the empty
// input as upstream publishes them, streaming equal to one call, a seed and a
// secret, the canonical (big-endian) forms, the 128-bit comparisons, and the
// version against its macros.
import std;
import mcpplibs.mwrap.xxhash;

namespace m = mcpplibs::mwrap::xxhash::macros;

int main()
{
    int failures = 0;
    auto check = [&](bool ok, std::string_view what) {
        std::println("{} {}", ok ? "ok  " : "FAIL", what);
        failures += ok ? 0 : 1;
    };

    // The empty input (upstream's tests/sanity_test_vectors.h, first entries).
    check(XXH32(nullptr, 0, 0) == 0x02CC5D05u, "XXH32 of nothing");
    check(XXH64(nullptr, 0, 0) == 0xEF46DB3751D8E999ull, "XXH64 of nothing");
    check(XXH3_64bits(nullptr, 0) == 0x2D06800538D394C2ull, "XXH3_64bits of nothing");
    const XXH128_hash_t empty = XXH3_128bits(nullptr, 0);
    check(empty.low64 == 0x6001C324468D497Full && empty.high64 == 0x99AA06D3014798D8ull, "XXH3_128bits of nothing");

    std::string text;
    for (int i = 0; i < 1000; ++i) text += std::format("{} ", i * 7919);

    // Streaming in uneven pieces equals one call.
    XXH3_state_t* state = XXH3_createState();
    check(XXH3_64bits_reset_withSeed(state, 42) == XXH_OK, "XXH3_64bits_reset_withSeed");
    for (std::size_t at = 0; at < text.size(); at += 97)
        XXH3_64bits_update(state, text.data() + at, std::min<std::size_t>(97, text.size() - at));
    check(XXH3_64bits_digest(state) == XXH3_64bits_withSeed(text.data(), text.size(), 42), "XXH3-64 streamed");
    XXH3_freeState(state);
    XXH64_state_t* state64 = XXH64_createState();
    XXH64_reset(state64, 7);
    XXH64_update(state64, text.data(), 10);
    XXH64_state_t* copy = XXH64_createState();
    XXH64_copyState(copy, state64);
    XXH64_update(state64, text.data() + 10, text.size() - 10);
    XXH64_update(copy, text.data() + 10, text.size() - 10);
    check(XXH64_digest(state64) == XXH64(text.data(), text.size(), 7) && XXH64_digest(copy) == XXH64_digest(state64),
          "XXH64 streamed, and from a copied state");
    XXH64_freeState(state64);
    XXH64_freeState(copy);

    // A secret of the minimum size changes the hash.
    std::string secret(m::XXH3_SECRET_SIZE_MIN, '\0');
    for (std::size_t i = 0; i < secret.size(); ++i) secret[i] = static_cast<char>(i * 31 + 7);
    const auto keyed = XXH3_128bits_withSecret(text.data(), text.size(), secret.data(), secret.size());
    const auto plain = XXH3_128bits(text.data(), text.size());
    check(!XXH128_isEqual(keyed, plain) && XXH128_cmp(&keyed, &keyed) == 0, "XXH3-128 with a secret");

    // Canonical forms are big-endian and convert back.
    XXH64_canonical_t canonical;
    XXH64_canonicalFromHash(&canonical, 0x0102030405060708ull);
    check(canonical.digest[0] == 1 && canonical.digest[7] == 8
              && XXH64_hashFromCanonical(&canonical) == 0x0102030405060708ull, "XXH64 canonical form");
    XXH128_canonical_t canonical128;
    XXH128_canonicalFromHash(&canonical128, keyed);
    check(XXH128_isEqual(XXH128_hashFromCanonical(&canonical128), keyed), "XXH128 canonical form");

    check(XXH_versionNumber() == m::XXH_VERSION_NUMBER && m::XXH_VERSION_NUMBER == 803u, "the library is 0.8.3");
    std::println("{} failures", failures);
    return failures != 0;
}
