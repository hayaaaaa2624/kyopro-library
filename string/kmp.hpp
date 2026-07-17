#pragma once

#include "../base.hpp"

/**
 * @brief Knuth-Morris-Pratt 法による文字列検索。
 *
 * 構築 O(M)、match(text) O(N)。一致開始位置をすべて返す。
 */
struct KMP {
    string pattern;
    vector<int> failure;

    explicit KMP(const string& pattern_text) : pattern(pattern_text) {
        const int m = static_cast<int>(pattern.size());
        failure.assign(m + 1, 0);
        failure[0] = -1;

        int i = 0;
        int matched = -1;
        while (i < m) {
            while (matched != -1 && pattern[i] != pattern[matched]) {
                matched = failure[matched];
            }
            ++i;
            ++matched;
            failure[i] = matched;
        }
    }

    vector<int> match(const string& text) const {
        vector<int> positions;
        const int n = static_cast<int>(text.size());
        const int m = static_cast<int>(pattern.size());
        if (m == 0) {
            positions.resize(n + 1);
            iota(positions.begin(), positions.end(), 0);
            return positions;
        }

        int i = 0;
        int matched = 0;
        while (i < n) {
            while (matched != -1 && (matched == m || text[i] != pattern[matched])) {
                matched = failure[matched];
            }
            ++i;
            ++matched;
            if (matched == m) positions.push_back(i - m);
        }
        return positions;
    }
};
