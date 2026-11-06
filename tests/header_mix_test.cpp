// The header and the module in one translation unit: the same entities, so a
// state created through one spelling is freed through the other.
#include <xxhash.h>
import std;
import mcpplibs.mwrap.xxhash;

int main()
{
    XXH32_state_t* s = ::XXH32_createState();                     // the header's declaration
    const bool reset = XXH32_reset(s, 0) == XXH_OK;               // the module's
    const bool freed = XXH32_freeState(s) == XXH_OK;
    const bool same = &::XXH64 == &XXH64 && XXH_versionNumber() == XXH_VERSION_NUMBER;
    std::println("{}", reset && freed && same ? "header and module agree" : "FAIL");
    return reset && freed && same ? 0 : 1;
}
