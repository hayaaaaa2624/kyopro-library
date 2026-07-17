#pragma once

#include "../base.hpp"

/** @brief a と b の最大公約数を返す。 */
template <class T>
T gcd(T a, T b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        const T remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}
