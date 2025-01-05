#include "math_utils.h"
#include <stdio.h>

int main() {
  int a = 5, b = 3;

  printf("Addition: %d + %d = %d\n", a, b, add(a, b));
  printf("Subtraction: %d - %d = %d\n", a, b, subtract(a, b));

  return 0;
}