#include <cmath>
#include <functional>
#include <iostream>

#include "BaseMethod.hpp"
#include "IterationMethod.hpp"
#include "NewtonMethod.hpp"

float function(float x) {
  // return -1 * (float)pow(x, 2) + 7 * x - 7;
  return -1 * pow(x, 2) + 7 * x - 4 * log(x) - 7;
}
float derivative(float x) {
  // return -2 * x + 7;
  return -2 * x + 7 - 4 / x;
}

int main() {
  std::function<float(float)> fun = function;
  std::function<float(float)> fun2 = derivative;
  // auto x = BaseMethod(fun, fun2);
  // auto y = NewtonMethod(fun, fun2);
  auto z = IterationMethod(fun, fun2);
  // std::cout << y.NewtonSolution(0.1) << std::endl;
  std::cout << z.IterationSolution(0.1, 1) << std::endl;
  std::cout << z.IterationSolution(1, 2) << std::endl;
  std::cout << z.IterationSolution(3, 4) << std::endl;

  // auto x = NewtonMethod(fun, fun2, 0.001);
  // auto x = B(1);
  return 0;
}

// float IterMethod(float x0, float eps) { return 1; }
