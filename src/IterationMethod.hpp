#pragma once

#include <cmath>

#include "BaseMethod.hpp"

template <float_like T = float>
class IterationMethod : public BaseMethod<T> {
 public:
  IterationMethod(std::function<T(T)> function, std::function<T(T)> derivative,
                  T epselon = 0.001)
      : BaseMethod<T>(function, derivative, epselon) {}

  T Solution(T l_bound, T r_bound) {
    lambda = -1 / findDerivativeAbsolutMaxValueInRange(l_bound, r_bound);
    if (this->derivative(l_bound) < 0) lambda *= -1;

    T xn_minus_1 = phi(l_bound);
    T xn = phi(xn_minus_1);

    int counter = 0;
    while (!isConvergence(xn, xn_minus_1, this->t_abs(phiDerivative(xn))) &&
           counter < 10) {
      if (xn != xn) break;
      xn_minus_1 = xn;
      xn = phi(xn);
      if (this->isEqual(xn, xn_minus_1)) counter++;
    }
    return xn;
  }

  T* Solution(T* bounds, int bounds_count) {
    T* result = new T[bounds_count / 2];
    for (int i = 0, j = 0; i < bounds_count / 2; i++, j += 2) {
      result[i] = Solution(bounds[j], bounds[j + 1]);
    }
    return result;
  }

 private:
  bool isConvergence(T Xn, T Xnmin1, T q) {
    auto difference = this->t_abs(Xn - Xnmin1);

    if (q < 1 / 2)
      return difference < this->epselon;
    else
      return difference < (q - 1) * this->epselon / q;
  }
  T findDerivativeAbsolutMaxValueInRange(T l, T r) {
    auto max_value = this->t_abs(this->derivative(l));
    for (T i = l; i < r; i += this->epselon) {
      T value = this->t_abs(this->derivative(i));
      if (max_value < value) max_value = value;
    }
    return max_value;
  }

  T phi(T x) { return x + this->lambda * this->function(x); }

  T phiDerivative(T x) { return 1 + this->lambda * this->derivative(x); }

  T lambda;
};