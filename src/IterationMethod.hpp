#pragma once

#include <cmath>

#include "BaseMethod.hpp"

template <float_like T = float>
class IterationMethod : public BaseMethod<T> {
 public:
  IterationMethod(std::function<T(T)> function, std::function<T(T)> derivative,
                  T epselon = 0.001)
      : BaseMethod<T>(function, derivative, epselon) {}

  T IterationSolution(T l_bound, T r_bound) {
    auto max_value = fabsf(findMaxValueInRange(l_bound, r_bound));
    lambda = 1 / max_value;
    if (this->derivative(l_bound) > 0) lambda *= -1;

    T xn_minus_1 = phi(l_bound);
    T xn = phi(xn_minus_1);

    std::cout << "lambda == " << lambda << std::endl;
    while (!isConvergence(xn, xn_minus_1, fabsf(phiDerivative(xn)))) {
      std::cout << "xn-1 == " << xn_minus_1 << " xn == " << xn << std::endl;
      if (xn != xn) break;
      xn_minus_1 = xn;
      xn = phi(xn);
    }
    return xn;
  }

  T* IterationSolution(T* l_bounds, int bounds_count) {
    T* result = new T[bounds_count];
    for (int i = 0; i < bounds_count; i++) {
      result[i] = IterationSolution(l_bounds[i], this->epselon);
    }
    return result;
  }

 private:
  bool isConvergence(T Xn, T Xnmin1, T q) {
    auto difference = fabsf(Xn - Xnmin1);

    if (q < 1 / 2)
      return difference < this->epselon;
    else
      return difference < (q - 1) * this->epselon / q;
  }
  T findMaxValueInRange(T l, T r) {
    T max_value = this->function(l);
    for (T i = l; i < r; i += this->epselon) {
      T value = this->function(i);
      if (max_value < value) max_value = value;
    }
    return max_value;
  }

  T phi(T x) { return x + this->lambda * this->function(x); }

  T phiDerivative(T x) { return 1 + this->lambda * this->derivative(x); }

  T lambda;
};