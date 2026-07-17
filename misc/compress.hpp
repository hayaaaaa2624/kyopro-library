#pragma once

#include "../base.hpp"

/**
 * @brief 座標圧縮を行う。
 * @param values 各要素を 0 始まりの順位に書き換える。
 * @return 昇順・重複除去済みの元の値。
 * @note 計算量 O(N log N)
 */
template <class T>
vector<T> compress(vector<T>& values) {
    vector<T> original_values = values;
    sort(original_values.begin(), original_values.end());
    original_values.erase(unique(original_values.begin(), original_values.end()), original_values.end());
    for (T& value : values) {
        value = static_cast<T>(lower_bound(original_values.begin(), original_values.end(), value) - original_values.begin());
    }
    return original_values;
}
