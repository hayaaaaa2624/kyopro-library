#pragma once

#include "../base.hpp"
#include "../data_structure/unionfind.hpp"

/** Kruskal 法で使う無向辺。 */
template <class Cost>
struct KruskalEdge {
    int from;
    int to;
    Cost cost;
};

/**
 * @brief 最小全域森のコストを求める。
 *
 * グラフが連結なら最小全域木、非連結なら各連結成分の最小全域木の合計を返す。
 * used_edges を渡した場合、採用した辺を格納する。
 *
 * @note 計算量 O(E log E)
 */
template <class Cost>
Cost kruskal(int vertex_count, vector<KruskalEdge<Cost>> edges,
             vector<KruskalEdge<Cost>>* used_edges = nullptr) {
    sort(edges.begin(), edges.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.cost < rhs.cost;
    });

    UnionFind uf(vertex_count);
    Cost total{};
    if (used_edges != nullptr) used_edges->clear();

    for (const auto& edge : edges) {
        if (uf.same(edge.from, edge.to)) continue;
        uf.unite(edge.from, edge.to);
        total += edge.cost;
        if (used_edges != nullptr) used_edges->push_back(edge);
    }
    return total;
}
