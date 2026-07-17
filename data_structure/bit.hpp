#pragma once

#include "../base.hpp"

/**
 * @brief Binary Indexed Tree（Fenwick Tree）
 *
 * 0-indexed の配列に対して一点加算と区間和を管理する。
 * 各操作の計算量は O(log N)。
 */
template <class T>
struct BIT {
    int n;
    vector<T> bit;

    explicit BIT(int size) : n(size), bit(size + 1, T{}) {}

    /** a[index] += value */
    void add(int index, T value) {
        for (++index; index <= n; index += index & -index) {
            bit[index] += value;
        }
    }

    /** [0, right] の和を返す。 */
    T sum(int right) const {
        T result{};
        for (++right; right > 0; right -= right & -right) {
            result += bit[right];
        }
        return result;
    }

    /** [left, right) の和を返す。 */
    T sum(int left, int right) const {
        if (left >= right) return T{};
        return sum(right - 1) - (left == 0 ? T{} : sum(left - 1));
    }
};
