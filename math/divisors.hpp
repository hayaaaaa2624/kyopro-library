#pragma once

#include "../base.hpp"

/**
 * @brief 正の整数 n の正の約数を昇順で列挙する。
 * @note 計算量 O(sqrt(n) + d log d)、d は約数個数
 */
inline vector<long long> divisors(long long n) {
    assert(n >= 1);
    vector<long long> result;

    for (long long d = 1; d <= n / d; ++d) {
        if (n % d != 0) continue;
        result.push_back(d);
        if (d != n / d) result.push_back(n / d);
    }

    sort(result.begin(), result.end());
    return result;
}
