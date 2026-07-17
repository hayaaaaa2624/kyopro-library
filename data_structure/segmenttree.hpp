#pragma once

#include "../base.hpp"

/**
 * @brief モノイドを扱う反復型セグメント木
 *
 * @tparam T 要素型
 * 構築 O(N)、一点更新・区間取得 O(log N)。区間は [left, right)。
 */
template <class T>
struct SegmentTree {
    int n;
    T identity;
    function<T(T, T)> operation;
    vector<T> data;

    SegmentTree(int size, T identity_element, function<T(T, T)> op)
        : n(1), identity(identity_element), operation(std::move(op)) {
        while (n < size) n <<= 1;
        data.assign(2 * n, identity);
    }

    /** build() 前に葉の値を設定する。 */
    void set(int index, T value) {
        data[index + n] = value;
    }

    void build() {
        for (int i = n - 1; i >= 1; --i) {
            data[i] = operation(data[i << 1], data[i << 1 | 1]);
        }
    }

    void update(int index, T value) {
        index += n;
        data[index] = value;
        while (index >>= 1) {
            data[index] = operation(data[index << 1], data[index << 1 | 1]);
        }
    }

    T query(int left, int right) const {
        T left_result = identity;
        T right_result = identity;
        for (left += n, right += n; left < right; left >>= 1, right >>= 1) {
            if (left & 1) left_result = operation(left_result, data[left++]);
            if (right & 1) right_result = operation(data[--right], right_result);
        }
        return operation(left_result, right_result);
    }

    T operator[](int index) const {
        return data[index + n];
    }
};
