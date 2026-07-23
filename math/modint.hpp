#pragma once

#include "../base.hpp"

/**
 * @brief コンパイル時に法を指定する modint
 *
 * 加減乗除、累乗、逆元を通常の数値型に近い記法で扱える。
 * 除算は MOD が素数で、除数が 0 でない場合を前提とする。
 */
template <int MOD>
class ModInt {
public:
    using value_type = int;

    constexpr ModInt(long long value = 0) {
        value %= MOD;
        if (value < 0) value += MOD;
        value_ = static_cast<int>(value);
    }

    static constexpr int mod() { return MOD; }
    constexpr int val() const { return value_; }

    constexpr ModInt& operator+=(const ModInt& rhs) {
        value_ += rhs.value_;
        if (value_ >= MOD) value_ -= MOD;
        return *this;
    }

    constexpr ModInt& operator-=(const ModInt& rhs) {
        value_ -= rhs.value_;
        if (value_ < 0) value_ += MOD;
        return *this;
    }

    constexpr ModInt& operator*=(const ModInt& rhs) {
        value_ = static_cast<int>(1LL * value_ * rhs.value_ % MOD);
        return *this;
    }

    constexpr ModInt& operator/=(const ModInt& rhs) {
        return *this *= rhs.inv();
    }

    constexpr ModInt operator+() const { return *this; }
    constexpr ModInt operator-() const { return ModInt(-value_); }

    friend constexpr ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
    friend constexpr ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
    friend constexpr ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
    friend constexpr ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }

    friend constexpr bool operator==(const ModInt& lhs, const ModInt& rhs) {
        return lhs.value_ == rhs.value_;
    }

    friend constexpr bool operator!=(const ModInt& lhs, const ModInt& rhs) {
        return !(lhs == rhs);
    }

    ModInt pow(long long exponent) const {
        assert(exponent >= 0);
        ModInt base = *this;
        ModInt result = 1;
        while (exponent > 0) {
            if (exponent & 1LL) result *= base;
            base *= base;
            exponent >>= 1;
        }
        return result;
    }

    ModInt inv() const {
        assert(value_ != 0);
        return pow(MOD - 2LL);
    }

    friend istream& operator>>(istream& is, ModInt& value) {
        long long x;
        is >> x;
        value = ModInt(x);
        return is;
    }

    friend ostream& operator<<(ostream& os, const ModInt& value) {
        return os << value.value_;
    }

private:
    int value_;
};

using mint998 = ModInt<998244353>;
using mint107 = ModInt<1000000007>;
