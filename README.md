# (pseudo-)Random Number Generators

This is a set of tests on pseudo-random number generation, using basic classical algorithms.

A good introduction: 

https://en.wikipedia.org/wiki/Pseudorandom_number_generator

Also, chapter 3, Volume 2 of Knuth.

To test the quality of the random numbers I used the TestU01 library (I only used the
SmallCrunch test set, the others take a lot of time to run).

Summary of tests:

| Algorithm  | Result                         |  
|------------|--------------------------------|
| vonnewmann | historic value, very poor      |
| unix       | poor                           |
| java       | poor                           |
| marsene    | good                           |
| well       | good and faster.               |   
| xorshift   | good and fastest               |
| threefry   | (very?) good, but slow.        |

## Setup

Before compiling it is necessary to download and install
TestU01 from here: https://simul.iro.umontreal.ca/testu01/tu01.html

Expand the compressed files to a folder, for instance `./TestU01-x.y.z/`.
You can chose to follow the instructions there in the `INSTALL` file,
or do this:

```
cd TestU01-x.y.z/
mkdir usr
./configure --prefix=$(pwd)/usr
make && make install
````

This will install to a subdirectory of the project (to ease cleanup).

After all this, **do not forget to update the paths in the `Makefile`**.
