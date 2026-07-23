#pragma once

#include "../base.hpp"

/**
 * @brief 2つの列の最長共通部分列（LCS）の長さを求める。
 * @note 計算量 O(NM)、空間計算量 O(M)
 */
template <class T>
int lcs_length(const vector<T>& s, const vector<T>& t) {
    vector<int> dp(t.size() + 1, 0);
    for (const T& value_s : s) {
        int diagonal = 0;
        for (size_t j = 0; j < t.size(); ++j) {
            const int previous = dp[j + 1];
            if (value_s == t[j]) {
                dp[j + 1] = diagonal + 1;
            } else {
                dp[j + 1] = max(dp[j + 1], dp[j]);
            }
            diagonal = previous;
        }
    }
    return dp.back();
}

inline int lcs_length(const string& s, const string& t) {
    return lcs_length(vector<char>(s.begin(), s.end()), vector<char>(t.begin(), t.end()));
}

/**
 * @brief 文字列 s, t の LCS を1つ復元する。
 * @note 計算量・空間計算量 O(|s||t|)
 */
inline string longest_common_subsequence(const string& s, const string& t) {
    const int n = static_cast<int>(s.size());
    const int m = static_cast<int>(t.size());
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i] == t[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }

    string result;
    int i = n;
    int j = m;
    while (i > 0 && j > 0) {
        if (s[i - 1] == t[j - 1]) {
            result.push_back(s[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    reverse(result.begin(), result.end());
    return result;
}
