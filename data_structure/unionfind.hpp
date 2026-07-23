#pragma once

#include "../base.hpp"

/**
 * @brief Union-Find（Disjoint Set Union）
 *
 * 要素の連結判定と集合の併合をほぼ定数時間で行う。
 * 償却計算量は O(alpha(N))。
 */
struct UnionFind {
    vector<int> parent;
    vector<int> size_data;

    explicit UnionFind(int n) : parent(n), size_data(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int root(int x) {
        if (parent[x] == x) return x;
        return parent[x] = root(parent[x]);
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    bool unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;

        if (size_data[x] < size_data[y]) swap(x, y);
        parent[y] = x;
        size_data[x] += size_data[y];
        return true;
    }

    int size(int x) {
        return size_data[root(x)];
    }
};
