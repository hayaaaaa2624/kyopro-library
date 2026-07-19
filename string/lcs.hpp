#pragma once
#include "../base.hpp"

/**
 * @brief 最長共通部分列（LCS）の長さを求める。
 *
 * 文字列 s, t の両方に部分列として現れる文字列のうち、
 * 最長のものの長さを返す。
 *
 * @param s 1つ目の文字列
 * @param t 2つ目の文字列
 * @return LCSの長さ
 *
 * @note 計算量: O(|s| × |t|)
 * @note 空間計算量: O(|t|)
 */
inline int lcs_length(const string& s, const string& t) {
    const int n = static_cast<int>(s.size());
    const int m = static_cast<int>(t.size());

    vector<int> dp(m + 1, 0);

    for (int i = 0; i < n; ++i) {
        int diagonal = 0;

        for (int j = 0; j < m; ++j) {
            const int previous = dp[j + 1];

            if (s[i] == t[j]) {
                dp[j + 1] = diagonal + 1;
            } else {
                dp[j + 1] = max(dp[j + 1], dp[j]);
            }

            diagonal = previous;
        }
    }

    return dp[m];
}

/**
 * @brief 最長共通部分列（LCS）を1つ復元する。
 *
 * LCSが複数存在する場合、そのうちの1つを返す。
 *
 * @param s 1つ目の文字列
 * @param t 2つ目の文字列
 * @return LCSとなる文字列
 *
 * @note 計算量: O(|s| × |t|)
 * @note 空間計算量: O(|s| × |t|)
 */
inline string longest_common_subsequence(
    const string& s,
    const string& t
) {
    const int n = static_cast<int>(s.size());
    const int m = static_cast<int>(t.size());

    vector<vector<int>> dp(
        n + 1,
        vector<int>(m + 1, 0)
    );

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i] == t[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                dp[i + 1][j + 1] =
                    max(dp[i][j + 1], dp[i + 1][j]);
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