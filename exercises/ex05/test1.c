#include <stdio.h>
#include <stdlib.h>

#include "rand.h"

main (int argc, char *argv[])
{
  int i;
  double x;

  srandom (time (NULL));

  for (i=0; i<10000; i++) {
    x = random_float();
    printf ("%lf\n", x);
  }
}
