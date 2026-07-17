#pragma once

#include "../base.hpp"

/**
 * @brief Z algorithm。
 * @return z[i] = S と S[i:] の最長共通接頭辞長。空文字列には空配列を返す。
 * @note 計算量 O(N)
 */
inline vector<int> z_algorithm(const string& text) {
    const int n = static_cast<int>(text.size());
    if (n == 0) return {};

    vector<int> z(n);
    z[0] = n;
    int index = 1;
    int matched = 0;

    while (index < n) {
        while (index + matched < n && text[matched] == text[index + matched]) ++matched;
        z[index] = matched;
        if (matched == 0) {
            ++index;
            continue;
        }

        int offset = 1;
        while (index + offset < n && offset + z[offset] < matched) {
            z[index + offset] = z[offset];
            ++offset;
        }
        index += offset;
        matched -= offset;
    }
    return z;
}
