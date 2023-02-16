#pragma once

#include "BaseMethod.hpp"

template <float_like T = float>
class NewtonMethod : public BaseMethod<T> {
 public:
  NewtonMethod(std::function<T(T)> function, std::function<T(T)> derivative,
               T epselon = 0.001)
      : BaseMethod<T>(function, derivative, epselon) {}

  T Solution(T l_bound) {
    T xn = NewtonFormula(l_bound);
    T xn_plus_1 = NewtonFormula(xn);
    while (!this->isEqual(xn, xn_plus_1)) {
      xn = xn_plus_1;
      xn_plus_1 = NewtonFormula(xn);
    }
    return xn_plus_1;
  }

  T* Solution(T* bounds, int bounds_count) {
    T* result = new T[bounds_count / 2];

    for (int i = 0, j = 0; i < bounds_count / 2; i++, j += 2) {
      result[i] = Solution(bounds[j]);
    }
    return result;
  }

 private:
  T NewtonFormula(T x) { return x - this->function(x) / this->derivative(x); }
};