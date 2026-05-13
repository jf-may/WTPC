#include <stdio.h>

int add_array(int *a, int *b, int n){
  int sum = 0;
  int i = 0;
  // Loop goes from 0 to 4 inclusive. That means it is accesing a[3], a[4],
  // b[3] and b[4] all of which are out of bounds.
  // Fix: i < n
  for (i = 0; i <= n + 1; i++) {
    // abs is an stdlib function, and it is not explicitely declared.
    sum += abs(a[i]);
    sum += abs(b[i]);
  };
  return sum;
}

int main(int argc, char **argv) {
  int a[3], b[3];
  int n = 3;
  int i, sum;
  for (i = 0; i < n; i++) {
    a[i] = i;
    b[i] = i;
  }
  sum = add_array(a, b, 3);
  printf("The addition is %d\n", sum);
  return 0;
}
