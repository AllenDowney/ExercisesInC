#include <stdio.h>

int main() {
  int x = 5; // corresponds to the line 17 when added to print statement
  // x's value not found in optimized compiler code when x is left unused
  int y = x + 1; // Compiler optimization does not store variables address
  printf("Hello, World!, %d\n", y);
  return 0;
}

/* I observed a few things that optimization does.  First, it replaces functions
 * with more helpful functions, such as printf and __printf_chk.  The difference
 * between these two functions is that __printf_chk checks for stack overflow
 * first.  Second, it turns variables into constant values, if possible, such as
 * using the number 6, instead of storing the address of x and y and then
 * performing calculations. Third, it rids unused variables
 */
