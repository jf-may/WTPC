      SUBROUTINE mat_Tmat_mul( A , C, SIZE )
   
      INTEGER SIZE
      REAL*4 A( SIZE, SIZE), C( SIZE, SIZE)
      
      ! temp is allocated on the stack. For large SIZE values this may exceed
      ! the stack limit and cause a segmentation fault.
      ! Running:
      ! ulimit -s unlimited
      ! increases the allowed stack size and may hide the problem, but does not
      ! actually fix it.
      ! Proper fix:
      ! allocate temp dynamically using ALLOCATE/DEALLOCATE.
      REAL*4 temp( SIZE, SIZE)   
      INTEGER i, j, k

      DO i = 1, SIZE 
         DO j = 1, SIZE 
            temp( j, i ) = A( i, j )
         END DO
      END DO
   
      DO i = 1, SIZE 
        DO j = 1, SIZE 
           DO k = 1, SIZE

              ! If SIZE is corrupted because the caller passed the wrong number
              ! of arguments, these accesses may go out of bounds and crash.
              C( i, j ) = C( i, j ) + A( i, k ) * temp( k, j )
           END DO
        END DO
      END DO

      write(*,*) "finished"
    
      END SUBROUTINE mat_Tmat_mul
