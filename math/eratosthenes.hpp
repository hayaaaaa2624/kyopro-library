#pragma once

#include "../base.hpp"

/**
 * @brief N 以下の素数を列挙する。
 * @note 計算量 O(N log log N)、空間 O(N)
 */
inline vector<int> eratosthenes(int n) {
    if (n < 2) return {};

    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n / i; ++i) {
        if (!is_prime[i]) continue;
        for (int multiple = i * i; multiple <= n; multiple += i) {
            is_prime[multiple] = false;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}
