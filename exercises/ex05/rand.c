/*  Implementations of several methods for generating random floating-point.

    Copyright 2016 Allen B. Downey
    License: MIT License https://opensource.org/licenses/MIT
*/

#include <stdlib.h>

// generate a random float using the algorithm described
// at http://allendowney.com/research/rand
float my_random_float()
{
  int x, exp, mant;
  float f;

  // this union is for assembling the float.
  union {
    float f;
    int i;
  } b;

  // generate 31 random bits (assuming that RAND_MAX is 2^31 - 1
  x = random();

  // use bit-scan-forward to find the first set bit and
  // compute the exponent
  asm ("bsfl %1, %0"
       :"=r"(exp)
       :"r"(x)
      );
  exp = 126 - exp;

  // use the other 23 bits for the mantissa (for small numbers
  // this means we are re-using some bits)
  mant = x >> 8;
  b.i = (exp << 23) | mant;

  return b.f;
}

// alternative implementation of my algorithm that doesn't use
// embedded assembly
float my_random_float2()
{
  int x;
  int mant;
  int exp = 126;
  int mask = 1;

  union {
    float f;
    int i;
  } b;

  // generate random bits until we see the first set bit
  while (1) {
    x = random();
    if (x == 0) {
      exp -= 31;
    } else {
      break;
    }
  }

  // find the location of the first set bit and compute the exponent
  while (x & mask) {
    mask <<= 1;
    exp--;
  }

  // use the remaining bit as the mantissa
  mant = x >> 8;
  b.i = (exp << 23) | mant;

  return b.f;
}

// compute a random double using my algorithm
double my_random_double()
{
  // TODO: fill this in
}

// return a constant (this is a dummy function for time trials)
float dummy()
{
  float f = 0.5;
  return f;
}

// generate a random integer and convert to float (dummy function)
float dummy2()
{
  int x;
  float f;

  x = random();
  f = (float) x;

  return f;
}

// generate a random float using the standard algorithm
float random_float()
{
  int x;
  float f;

  x = random();
  f = (float) x / (float) RAND_MAX;

  return f;
}


// generate a random double using the standard algorithm
float random_double()
{
  int x;
  double f;

  x = random();
  f = (double) x / (double) RAND_MAX;

  return f;
}


