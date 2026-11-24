/*
* https://en.wikipedia.org/wiki/Xorshift
*/

#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t a;
} XorShift32State;

// The state must be initialized to non-zero
uint32_t xorshift32(XorShift32State* state) {
	// Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs"
	uint32_t x = state->a;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return state->a = x;
}

typedef struct {
    uint64_t a;
} XorShift64State;

// The state must be initialized to non-zero
uint64_t xorshift64(XorShift64State* state) {
	uint64_t x = state->a;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return state->a = x;
}

// XorShift128State can alternatively be defined as a pair
// of uint64_t or a uint128_t where supported
typedef struct {
    uint32_t x[4];
} XorShift128State;

// The state must be initialized to non-zero
uint32_t xorshift128(XorShift128State* state) {
	// Algorithm "xor128" from p. 5 of Marsaglia, "Xorshift RNGs"
	uint32_t t = state->x[3];
    
    uint32_t s = state->x[0]; // Perform a contrived 32-bit shift.
	state->x[3] = state->x[2];
	state->x[2] = state->x[1];
	state->x[1] = s;

	t ^= t << 11;
	t ^= t >> 8;
	return state->x[0] = t ^ s ^ (s >> 19);
}

int main(void)
{
    XorShift32State state;
    int count = 100;
    state.a = 1;
    do {
        unsigned v = xorshift32(&state);
        printf("%u\n", v);
    }while (--count);
    return 0;
}
