#pragma once

#include "../base.hpp"

/**
 * @brief 狭義単調増加部分列の最大長を返す。
 * @note 計算量 O(N log N)
 */
template <class T>
int LIS(const vector<T>& values) {
    vector<T> tails;
    for (const T& value : values) {
        auto it = lower_bound(tails.begin(), tails.end(), value);
        if (it == tails.end()) tails.push_back(value);
        else *it = value;
    }
    return static_cast<int>(tails.size());
}
