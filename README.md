# (pseudo-)Random Number Generators

This is a set of tests on pseudo-random number generation, using basic classical algorithms.

A good introduction: 

https://en.wikipedia.org/wiki/Pseudorandom_number_generator

Also, chapter 3, Volume 2 of Knuth.

To test the quality of the random numbers I used the TestU01 library (I only used the
SmallCrunch test set, the others take a lot of time to run).

Summary of tests:

-------------  --------------------------------
  Algorithm      Result   
-------------  --------------------------------
 von Newmann    historic value, very poor
 unix           poor
 java           poorer
 marsene        good
 well           good and faster
 xorshift       good and fastest
 threefry       (very?) good, but slow
-------------  --------------------------------
