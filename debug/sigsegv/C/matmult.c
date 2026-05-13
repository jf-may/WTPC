/* 
 * This source code was implemented as example for a debugging session
 * of the Workshop on Advanced Techniques for Scientific Programming
 * and Management of Open Source Software Packages.  The code
 * impements an inefficient version of a matrix multiplication such as
 * C = A * AT.  Where A, AT and C are square matrix of dimension SIZE
 * x SIZE.
 */ 


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __SMALL
#define SIZE 100
#else 
#define SIZE 2500
#endif

void mat_Tmat_mul( float * A, float * C ){

  int i, j, k;

  // temp is allocated on the stack.
  // For SIZE = 2500 this requires roughly: 2500 * 2500 * 4 bytes ~= 25 MB.
  // This exceeds the default stack size limit on many Linux systems, causing
  // a SIGSEGV (stack overflow).
  // Temporary workaround: ulimit -s unlimited
  // Proper fix: allocate temp dynamically with malloc/free.
  float temp[SIZE][SIZE];

  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      temp[j][i] = A[(i * SIZE) + j];

  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      for (k = 0; k < SIZE; k++)
        C[(i * SIZE) + j] += A[(i * SIZE ) + k] * temp[k][j];
  
}

int main(int argc, char * argv[]){
  
  int i, j;
  float *A, *C;
  
  A = (float *) malloc(SIZE * SIZE * sizeof(float));
  C = (float *) malloc(SIZE * SIZE * sizeof(float));

  // malloc return values are not checked.
  // If allocation fails, A or C become NULL and later accesses will cause
  // undefined behavior or segmentation faults.
  // Fix: verify A != NULL and C != NULL before use.
  // TODO: Add this error to every malloc instance prior

  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      // Division by zero when j == 0 produces inf, -inf or nan instead of
      // crashing. Fix: handle j == 0 explicitly.
      A[(i * SIZE) + j] = ((float) i) / j;
    }
  }

  memset(C, 0, SIZE * SIZE * sizeof(float));
  
  mat_Tmat_mul(A, C);
  
  free(A);
  free(C);

  return 0;
}
  
