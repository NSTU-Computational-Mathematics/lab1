#include <cmath>
#include <functional>
#include <iostream>

#include "BaseMethod.hpp"
#include "IterationMethod.hpp"
#include "NewtonMethod.hpp"
#include "SecantMethod.hpp"

template <float_like T = float>
T function(T x) {
  return -1 * pow(x, 2) + 7 * x - 4 * log(x) - 7;
}
template <float_like T = float>
T derivative(T x) {
  return -2 * x + 7 - 4 / x;
}

template <float_like T = float>
void PrintAnswers(T* answers, T* result, int count) {
  for (int i = 0; i < count; i++) {
    std::cout << "#" << i << " Answer = " << result[i] << '\n';
    if (answers != NULL) {
      std::cout << "#" << i << " Expected = " << answers[i] << '\n'
                << "Difference = " << result[i] - answers[i] << '\n';
    }
  }
}

template <float_like T = float>
void NewtonTest(T* l_bounds, int l_bounds_count, std::function<T(T)> function,
                std::function<T(T)> derivative, T* answers = NULL) {
  auto newton = NewtonMethod<T>(function, derivative);
  auto result = newton.Solution(l_bounds, l_bounds_count);
  PrintAnswers(answers, result, l_bounds_count);
}

int main() {
  std::function<float(float)> fun = function<float>;
  std::function<float(float)> der = derivative<float>;

  float answers[] = {0.2766, 1.7925, 3.6841};
  float bounds[] = {0.1, 1, 1, 2, 3, 4};
  float l_bounds[] = {0.1, 1, 3};
  NewtonTest(l_bounds, 3, fun, der, answers);
  return 0;
}
