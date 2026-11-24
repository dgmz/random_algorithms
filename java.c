/*
 * Java 1.1 random number generator (java.util.Random.next()).
 * https://developer.classpath.org/doc/java/util/Random-source.html
 * Basically the same as UNIX, with different constant choices.
 * Very simple congruential random number generator with prime modulus.
 * 
 * Results are not very good:
 * ========= Summary results of SmallCrush =========
 * 
 *  Version:          TestU01 1.2.3
 *  Generator:        java
 *  Number of statistics:  15
 *  Total CPU time:   00:00:05.87
 *  The following tests gave p-values outside [0.001, 0.9990]:
 *  (eps  means a value < 1.0e-300):
 *  (eps1 means a value < 1.0e-15):
 * 
 *        Test                          p-value
 *  ----------------------------------------------
 *   1  BirthdaySpacings                 eps  
 *   3  Gap                            1 -  4.4e-6
 *   4  SimpPoker                       6.8e-9
 *   5  CouponCollector                  eps  
 *   7  WeightDistrib                    eps  
 *  ----------------------------------------------
 *  All other tests were passed
 */

#include "unif01.h"
#include "bbattery.h"

unsigned long int seed = 1;

long int rand(int bits)
{
    seed = (seed * 0x5DEECE66DL +0xBL) & ((1L << 48) - 1); // 48-bit
    return seed >> (48 - bits);
}

unsigned wrapper(void)
{
    return (unsigned) rand(32); // take upper 32 bits
}

int main(void)
{
    unif01_Gen *gen;

    gen = unif01_CreateExternGenBits("java", wrapper);
    bbattery_SmallCrush(gen);
    unif01_DeleteExternGenBits(gen);
    return 0;
}