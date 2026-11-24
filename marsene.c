/*
* Implementation of MT19937.
* https://en.wikipedia.org/wiki/Mersenne_Twister
* A slightly simpler version of the wikipedia code.
* 
* result:
* ========= Summary results of SmallCrush =========
* 
*  Version:          TestU01 1.2.3
*  Generator:        marsene
*  Number of statistics:  15
*  Total CPU time:   00:00:09.98
* 
*  All tests were passed
*/


#include "unif01.h"
#include "bbattery.h"

#define W_WORDSIZE 32
#define N_RECURRENCE 624
#define M_MIDDLE 397
#define R_SEPARATION 31 
#define A_TWIST_MATRIX 0x9908B0DF
#define B_MASK 0x9D2C5680
#define C_MASK 0xEFC60000
#define S_SHIFT 7
#define T_SHIFT 15
#define U_SHIFT 11
#define D_MASK 0xFFFFFFFF
#define L_SHIFT 18
#define U_MASK (0xFFFFFFFF << R_SEPARATION)
#define L_MASK (0xFFFFFFFF >> (W_WORDSIZE - R_SEPARATION))
#define F 1812433253UL

unsigned int state[N_RECURRENCE] = { 0 };
int state_idx = 0;

void init_state(unsigned int seed)
{
    state_idx = 0;
    state[0] = seed;
    for (int i = 1; i < N_RECURRENCE; i++) {
        seed = F * (seed ^(seed >> (W_WORDSIZE - 2))) + i;
        state[i] = seed;
    }
}

unsigned int twister(void) 
{
    int j = (state_idx + 1) % N_RECURRENCE;
    unsigned int x = (state[state_idx] & U_MASK) | (state[j] & L_MASK);
    unsigned int xa = x >> 1;
    if (x & 1) {
        xa ^= A_TWIST_MATRIX;
    }
    j = (state_idx + M_MIDDLE) % N_RECURRENCE;
    x = state[j] ^ xa;
    state[state_idx] = x;
    state_idx = (state_idx + 1) % N_RECURRENCE;
    unsigned int y = x ^ (x >> U_SHIFT);
    y = y ^ ((y << S_SHIFT) & B_MASK);
    y = y ^ ((y << T_SHIFT) & C_MASK);
    y = y ^ (y >> L_SHIFT);
    return y;
}

unsigned wrapper(void)
{
    return twister();
}

int main(void)
{
    unif01_Gen *gen;

    init_state(0);
    gen = unif01_CreateExternGenBits("marsene", wrapper);
    bbattery_SmallCrush(gen);
    unif01_DeleteExternGenBits(gen);
    return 0;
}