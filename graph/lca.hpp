#pragma once

#include "../base.hpp"

/**
 * @brief 木上の Lowest Common Ancestor（最小共通祖先）。
 *
 * ダブリングにより、構築 O(N log N)、LCA・頂点間距離を O(log N) で求める。
 * 入力グラフは連結な木であることを前提とする。
 */
struct LCA {
    int n;
    int log;
    Graph graph;
    vector<int> depth;
    vector<vector<int>> parent;

    explicit LCA(const Graph& input_graph, int root = 0)
        : n(static_cast<int>(input_graph.size())), log(1), graph(input_graph) {
        while ((1 << log) <= max(1, n)) ++log;
        depth.assign(n, -1);
        parent.assign(log, vector<int>(n, -1));

        build_depth(root, -1, 0);
        for (int k = 0; k + 1 < log; ++k) {
            for (int vertex = 0; vertex < n; ++vertex) {
                const int p = parent[k][vertex];
                parent[k + 1][vertex] = (p == -1 ? -1 : parent[k][p]);
            }
        }
    }

    void build_depth(int vertex, int previous, int current_depth) {
        parent[0][vertex] = previous;
        depth[vertex] = current_depth;
        for (int next : graph[vertex]) {
            if (next == previous) continue;
            build_depth(next, vertex, current_depth + 1);
        }
    }

    /** u と v の最小共通祖先を返す。 */
    int query(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        const int difference = depth[u] - depth[v];
        for (int k = 0; k < log; ++k) {
            if ((difference >> k) & 1) u = parent[k][u];
        }
        if (u == v) return u;

        for (int k = log - 1; k >= 0; --k) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    /** 木上での u-v 間の辺数を返す。 */
    int dist(int u, int v) const {
        return depth[u] + depth[v] - 2 * depth[query(u, v)];
    }
};
