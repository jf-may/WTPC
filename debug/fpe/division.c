#include <stdlib.h>
#include <stdio.h>
// If compiling with -DTRAPFPE, then this header file is included.
// Note: You also need to add the path to the folder using -Ifpe_x87_sse
//       and link libm using -lm
#ifdef TRAPFPE
#include "fpe_x87_sse.h"
#endif

int main(int argc, char *argv[])
{
  float a, b, c;

// If compiling with -DTRAPFPE, then this function is called. It enables
// exception errors for divbyzero, overflow and invalid operations.
#ifdef TRAPFPE
  set_fpe_x87_sse();
#endif

  printf("Division\n");
  printf("Insert a\n");
  scanf("%f",&a);
  printf("Insert b\n");
  scanf("%f",&b);

  // If dividing by zero, the program prints inf or -inf instead of failing.
  // Dividing zero by zero instead gives nan.
  // If you add -DTRAPFPE, then the error generates a SIGFPE signal and
  // terminates the program.
  printf("Calculating a/b...");
  c = a / b;
  printf("Done!\n");

  printf("c = a/b = %f\n", c);
  return(EXIT_SUCCESS);
}
