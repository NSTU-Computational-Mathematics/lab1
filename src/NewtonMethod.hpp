#pragma once

#include "BaseMethod.hpp"

template <float_like T = float>
class NewtonMethod : public BaseMethod<T> {
 public:
  NewtonMethod(std::function<T(T)> function, std::function<T(T)> derivative,
               T epsilon = 0.001)
      : BaseMethod<T>(function, derivative, epsilon) {}

  T Solution(T l_bound, bool print_intermediate_results = false,
             std::ostream& os = std::cout) {
    T xn = NewtonFormula(l_bound);
    T xn_plus_1 = NewtonFormula(xn);
    while (!this->isEqual(xn, xn_plus_1)) {
      if (print_intermediate_results) {
        os << "xn = " << xn << " xn+1 = " << xn_plus_1 << '\n';
      }
      xn = xn_plus_1;
      xn_plus_1 = NewtonFormula(xn);
    }
    return xn_plus_1;
  }

  T* Solution(T* bounds, int bounds_count,
              bool print_intermediate_results = false,
              std::ostream& os = std::cout) {
    T* result = new T[bounds_count / 2];
    if (print_intermediate_results) this->printIntermTitle(os);
    for (int i = 0, j = 0; i < bounds_count / 2; i++, j += 2) {
      if (print_intermediate_results) os << "#" << i + 1 << '\n';

      result[i] = Solution(bounds[j], print_intermediate_results, os);
    }
    return result;
  }

 private:
  T NewtonFormula(T x) { return x - this->function(x) / this->derivative(x); }
};