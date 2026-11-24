/*
* https://pdebuyl.be/blog/2016/threefry-rng.html
* https://en.wikipedia.org/wiki/Counter-based_random_number_generator
* This algrithm uses a weaker version of the Threefish encription algorithm.
* It's slow, but the quality should be high.
* 
* results:
* ========= Summary results of SmallCrush =========
* 
*  Version:          TestU01 1.2.3
*  Generator:        threefry
*  Number of statistics:  15
*  Total CPU time:   00:01:09.82
* 
*  All tests were passed
*/

#include <stdint.h>
#include "unif01.h"
#include "bbattery.h"

#define MASK (-1ULL)
#define NW_THREEFRY 2
#define C240 0x1BD11BDAA9FC1A22
#define N_ROUNDS_THREEFRY 20

static const unsigned R_THREEFRY[] = {16, 42, 12, 31, 16, 32, 24, 21};

typedef struct {
    uint64_t v[2];
} pair;

typedef struct {
    uint64_t v[3];
} triple;

uint64_t rotl_64(uint64_t x, unsigned d)
{
    return ((x << d) | (x >> (64-d))) & MASK;
}

pair mix(pair x, unsigned R)
{
    pair y;
    y.v[0] = (x.v[0] + x.v[1]) & MASK;
    y.v[1] = rotl_64(x.v[1], R) ^ y.v[0];
    return y;
}

pair key_schedule_threefry(triple K, unsigned s)
{
    pair r;
    r.v[0] = K.v[(s)%(NW_THREEFRY+1)] & MASK;
    r.v[1] = (K.v[(s+1)%(NW_THREEFRY+1)] + s) & MASK;
    return r;
}

pair threefry(pair p, pair K)
{
    triple K3;
    K3.v[0] = K.v[0];
    K3.v[1] = K.v[1];
    K3.v[2] = C240 ^ K.v[0] ^ K.v[1];
    pair v = p;
    pair ksi;
    for (int r = 0; r < N_ROUNDS_THREEFRY; r++) {
        pair e;
        if (0 == r%4) {
            ksi = key_schedule_threefry(K3, r/4);
            e.v[0] = (v.v[0]+ksi.v[0]) & MASK;
            e.v[1] = (v.v[1]+ksi.v[1]) & MASK;
        } else {
            e = v;
        }
        v = mix(e, R_THREEFRY[r%8]);
    }
    ksi = key_schedule_threefry(K3, N_ROUNDS_THREEFRY/4);
    v.v[0] = (v.v[0] + ksi.v[0]) & MASK;
    v.v[1] = (v.v[1] + ksi.v[1]) & MASK;

    return v;
}


unsigned random(void)
{
    static int i = 0;
    pair k = { 0, 0x1234 };
    pair p = { i++, 0 };
    pair r = threefry(p, k);
    return r.v[0];   
}

unsigned wrapper(void)
{
    return random();
}

int main(void)
{
    unif01_Gen *gen;

    gen = unif01_CreateExternGenBits("threefry", wrapper);
    bbattery_SmallCrush(gen);
    unif01_DeleteExternGenBits(gen);
    return 0;
}