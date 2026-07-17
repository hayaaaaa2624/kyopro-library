#pragma once

#include "../base.hpp"

/**
 * @brief Kosaraju 法による強連結成分分解。
 *
 * build() は成分数を返し、scc[v] で頂点 v の成分番号を取得できる。
 * 計算量 O(V + E)。
 */
struct SCC {
    int n;
    Graph graph;
    Graph reverse_graph;
    vector<bool> used;
    vector<int> component;
    vector<int> order;

    explicit SCC(int vertex_count)
        : n(vertex_count), graph(vertex_count), reverse_graph(vertex_count) {}

    void add_edge(int from, int to) {
        graph[from].push_back(to);
        reverse_graph[to].push_back(from);
    }

    void forward_dfs(int vertex) {
        used[vertex] = true;
        for (int next : graph[vertex]) {
            if (!used[next]) forward_dfs(next);
        }
        order.push_back(vertex);
    }

    void reverse_dfs(int vertex, int component_id) {
        component[vertex] = component_id;
        for (int next : reverse_graph[vertex]) {
            if (component[next] == -1) reverse_dfs(next, component_id);
        }
    }

    int build() {
        used.assign(n, false);
        order.clear();
        for (int vertex = 0; vertex < n; ++vertex) {
            if (!used[vertex]) forward_dfs(vertex);
        }

        component.assign(n, -1);
        reverse(order.begin(), order.end());
        int component_count = 0;
        for (int vertex : order) {
            if (component[vertex] == -1) reverse_dfs(vertex, component_count++);
        }
        return component_count;
    }

    int operator[](int vertex) const {
        return component[vertex];
    }
};
