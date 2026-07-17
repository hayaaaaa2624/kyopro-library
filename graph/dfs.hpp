#pragma once

#include "../base.hpp"

/**
 * @brief 深さ優先探索で start から到達可能な頂点を訪問済みにする。
 * @note 計算量 O(V + E)。深いグラフでは再帰の深さに注意。
 */
inline void dfs(const Graph& graph, int start, vector<bool>& visited) {
    visited[start] = true;
    for (int next : graph[start]) {
        if (!visited[next]) dfs(graph, next, visited);
    }
}
