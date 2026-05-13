#include <stdio.h>

int add_array(int *a, int *b, int n){
  int sum = 0;
  int i = 0;
  // Same out of bounds access as add_array_static and add_array_dynamic
  for (i = 0; i <= n + 1; i++) {
    // abs is an stdlib function, and it is not explicitely declared.
    sum += abs(a[i]);
    sum += abs(b[i]);
  };
  return sum;
}

int main(int argc, char **argv) {
  int *a, *b; // Declared but never initialized.
  int n = 3;
  int i, sum;
  // Loop tries to access invalid memory, segmentation fault.
  for (i = 0; i < n; i++) {
    a[i] = i;
    b[i] = i;
  }
  sum = add_array(a, b, 3);
  printf("The addition is %d\n", sum);
  return 0;
}
