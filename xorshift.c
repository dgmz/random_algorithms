/*
* https://en.wikipedia.org/wiki/Xorshift
* Here we implement xorshiftr+.
* Very fast and passes all tests in TestU01 BigCrunch.
* 
* result:
* ========= Summary results of SmallCrush =========
* 
*  Version:          TestU01 1.2.3
*  Generator:        xorshift
*  Number of statistics:  15
*  Total CPU time:   00:00:06.17
* 
*  All tests were passed
*/

#include <stdint.h>
#include "unif01.h"
#include "bbattery.h"

// L'estat intern ocupa 64 bits en total (no pot ser tot zero)
uint64_t s[2] = { 123456789, 362436069 };

uint32_t xorshiftr_plus_32(void) {
    uint64_t x = s[0];
    uint64_t const y = s[1];
    s[0] = y;
    x ^= x << 23;
    x ^= x >> 17;
    x ^= y;
    s[1] = x + y;
    return x;
}

unsigned wrapper(void)
{
    return xorshiftr_plus_32();
}

int main(void)
{
    unif01_Gen *gen;

    gen = unif01_CreateExternGenBits("xorshift", wrapper);
    bbattery_SmallCrush(gen);
    unif01_DeleteExternGenBits(gen);
    return 0;
}
