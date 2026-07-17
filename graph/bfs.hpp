#pragma once

#include "../base.hpp"

/**
 * @brief 無重みグラフの単一始点最短距離を求める。
 * @return 始点からの距離。到達不能な頂点は -1。
 * @note 計算量 O(V + E)
 */
inline vector<int> bfs(const Graph& graph, int start) {
    vector<int> distance(graph.size(), -1);
    queue<int> que;
    distance[start] = 0;
    que.push(start);

    while (!que.empty()) {
        const int vertex = que.front();
        que.pop();
        for (int next : graph[vertex]) {
            if (distance[next] != -1) continue;
            distance[next] = distance[vertex] + 1;
            que.push(next);
        }
    }
    return distance;
}
