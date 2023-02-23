#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>

#include "BaseMethod.hpp"
#include "IterationMethod.hpp"
#include "NewtonMethod.hpp"
#include "SecantMethod.hpp"

#define EPSILON 1e-3

template <float_like T = float>
T function(T x) {
  return -1 * x * x + 7 * x - 4 * log(x) - 7;
}
template <float_like T = float>
T derivative(T x) {
  return -2 * x + 7 - 4 / x;
}

template <float_like T = float>
T function2(T x) {
  return 100 * x * x - 1000 * x - 6;
}
template <float_like T = float>
T derivative2(T x) {
  return 200 * x - 1000;
}

void PrintTitle(std::string title, std::ostream& os = std::cout) {
  os << "\n****" << title << "****" << '\n';
}

template <float_like T = float>
void PrintAnswers(T* answers, T* result, int count,
                  std::ostream& os = std::cout) {
  os << "Answers and Expected values\n";

  for (int i = 0; i < count; i++) {
    os << "#" << i + 1 << '\n';
    os << "Ans = " << result[i] << '\n';
    if (answers != NULL) {
      os << "Exp = " << answers[i] << '\n';
      if (fabsf(result[i] - answers[i]) > EPSILON) {
        os << "Dif = " << result[i] - answers[i] << '\n';
      }
      os << "Difference was more than epsilon: " << EPSILON << '\n';
    }
  }
}

template <float_like T = float>
void NewtonTest(T* bounds, int bounds_count, std::function<T(T)> function,
                std::function<T(T)> derivative, T* answers = NULL,
                bool printAll = false, std::ostream& os = std::cout) {
  PrintTitle("NEWTON METHOD TEST", os);

  auto method = NewtonMethod<T>(function, derivative);
  auto result = method.Solution(bounds, bounds_count, printAll, os);
  if (result == NULL) throw std::runtime_error("Null back");
  PrintAnswers(answers, result, bounds_count / 2, os);
  free(result);
}

template <float_like T = float>
void IterationTest(T* bounds, int bounds_count, std::function<T(T)> function,
                   std::function<T(T)> derivative, T* answers = NULL,
                   bool printAll = false, std::ostream& os = std::cout) {
  PrintTitle("ITERATION METHOD TEST", os);

  auto method = IterationMethod<T>(function, derivative, 0.01);
  auto result = method.Solution(bounds, bounds_count, printAll, os);
  if (result == NULL) throw std::runtime_error("Null back");

  PrintAnswers(answers, result, bounds_count / 2, os);
  free(result);
}

template <float_like T = float>
void SecantTest(T* bounds, int bounds_count, std::function<T(T)> function,
                std::function<T(T)> derivative, T* answers = NULL,
                bool printAll = false, std::ostream& os = std::cout,
                T step = 0.001) {
  PrintTitle("SECANT METHOD TEST", os);
  auto method = SecantMethod<T>(function, derivative);
  auto result = method.Solution(bounds, bounds_count, step, printAll, os);
  if (result == NULL) throw std::runtime_error("Null back");

  PrintAnswers(answers, result, bounds_count / 2, os);
  free(result);
}

void Task1(bool printAll = false, std::ostream& os = std::cout) {
  os << "\nTASK 1 fun: -x^2 + 7x - 4ln(x) - 7\n";
  std::function<float(float)> fun = function<float>;
  std::function<float(float)> der = derivative<float>;

  float answers[] = {0.2766, 1.7925, 3.6841};
  float bounds[] = {0.001, 1.0, 1.0, 2.0, 3.0, 4.0};

  NewtonTest(bounds, 6, fun, der, answers, printAll, os);
  IterationTest(bounds, 6, fun, der, answers, printAll, os);
  SecantTest(bounds, 6, fun, der, answers, printAll, os, 0.1f);
}

void Task2(bool printAll = false, std::ostream& os = std::cout) {
  os << "\nTASK 2 fun: 100x^2 - 1000x -6\n";
  std::function<float(float)> fun = function2<float>;
  std::function<float(float)> der = derivative2<float>;

  float answers[] = {-0.006, 10.006};
  float bounds[] = {-1, 0, 10, 11};
  NewtonTest(bounds, 4, fun, der, answers, printAll, os);
  IterationTest(bounds, 4, fun, der, answers, printAll, os);
  SecantTest(bounds, 4, fun, der, answers, printAll, os);
}

int main() {
  std::ofstream os;

  os.open("../results/Task1.txt", std::ofstream::out | std::ofstream::trunc);
  Task1(false, os);
  os.close();

  os.open("../results/Task1+.txt", std::ofstream::out | std::ofstream::trunc);
  Task1(true, os);
  os.close();

  os.open("../results/Task2.txt", std::ofstream::out | std::ofstream::trunc);
  Task2(false, os);
  os.close();

  os.open("../results/Task2+.txt", std::ofstream::out | std::ofstream::trunc);
  Task2(true, os);
  os.close();

  Task1();
  Task2();

  return 0;
}
