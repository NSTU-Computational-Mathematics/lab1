#include <cmath>
#include <functional>
#include <iostream>

#include "BaseMethod.hpp"
#include "IterationMethod.hpp"
#include "NewtonMethod.hpp"
#include "SecantMethod.hpp"

#define EPSILON 1e-4

template <float_like T = float>
T function(T x) {
  return -1 * x * x + 7 * x - 4 * log(x) - 7;
  // return pow(2, x) - 5 * x * x + 10;
}
template <float_like T = float>
T derivative(T x) {
  return -2 * x + 7 - 4 / x;
  // return log(2) * pow(2, x) - 10 * x;
}

template <float_like T = float>
void PrintAnswers(char* title, T* answers, T* result, int count) {
  printf("\n\x1b[32m%s\x1b[0m\n", title);

  for (int i = 0; i < count; i++) {
    printf("\x1b[33m#%d\x1b[0m\n", i + 1);
    std::cout << "Ans = " << result[i];
    if (answers != NULL) {
      std::cout << "\nExp = " << answers[i] << '\n';
      if (fabsf(result[i] - answers[i]) > EPSILON)
        std::cout << "\x1b[31mDif = \x1b[0m" << result[i] - answers[i] << '\n';
    } else {
      std::cout << '\n';
    }
  }
}

template <float_like T = float>
void NewtonTest(T* bounds, int bounds_count, std::function<T(T)> function,
                std::function<T(T)> derivative, T* answers = NULL) {
  auto method = NewtonMethod<T>(function, derivative);
  auto result = method.Solution(bounds, bounds_count);
  if (result == NULL) throw std::runtime_error("Null back");
  char title[] = "NEWTON METHOD TEST";
  PrintAnswers(title, answers, result, bounds_count / 2);
  free(result);
}

template <float_like T = float>
void IterationTest(T* bounds, int bounds_count, std::function<T(T)> function,
                   std::function<T(T)> derivative, T* answers = NULL) {
  auto method = IterationMethod<T>(function, derivative);
  T* result = method.Solution(bounds, bounds_count);
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
  float bounds[] = {0.001, 1, 1, 2, 3, 4};

  // float answers[] = {-1.4404, 1.61657, 8.43279};
  // float bounds[] = {-2, -1, 1, 2, 8, 9};

  NewtonTest(bounds, 6, fun, der, answers);
  IterationTest(bounds, 6, fun, der, answers);
  SecantTest(bounds, 6, fun, der, answers);
  return 0;
}
