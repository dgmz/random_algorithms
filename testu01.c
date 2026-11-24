/* 
Check for the TestU01 library. Try with the default libc rand() function.
Surprisingly, on MacOS it passes all SmallCrunch tests if we extend the 
output to 32 bits.
*/


#include <stdlib.h>

#include "unif01.h"
#include "bbattery.h"

#define TEST_BITS 1

#ifdef TEST_BITS

unsigned int wrapper(void)
{
    unsigned u1 = rand();
    unsigned u2 = rand();
    return (u1 << 1) ^ u2; // RAND_MAX is 2^31-1 in my system, but 32 bits are needed
}
#else 
double wrapper(void)
{
    return (double) rand() / ((double) RAND_MAX + 1.0); 
}
#endif

int main(void)
{
    unif01_Gen *gen;

#ifdef TEST_BITS
    gen = unif01_CreateExternGenBits(
#else
    gen = unif01_CreateExternGen01(
#endif
        "libc",
        wrapper
    );

    bbattery_SmallCrush(gen);
    //bbattery_Crush(gen);
    //bbattery_BigCrush(gen);

#ifdef TEST_BITS
    unif01_DeleteExternGenBits(gen);
#else
    unif01_DeleteExternGen01(gen);
#endif
    return 0;
}