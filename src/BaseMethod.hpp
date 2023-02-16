#pragma once

#include <functional>

template <typename T = float>
concept float_like = std::is_same_v<T, float> || std::is_same_v<T, double> ||
                     std::is_same_v<T, long double>;

template <float_like T = float>
class BaseMethod {
 public:
  BaseMethod(std::function<T(T)> function, std::function<T(T)> derivative,
             T epselon) {
    this->function = function;
    this->derivative = derivative;
    if (epselon < 1e-30) throw std::runtime_error("too small epselon");
    if (epselon < 0) throw std::runtime_error("negative epselon");
    this->epselon = epselon;
  }
  T Function(T x) { return this->function(x); }
  T Derivative(T x) { return this->derivative(x); }

  T getEpselon() { return this->epselon; }
  void setEpselon(T newEpselon) {
    if (newEpselon < 1e-30) throw std::runtime_error("too small epselon");
    if (newEpselon < 0) throw std::runtime_error("negative epselon");
    this->epselon = newEpselon;
  }

 protected:
  T epselon;
  std::function<T(T)> function;
  std::function<T(T)> derivative;
  bool isEqual(T val1, T val2) {
    if (t_abs(val1 - val2) < this->epselon)
      return true;
    else
      return false;
  }
  T t_abs(T x) {
    if (x < 0) x *= -1;
    return x;
  }
};
