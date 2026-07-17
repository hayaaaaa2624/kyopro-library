#pragma once

#include "../base.hpp"

using WeightedGraph = vector<vector<pair<int, ll>>>;

/**
 * @brief 非負辺重みグラフの単一始点最短路を求める。
 * @return 始点からの距離。到達不能な頂点は 2^60。
 * @note 計算量 O((V + E) log V)。負辺には使用不可。
 */
inline vector<ll> dijkstra(const WeightedGraph& graph, int start) {
    constexpr ll INF = 1LL << 60;
    vector<ll> distance(graph.size(), INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;

    distance[start] = 0;
    que.emplace(0, start);
    while (!que.empty()) {
        const auto [current_distance, vertex] = que.top();
        que.pop();
        if (current_distance != distance[vertex]) continue;

        for (const auto& [next, cost] : graph[vertex]) {
            if (distance[next] <= current_distance + cost) continue;
            distance[next] = current_distance + cost;
            que.emplace(distance[next], next);
        }
    }
    return distance;
}
