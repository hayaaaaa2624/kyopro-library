#pragma once

#include "modpow.hpp"

/**
 * @brief a / b mod m を求める。
 * @pre m は素数、かつ b は m の倍数でないこと。
 */
inline ll moddiv(ll a, ll b, ll m) {
    return (a % m) * modpow(b, m - 2, m) % m;
}
