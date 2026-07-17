#pragma once

#include "gcd.hpp"

/** @brief a と b の最小公倍数を返す。どちらかが 0 なら 0。 */
template <class T>
T lcm(T a, T b) {
    if (a == 0 || b == 0) return 0;
    return a / gcd(a, b) * b;
}
