/*
 * Middle-squares method proposed by John von Neumann in 1947, and used by 
 * Stan Ulam for the Manhattan project.
 * 
 * It generates poor random numbers, and can easily fall in loops or degrade
 * to generate 0.
 * 
 * Not tested with TestU01, it's not worth it.
*/

#include <stdio.h>

int main(void)
{
    unsigned short seed = 12345; // at least 16-bit
    unsigned long v = seed; // at least 32-bit
    int count = 100;
    do {
        printf("%lu\n", v);
        v *= v; // square
        v = 0xFFFF & (v >> 8); // keep center bits
    } while(--count);

    return 0;
}