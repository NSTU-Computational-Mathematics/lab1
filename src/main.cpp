#include <cmath>
#include <functional>
#include <iostream>

#include "BaseMethod.hpp"
#include "IterationMethod.hpp"
#include "NewtonMethod.hpp"
#include "SecantMethod.hpp"

#define EPSILON 1e-10

template <float_like T = float>
T function(T x) {
  return -1 * pow(x, 2) + 7 * x - 4 * log(x) - 7;
}
template <float_like T = float>
T derivative(T x) {
  return -2 * x + 7 - 4 / x;
}

template <float_like T = float>
void PrintAnswers(char* title, T* answers, T* result, int count) {
  // printf("\x1b[31%sx1b[0m\n", title);
  printf("\n\x1b[32m%s\x1b[0m\n", title);

  for (int i = 0; i < count; i++) {
    printf("\x1b[33m#%d\x1b[0m\n", i);
    std::cout << "Answer = " << result[i];
    // printf("Answer = ", )
    if (answers != NULL) {
      std::cout << " Expected = " << answers[i] << '\n';
      if (fabsf(result[i] - answers[i]) > EPSILON)
        std::cout << "\x1b[31mDifference = \x1b[0m" << result[i] - answers[i]
                  << '\n';
    } else {
      std::cout << '\n';
    }
  }
}

template <float_like T = float>
void NewtonTest(T* l_bounds, int l_bounds_count, std::function<T(T)> function,
                std::function<T(T)> derivative, T* answers = NULL) {
  auto method = NewtonMethod<T>(function, derivative);
  auto result = method.Solution(l_bounds, l_bounds_count);
  if (result == NULL) throw std::runtime_error("Null back");
  char title[] = "NEWTON METHOD TEST";
  PrintAnswers(title, answers, result, l_bounds_count);
  free(result);
}

template <float_like T = float>
void IterationTest(T* bounds, int bounds_count, std::function<T(T)> function,
                   std::function<T(T)> derivative, T* answers = NULL) {
  auto method = IterationMethod<T>(function, derivative);
  auto result = method.Solution(bounds, bounds_count);
  if (result == NULL) throw std::runtime_error("Null back");
  char title[] = "ITERATION METHOD TEST";

  PrintAnswers(title, answers, result, bounds_count / 2);
  free(result);
}

template <float_like T = float>
void SecantTest(T* bounds, int bounds_count, std::function<T(T)> function,
                std::function<T(T)> derivative, T* answers = NULL) {
  auto method = SecantMethod<T>(function, derivative);
  auto result = method.Solution(bounds, bounds_count);
  if (result == NULL) throw std::runtime_error("Null back");
  char title[] = "SECANT METHOD TEST";

  PrintAnswers(title, answers, result, bounds_count / 2);
  free(result);
}

int main() {
  std::function<float(float)> fun = function<float>;
  std::function<float(float)> der = derivative<float>;

  float answers[] = {0.2766, 1.7925, 3.6841};
  float bounds[] = {0.1, 1, 1, 2, 3, 4};
  float l_bounds[] = {0.1, 1, 3};
  NewtonTest(l_bounds, 3, fun, der, answers);
  IterationTest(bounds, 6, fun, der, answers);
  SecantTest(bounds, 6, fun, der, answers);
  return 0;
}
