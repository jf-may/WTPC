#include <stdlib.h>
#include <stdio.h>

#define DIM 10000000

void mysub(float **a, int dim)
{
  int j;
  
  (*a) = (float *)malloc(sizeof(float)*dim);
  
  for(j=0; j<dim; j++)
    {
      (*a)[j] = 7.;
    }
  
}

int main(int argc, char *argv[])
{
  float *a;
  int i;
  int mydim = DIM;
  int last;

  printf("Insert last \n");
  scanf("%d",&last);
  for(i=0; i<last; i++)
    {
      // Each iteration overwrites the previous pointer stored in a.
      // The previously allocated block becomes unreachable, producing a
      // memory leak. Fix: call free(a) before assigning a new allocation.
      mysub(&a, mydim);
    }

  printf("a = %f \n", a[0]);

  // Final allocation is also never freed.
  // Fix: add free(a) before exiting.
  return(EXIT_SUCCESS);
}
