#pragma once

#include "../base.hpp"

/**
 * @brief Kahn 法によるトポロジカルソート。
 * @return 順序。返り値の要素数が V 未満なら閉路が存在する。
 * @note 計算量 O(V + E)
 */
inline vector<int> topological_sort(const Graph& graph) {
    const int n = static_cast<int>(graph.size());
    vector<int> indegree(n);
    for (int vertex = 0; vertex < n; ++vertex) {
        for (int next : graph[vertex]) ++indegree[next];
    }

    queue<int> que;
    for (int vertex = 0; vertex < n; ++vertex) {
        if (indegree[vertex] == 0) que.push(vertex);
    }

    vector<int> order;
    while (!que.empty()) {
        const int vertex = que.front();
        que.pop();
        order.push_back(vertex);
        for (int next : graph[vertex]) {
            if (--indegree[next] == 0) que.push(next);
        }
    }
    return order;
}
