#pragma once

#include "../base.hpp"

/** @brief a^n mod m を二分累乗法で求める。計算量 O(log n)。 */
inline ll modpow(ll a, ll n, ll m) {
    a %= m;
    ll result = 1 % m;
    while (n > 0) {
        if (n & 1) result = result * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return result;
}
