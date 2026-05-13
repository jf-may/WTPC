/* 
 * This source code was implemented as example for a debugging session of the 
 * Workshop on Advanced Techniques for Scientific Programming and Management of Open Source Software Packages. 
 * The code impements an inefficient version of a matrix multiplication such as C = A * AT.
 * Where A, AT and C are square matrix of dimension SIZE x SIZE.
 * A is the input matrix while C is te output matrix. With in the function mat_Tmat_mul a temporary AT matrix is defined.
 * The program contains an infite loop calling the function mat_Tmat_mul
 * Run the program compiling the proposed version on your workstation as reported:
 *
 *     1) gcc source1.c -O3 -g; ./a.out
 *
 * Open an other shell and check the memory consumption. 
 * Run the debug using valgrind (possibly at reduced SIZE). 
 * Please, use the valgrind on-line manual or publicly available documentation on web for details on valgrind sintax.
 *
 */ 


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 1000

void mat_Tmat_mul( float * A, float * C ){

  int i, j, k;
  float * temp;

  // temp is allocated every time the function is called, but it is never freed.
  // Since this function is called inside an infinite loop, memory usage grows
  // indefinitely.
  // Fix: add free(temp) before returning from the function.
  // Valgrind detects this as memory blocks that are "definitely lost"
  temp = (float *) malloc( SIZE * SIZE * sizeof(float) );

  for( i = 0; i < SIZE; i++ )
    for( j = 0; j < SIZE; j++ )
      temp[ ( j * SIZE) + i ] = A[ ( i * SIZE ) + j ];

  for( i = 0; i < SIZE; i++ )
    for( j = 0; j < SIZE; j++ )
      for( k = 0; k < SIZE; k++ )
	C[ ( i * SIZE ) + j ] += A[ ( i * SIZE ) + k ] * temp[ ( k * SIZE ) + j ] ;
  
}

int main( int argc, char * argv[] ){
  
  int i, j;
  float * A, * C;
  
  A = (float *) malloc( SIZE * SIZE * sizeof(float) );
  C = (float *) malloc( SIZE * SIZE * sizeof(float) );
  
  // When j == 0 this performs a division by zero, which generates inf or
  // nan values. Fix: handle the j == 0 case.
  for( i = 0; i < SIZE; i++ ){
    for( j = 0; j < SIZE; j++ ){
      A[ ( i * SIZE ) + j ] = ( (float) i ) / j;
    }
  }
   
  memset( C, 0, SIZE * SIZE * sizeof(float) );

  // Infinite loop continuously calling a function that leaks memory.
  for(;;) mat_Tmat_mul( A, C );
  
  free( A );
  free( C );
  
  return 0;
}
  
