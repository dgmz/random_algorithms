/*
 * Kernighan & Ritchie random number generator.
 * As appears in section 2.7 of "The C Programming Language".
 * Very simple congruential random number generator with prime modulus.
 * RAND_MAX is 2^15-1 (15 random bits only).
 * 
 * The results:
 *  Total CPU time:   00:00:07.04
 *  The following tests gave p-values outside [0.001, 0.9990]:
 *  (eps  means a value < 1.0e-300):
 *  (eps1 means a value < 1.0e-15):
 * 
 *        Test                          p-value
 *  ----------------------------------------------
 *   1  BirthdaySpacings                 eps  
 *   2  Collision                        eps  
 *   4  SimpPoker                       6.4e-5
 *   5  CouponCollector                  eps  
 *   7  WeightDistrib                    eps  
 *  ----------------------------------------------
 *  All other tests were passed

*/

#include "unif01.h"
#include "bbattery.h"

unsigned long int next = 1;

int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

unsigned wrapper(void)
{
    unsigned u1 = rand();
    unsigned u2 = rand();
    unsigned u3 = rand();
    return (u1 << 17) ^ (u2 << 2) ^ u3; // 32 bits are needed
}

int main(void)
{
    unif01_Gen *gen;

    gen = unif01_CreateExternGenBits("unix", wrapper);
    bbattery_SmallCrush(gen);
    unif01_DeleteExternGenBits(gen);

    return 0;
}
