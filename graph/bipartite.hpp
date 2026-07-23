#pragma once

#include "../base.hpp"

/**
 * @brief 無向グラフが二部グラフか判定する。
 * @param graph 隣接リスト
 * @param colors 指定時、各頂点の色（0/1）を格納する。
 * @note 計算量 O(V + E)
 */
inline bool is_bipartite(const Graph& graph, vector<int>* colors = nullptr) {
    const int n = static_cast<int>(graph.size());
    vector<int> color(n, -1);
    queue<int> que;

    for (int start = 0; start < n; ++start) {
        if (color[start] != -1) continue;
        color[start] = 0;
        que.push(start);

        while (!que.empty()) {
            const int v = que.front();
            que.pop();
            for (int to : graph[v]) {
                if (color[to] == -1) {
                    color[to] = color[v] ^ 1;
                    que.push(to);
                } else if (color[to] == color[v]) {
                    if (colors != nullptr) *colors = std::move(color);
                    return false;
                }
            }
        }
    }

    if (colors != nullptr) *colors = std::move(color);
    return true;
}
