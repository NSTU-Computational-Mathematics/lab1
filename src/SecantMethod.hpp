#pragma once

#include "BaseMethod.hpp"

template <float_like T = float>
class SecantMethod : public BaseMethod<T> {
 public:
  SecantMethod(std::function<T(T)> function, std::function<T(T)> derivative,
               T epselon = 0.001)
      : BaseMethod<T>(function, derivative, epselon) {}

  T Solution(T l_bound, T r_bound) {
    T xn_minus_2 = SecantFormula(l_bound, r_bound);
    // T xn_minus_2 = l_bound;
    T xn_minus_1 = SecantFormula(xn_minus_1, l_bound);
    // if (fabsf())
    T xn = SecantFormula(xn_minus_1, xn_minus_2);
    // std::cout << "xn-2 == " << xn_minus_2 << "\n";

    // std::cout << "xn-1 == " << xn_minus_1 << "\n";
    // std::cout << "xn == " << xn << "\n";
    while (fabsf(xn - xn_minus_1) > this->epselon) {
      // std::cout << "xn-2 == " << xn_minus_2 << "\n";
      // std::cout << "xn-1 == " << xn_minus_1 << "\n";
      // std::cout << "xn == " << xn << "\n";
      auto buf1 = xn_minus_1;
      auto buf2 = xn_minus_2;
      xn_minus_2 = xn_minus_1;
      xn_minus_1 = xn;
      xn = SecantFormula(buf1, buf2);
    }
    return xn;
  }

  T* Solution(T* bounds, int bounds_count) {
    T* result = new T[bounds_count];
    for (int i = 0; i < bounds_count; i += 2)
      result[i] = Solution(bounds[i], bounds[i + 1]);

    return result;
  }

 private:
  T SecantFormula(T xn_minus_1, T xn_minus_2) {
    auto diff1 = xn_minus_1 - xn_minus_2;
    auto diff2 = this->function(xn_minus_1) - this->function(xn_minus_2);
    if (fabsf(diff1) < this->epselon) return xn_minus_1;
    if (fabsf(diff2) < this->epselon) throw std::runtime_error("asd");
    // std::cout << "diff1 == " << diff1 << std::endl;
    // std::cout << "diff2 == " << diff2 << std::endl;
    return xn_minus_1 - (this->function(xn_minus_1) * diff1 / diff2);
  }
};