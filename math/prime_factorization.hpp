#pragma once

#include "../base.hpp"

/**
 * @brief 正の整数 n を素因数分解する。
 * @return (素因数, 指数) の組を昇順で返す。
 * @note 計算量 O(sqrt(n))
 */
inline vector<pair<long long, int>> prime_factorization(long long n) {
    assert(n >= 1);
    vector<pair<long long, int>> factors;

    for (long long p = 2; p <= n / p; ++p) {
        if (n % p != 0) continue;
        int exponent = 0;
        while (n % p == 0) {
            n /= p;
            ++exponent;
        }
        factors.emplace_back(p, exponent);
    }

    if (n > 1) factors.emplace_back(n, 1);
    return factors;
}
