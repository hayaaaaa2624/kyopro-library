#pragma once

#include "../base.hpp"

/** 木の重み付き辺。重みは非負を想定する。 */
template <class Cost>
struct TreeEdge {
    int to;
    Cost cost;
};

/**
 * @brief 重み付き木の直径を求める。
 * @return {直径の長さ, 一方の端点, もう一方の端点}
 * @note 計算量 O(N)
 */
template <class Cost>
tuple<Cost, int, int> tree_diameter(const vector<vector<TreeEdge<Cost>>>& tree) {
    const int n = static_cast<int>(tree.size());
    assert(n > 0);

    auto farthest = [&](int start) {
        vector<Cost> distance(n, Cost{-1});
        vector<int> parent(n, -1);
        stack<int> st;
        distance[start] = Cost{};
        st.push(start);

        while (!st.empty()) {
            const int v = st.top();
            st.pop();
            for (const auto& edge : tree[v]) {
                if (edge.to == parent[v]) continue;
                parent[edge.to] = v;
                distance[edge.to] = distance[v] + edge.cost;
                st.push(edge.to);
            }
        }

        int vertex = start;
        for (int v = 0; v < n; ++v) {
            if (distance[v] > distance[vertex]) vertex = v;
        }
        return pair<int, vector<Cost>>(vertex, std::move(distance));
    };

    const int left = farthest(0).first;
    auto [right, distance] = farthest(left);
    return {distance[right], left, right};
}

/** 無重み木の直径。 */
inline tuple<int, int, int> tree_diameter(const Graph& tree) {
    vector<vector<TreeEdge<int>>> weighted(tree.size());
    for (size_t v = 0; v < tree.size(); ++v) {
        for (int to : tree[v]) weighted[v].push_back({to, 1});
    }
    return tree_diameter(weighted);
}
