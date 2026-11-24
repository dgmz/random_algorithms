/*
https://en.wikipedia.org/wiki/Well_equidistributed_long-period_linear
Better than a Marsene Twister, but slower and requires big state.
https://lomont.org/papers/2008/Lomont_PRNG_2008.pdf

result:
========= Summary results of SmallCrush =========

 Version:          TestU01 1.2.3
 Generator:        xorshift
 Number of statistics:  15
 Total CPU time:   00:00:07.19

 All tests were passed
 
*/

#include "unif01.h"
#include "bbattery.h"

/* initialize state to random bits */
static unsigned long state[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
/* init should also reset this to 0 */
static unsigned int index = 0;
/* return 32 bit random number */
unsigned long WELLRNG512(void)
{
    unsigned long a, b, c, d;
    a = state[index];
    c = state[(index+13)&15];
    b = a^c^(a<<16)^(c<<15);
    c = state[(index+9)&15];
    c ^= (c>>11);
    a = state[index] = b^c;
    d = a^((a<<5)&0xDA442D24UL);
    index = (index + 15)&15;
    a = state[index];
    state[index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
    return state[index];
}

unsigned wrapper(void)
{
    return WELLRNG512();
}

int main(void)
{
    unif01_Gen *gen;

    gen = unif01_CreateExternGenBits("xorshift", wrapper);
    bbattery_SmallCrush(gen);
    unif01_DeleteExternGenBits(gen);
    return 0;
}
