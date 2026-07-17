#pragma once

#include "modpow.hpp"

/**
 * @brief 素数 mod 上で階乗と逆階乗を高速に計算する。
 *
 * 構築時に 0 以上 max_n 以下の階乗と逆階乗を前計算する。
 * @tparam Mod 法。素数であること。
 */
template <ll Mod = MOD>
class Factorial {
private:
    vector<ll> factorial_;
    vector<ll> inverse_factorial_;

public:
    /**
     * @brief 0 以上 max_n 以下を前計算する。
     * @pre 0 <= max_n < Mod
     * @note 計算量 O(max_n)、メモリ O(max_n)。
     */
    explicit Factorial(int max_n)
        : factorial_(max_n + 1, 1), inverse_factorial_(max_n + 1, 1) {
        assert(0 <= max_n);
        assert(max_n < Mod);

        for (int i = 1; i <= max_n; ++i) {
            factorial_[i] = factorial_[i - 1] * i % Mod;
        }

        inverse_factorial_[max_n] = modpow(factorial_[max_n], Mod - 2, Mod);
        for (int i = max_n; i >= 1; --i) {
            inverse_factorial_[i - 1] = inverse_factorial_[i] * i % Mod;
        }
    }

    /** @brief n! mod Mod を返す。計算量 O(1)。 */
    ll factorial(int n) const {
        assert(0 <= n && n < static_cast<int>(factorial_.size()));
        return factorial_[n];
    }

    /** @brief (n!)^{-1} mod Mod を返す。計算量 O(1)。 */
    ll inverse_factorial(int n) const {
        assert(0 <= n && n < static_cast<int>(inverse_factorial_.size()));
        return inverse_factorial_[n];
    }

    /** @brief 前計算済みの最大値を返す。 */
    int max_n() const {
        return static_cast<int>(factorial_.size()) - 1;
    }
};
