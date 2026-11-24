/*
 * Java random number generator.
 * Basically the same as UNIX, with different constant choices.
 * Very simple congruential random number generator with prime modulus.
 * 
 * Results are not very good:
 * ========= Summary results of SmallCrush =========
 * 
 *  Version:          TestU01 1.2.3
 *  Generator:        java
 *  Number of statistics:  15
 *  Total CPU time:   00:00:05.24
 *  The following tests gave p-values outside [0.001, 0.9990]:
 *  (eps  means a value < 1.0e-300):
 *  (eps1 means a value < 1.0e-15):
 * 
 *        Test                          p-value
 *  ----------------------------------------------
 *   1  BirthdaySpacings                 eps  
 *   2  Collision                      1 - eps1
 *   3  Gap                              eps  
 *   4  SimpPoker                        eps  
 *   5  CouponCollector                  eps  
 *   7  WeightDistrib                    eps  
 *   8  MatrixRank                       eps  
 *   9  HammingIndep                     eps  
 *  10  RandomWalk1 H                   1.4e-7
 *  10  RandomWalk1 M                    eps  
 *  ----------------------------------------------
 *  All other tests were passed

 */

#include "unif01.h"
#include "bbattery.h"

unsigned long int next = 1;

long int rand(void)
{
    next = (next * 25214903917 + 11) % 281474976710656; // 48-bit
    return next;
}

unsigned wrapper(void)
{
    return (unsigned) rand(); // take upper 32 bits
}

int main(void)
{
    unif01_Gen *gen;

    gen = unif01_CreateExternGenBits("java", wrapper);
    bbattery_SmallCrush(gen);
    unif01_DeleteExternGenBits(gen);
    return 0;
}