#pragma once

#include "BaseMethod.hpp"

template <float_like T = float>
class NewtonMethod : public BaseMethod<T> {
 public:
  NewtonMethod(std::function<T(T)> function, std::function<T(T)> derivative,
               T epselon = 0.001)
      : BaseMethod<T>(function, derivative, epselon) {}

  T NewtonSolution(T l_bound) {
    T xn = NewtonFormula(l_bound);
    T xn_plus_1 = NewtonFormula(xn);
    while (abs(xn - xn_plus_1) > this->epselon) {
      xn = xn_plus_1;
      xn_plus_1 = NewtonFormula(xn);
    }
    return xn_plus_1;
  }

  T* NewtonSolution(T* l_bounds, int bounds_count) {
    T* result = new T[bounds_count];
    for (int i = 0; i < bounds_count; i++) {
      result[i] = NewtonMethod(l_bounds[i], this->epselon);
    }
    return result;
  }

 private:
  T NewtonFormula(T x) { return x - this->function(x) / this->derivative(x); }
};