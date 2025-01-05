#include "math_utils.h"
#include <iostream>

int main() {
  int a = 5, b = 3;

  std::cout << "Addition: " << a << " + " << b << " = " << add(a, b)
            << std::endl;
  std::cout << "Subtraction: " << a << " - " << b << " = " << subtract(a, b)
            << std::endl;

  return 0;
}