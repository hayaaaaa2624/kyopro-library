#pragma once

#include "../base.hpp"

/**
 * @brief Dinic 法による最大流。
 *
 * add_edge(from, to, capacity) で有向辺を追加し、max_flow(s, t) で最大流を求める。
 * 一般の計算量は O(V^2 E)。容量は long long。
 */
struct Dinic {
    struct Edge {
        int to;
        int reverse_index;
        ll capacity;
    };

    int n;
    vector<vector<Edge>> graph;
    vector<int> level;
    vector<int> iterator;

    explicit Dinic(int vertex_count)
        : n(vertex_count), graph(vertex_count), level(vertex_count), iterator(vertex_count) {}

    void add_edge(int from, int to, ll capacity) {
        graph[from].push_back({to, static_cast<int>(graph[to].size()), capacity});
        graph[to].push_back({from, static_cast<int>(graph[from].size()) - 1, 0});
    }

    void build_level_graph(int source) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[source] = 0;
        que.push(source);

        while (!que.empty()) {
            const int vertex = que.front();
            que.pop();
            for (const Edge& edge : graph[vertex]) {
                if (edge.capacity <= 0 || level[edge.to] != -1) continue;
                level[edge.to] = level[vertex] + 1;
                que.push(edge.to);
            }
        }
    }

    ll send_flow(int vertex, int sink, ll flow_limit) {
        if (vertex == sink) return flow_limit;
        for (int& i = iterator[vertex]; i < static_cast<int>(graph[vertex].size()); ++i) {
            Edge& edge = graph[vertex][i];
            if (edge.capacity <= 0 || level[vertex] >= level[edge.to]) continue;

            const ll flow = send_flow(edge.to, sink, min(flow_limit, edge.capacity));
            if (flow == 0) continue;
            edge.capacity -= flow;
            graph[edge.to][edge.reverse_index].capacity += flow;
            return flow;
        }
        return 0;
    }

    ll max_flow(int source, int sink) {
        constexpr ll INF = 1LL << 60;
        ll total_flow = 0;
        while (true) {
            build_level_graph(source);
            if (level[sink] == -1) return total_flow;
            fill(iterator.begin(), iterator.end(), 0);
            while (const ll flow = send_flow(source, sink, INF)) {
                total_flow += flow;
            }
        }
    }
};
