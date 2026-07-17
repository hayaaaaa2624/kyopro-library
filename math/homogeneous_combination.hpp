#pragma once

#include "combination.hpp"

/**
 * @brief 素数 mod 上で重複組合せ nHr を高速に計算する。
 * @tparam Mod 法。素数であること。
 */
template <ll Mod = MOD>
class HomogeneousCombination {
private:
    Combination<Mod> combination_;

public:
    /**
     * @brief 0 以上 max_n 以下の nCr を前計算する。
     * @pre 0 <= max_n < Mod
     * @note homogeneous(n, r) には max_n >= n + r - 1 が必要。
     */
    explicit HomogeneousCombination(int max_n) : combination_(max_n) {}

    /**
     * @brief 重複組合せ nHr mod Mod を返す。
     * @return n < 0 または r < 0 のとき 0。
     * @note nHr = (n + r - 1)Cr。計算量 O(1)。
     */
    ll homogeneous(int n, int r) const {
        if (n < 0 || r < 0) return 0;
        if (n == 0) return r == 0 ? 1 : 0;
        return combination_.combination(n + r - 1, r);
    }
};
