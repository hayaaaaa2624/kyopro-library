#pragma once

#include "../base.hpp"

struct BellmanFordEdge {
    int from;
    int to;
    ll cost;
};

// 後方互換用。ほかの Edge 型と衝突する場合は BellmanFordEdge を使用する。
using Edge = BellmanFordEdge;

/**
 * @brief 負辺を含むグラフの単一始点最短路を求める。
 * @note 計算量 O(VE)。この関数は負閉路検出を行わない。
 */
inline vector<ll> bellman_ford(int vertex_count, const vector<BellmanFordEdge>& edges, int start) {
    constexpr ll INF = 1LL << 60;
    vector<ll> distance(vertex_count, INF);
    distance[start] = 0;

    for (int i = 0; i < vertex_count - 1; ++i) {
        bool updated = false;
        for (const auto& edge : edges) {
            if (distance[edge.from] == INF) continue;
            if (distance[edge.to] <= distance[edge.from] + edge.cost) continue;
            distance[edge.to] = distance[edge.from] + edge.cost;
            updated = true;
        }
        if (!updated) break;
    }
    return distance;
}
