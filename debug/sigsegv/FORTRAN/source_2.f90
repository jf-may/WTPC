! 
! This source code was implemented as example for a debugging session of the 
! Workshop on Advanced Techniques for Scientific Programming and Management of Open Source Software Packages. 
! The code impements an inefficient version of a matrix multiplication such as C = A! AT.
! Where A, AT and C are square matrix of dimension SIZE x SIZE.
! A is the input matrix while C is te output matrix. With in the subroutine mat_Tmat_mul a temporary AT matrix is defined.
! Run the program compiling both version on your workstation as reported
!
!     1) gfortran -fpp source.f90 -o small.x -D__SMALL -O0 -g
!
!     2) gfortran -fpp source.f90 -o big.x -O0 -g
!
! The case number 2) is expected to crash with a "Segmentation fault" generating a core file. 
! Try to analize the core file using gdb to identify where the execution broke. 
! Print the content of local variable to understand the source of the error.
!
! The command to anylize core file is as follows:
!
! $gdb ./[EXE].x core.[PID]
!
! Please, use the gdb on-line manual or publicly available documentation on web for details on gdb sintax.
!

PROGRAM DEBUG

  IMPLICIT NONE

  INTEGER, PARAMETER :: SIZE = 1000

  INTEGER :: i, j
  REAL*4, ALLOCATABLE, DIMENSION ( :, : ) :: A, C

  ALLOCATE ( A( SIZE, SIZE ) )
  ALLOCATE ( C( SIZE, SIZE ) )

  DO j = 1, SIZE 
     DO i = 1, SIZE 
        A( i, j ) = REAL(i) / j
     END DO
  END DO

  C = 0.0

  ! mat_Tmat_mul expects:
  ! (A, C, SIZE)
  ! but SIZE is missing in this call.
  ! Because there is no explicit interface, the compiler cannot detect the
  ! error. The subroutine reads an invalid SIZE value from memory, which may
  ! cause out-of-bounds accesses or SIGSEGV.
  ! Fix:
  ! CALL mat_Tmat_mul( A, C, SIZE )
  CALL mat_Tmat_mul( A, C )

  DEALLOCATE( A );
  DEALLOCATE( C );

  STOP

END PROGRAM DEBUG
