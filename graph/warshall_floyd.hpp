#pragma once

#include "../base.hpp"

/**
 * @brief Warshall-Floyd 法で全点対最短距離を求める。
 *
 * dist[i][j] に辺コスト、辺がない場所に inf を設定して渡す。
 * dist[i][i] は 0 にしておく。
 *
 * @return 負閉路が存在しなければ true。存在すれば false。
 * @note 計算量 O(N^3)、空間計算量 O(N^2)
 */
template <class T>
bool warshall_floyd(vector<vector<T>>& dist, T inf) {
    const int n = static_cast<int>(dist.size());
    for (const auto& row : dist) assert(static_cast<int>(row.size()) == n);

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][k] == inf) continue;
            for (int j = 0; j < n; ++j) {
                if (dist[k][j] == inf) continue;
                chmin(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (dist[i][i] < T{}) return false;
    }
    return true;
}
