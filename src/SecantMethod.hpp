#pragma once

#include "BaseMethod.hpp"

template <float_like T = float>
class SecantMethod : public BaseMethod<T> {
 public:
  SecantMethod(std::function<T(T)> function, std::function<T(T)> derivative,
               T epsilon = 0.001)
      : BaseMethod<T>(function, derivative, epsilon) {}

  T Solution(T l_bound, T r_bound, bool print_intermediate_results = false,
             std::ostream& os = std::cout) {
    T xn_minus_2 = SecantFormula(l_bound, r_bound);
    T xn_minus_1 = SecantFormula(xn_minus_1, r_bound);
    T xn = SecantFormula(xn_minus_1, xn_minus_2);

    if (print_intermediate_results) {
      os << "xn-1 = " << xn_minus_1 << " xn = " << xn << '\n';
    }

    while (!this->isEqual(xn, xn_minus_1)) {
      if (print_intermediate_results) {
        os << "xn-1 = " << xn_minus_1 << " xn = " << xn << '\n';
      }
      if (xn != xn) break;

      auto buf1 = xn_minus_1;
      auto buf2 = xn_minus_2;

      xn_minus_2 = xn_minus_1;
      xn_minus_1 = xn;
      xn = SecantFormula(buf1, buf2);
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
          Solution(bounds[j], bounds[j] + 0.01, print_intermediate_results, os);
    }
    return result;
  }

 private:
  T SecantFormula(T xn_minus_1, T xn_minus_2) {
    auto diff1 = xn_minus_1 - xn_minus_2;
    auto diff2 = this->function(xn_minus_1) - this->function(xn_minus_2);
    if (diff1 < this->epsilon) return xn_minus_1;
    if (fabsf(diff2) < this->epsilon) throw std::runtime_error("asd");
    return xn_minus_1 - (this->function(xn_minus_1) * diff1 / diff2);
  }
};