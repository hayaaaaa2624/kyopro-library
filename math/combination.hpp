#pragma once

#include "factorial.hpp"

/**
 * @brief 素数 mod 上で組合せ nCr を高速に計算する。
 * @tparam Mod 法。素数であること。
 */
template <ll Mod = MOD>
class Combination {
private:
    Factorial<Mod> factorial_;

public:
    /**
     * @brief 0 以上 max_n 以下を前計算する。
     * @pre 0 <= max_n < Mod
     * @note 計算量 O(max_n)、メモリ O(max_n)。
     */
    explicit Combination(int max_n) : factorial_(max_n) {}

    /**
     * @brief nCr mod Mod を返す。
     * @return r < 0 または n < r のとき 0。
     * @note 計算量 O(1)。
     */
    ll combination(int n, int r) const {
        if (n < 0 || r < 0 || n < r) return 0;
        assert(n <= factorial_.max_n());

        return factorial_.factorial(n) * factorial_.inverse_factorial(r) % Mod
             * factorial_.inverse_factorial(n - r) % Mod;
    }
};
