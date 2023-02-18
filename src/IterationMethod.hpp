#pragma once

#include <cmath>

#include "BaseMethod.hpp"

template <float_like T = float>
class IterationMethod : public BaseMethod<T> {
 public:
  IterationMethod(std::function<T(T)> function, std::function<T(T)> derivative,
                  T epsilon = 0.001)
      : BaseMethod<T>(function, derivative, epsilon) {}

  T Solution(T l_bound, T r_bound, bool print_intermediate_results = false,
             std::ostream& os = std::cout) {
    lambda = -1 / findDerivativeAbsolutMaxValueInRange(l_bound, r_bound);
    if (this->derivative(l_bound) < 0) lambda *= -1;

    T xn_minus_1 = phi(l_bound);
    T xn = phi(xn_minus_1);

    int counter = 0;
    while (!isConvergence(xn, xn_minus_1, this->t_abs(phiDerivative(xn))) &&
           counter < 1000) {
      if (print_intermediate_results) {
        os << "xn - 1 = " << xn_minus_1 << " xn = " << xn << '\n';
      }
      if (xn != xn) break;
      auto cycle_check = xn_minus_1;
      xn_minus_1 = xn;
      xn = phi(xn);
      if (this->isEqual(xn, xn_minus_1)) counter++;
      if (this->isEqual(xn, cycle_check)) counter++;
    }
    return xn;
  }

  T* Solution(T* bounds, int bounds_count,
              bool print_intermediate_results = false,
              std::ostream& os = std::cout) {
    T* result = new T[bounds_count / 2];
    if (print_intermediate_results) this->printIntermTitle(os);
    for (int i = 0, j = 0; i < bounds_count / 2; i++, j += 2) {
      if (print_intermediate_results) os << "#" << i + 1 << '\n';

      result[i] =
          Solution(bounds[j], bounds[j + 1], print_intermediate_results, os);
    }
    return result;
  }

 private:
  bool isConvergence(T Xn, T Xnmin1, T q) {
    auto difference = this->t_abs(Xn - Xnmin1);

    if (q < 1 / 2)
      return difference < this->epsilon;
    else
      return difference < (q - 1) * this->epsilon / q;
  }
  T findDerivativeAbsolutMaxValueInRange(T l, T r) {
    auto max_value = this->t_abs(this->derivative(l));
    for (T i = l; i < r; i += this->epsilon) {
      T value = this->t_abs(this->derivative(i));
      if (max_value < value) max_value = value;
    }
    return max_value;
  }

  T phi(T x) { return x + this->lambda * this->function(x); }

  T phiDerivative(T x) { return 1 + this->lambda * this->derivative(x); }

  T lambda;
};