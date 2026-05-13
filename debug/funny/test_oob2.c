#include <stdlib.h>
#include <stdio.h>

#define DIM 1039596


int main(int argc, char *argv[])
{
  float *a;
  int i;
  int mydim = DIM;
// If compiling with -DDEBUG, define a string called errmsg.
#ifdef DEBUG
  char *errmsg;
#endif


  a = (float *)malloc(sizeof(float)*mydim);
// If compiling with -DDEBUG, allocate memory for a string, just after the
// allocation for a, which when we have an out of bounds memory access later, it
// might access some of this memory.
#ifdef DEBUG
  errmsg = (char *)malloc(sizeof(char)*1024);
  sprintf(errmsg, "I'm HERE !!!! \n");
#endif

// If compiling with -DDEBUG, print the error msg. This doesn't actually do any
// signaling, it is just a hard coded "errmsg".
#ifdef DEBUG
  printf("%s", errmsg);
#endif

  for(i=0; i<mydim; i++)
    {
      // Out of bounds memory access. 1000 extra elements from the assigned
      // memory.
      a[i+1000] = a[i];
    }

  printf("a = %f \n", a[0]);

  free(a);

// If compiling with -DDEBUG, free the errmsg memory
#ifdef DEBUG
  free(errmsg);
#endif

  return(EXIT_SUCCESS);
}
