#pragma once

#include "../base.hpp"

/**
 * @brief 頂点間のポテンシャル差を管理する重み付き Union-Find
 *
 * unite(x, y, w) は potential(y) - potential(x) = w を追加する。
 * T は加減算、単位元 T{}、等値比較ができる型を想定する。
 */
template <class T>
class WeightedUnionFind {
public:
    explicit WeightedUnionFind(int n)
        : parent_or_size_(n, -1), diff_weight_(n, T{}) {}

    int leader(int x) {
        if (parent_or_size_[x] < 0) return x;
        const int parent = parent_or_size_[x];
        const int root = leader(parent);
        diff_weight_[x] += diff_weight_[parent];
        return parent_or_size_[x] = root;
    }

    T weight(int x) {
        leader(x);
        return diff_weight_[x];
    }

    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    /** potential(y) - potential(x) を返す。same(x,y) が true のときのみ有効。 */
    T diff(int x, int y) {
        assert(same(x, y));
        return weight(y) - weight(x);
    }

    /**
     * @return 新しく併合した、または既存制約と整合するなら true。
     *         既存制約と矛盾するなら false。
     */
    bool unite(int x, int y, T w) {
        w += weight(x);
        w -= weight(y);
        x = leader(x);
        y = leader(y);

        if (x == y) return w == T{};

        if (-parent_or_size_[x] < -parent_or_size_[y]) {
            swap(x, y);
            w = -w;
        }

        parent_or_size_[x] += parent_or_size_[y];
        parent_or_size_[y] = x;
        diff_weight_[y] = w;
        return true;
    }

    int size(int x) {
        return -parent_or_size_[leader(x)];
    }

private:
    vector<int> parent_or_size_;
    vector<T> diff_weight_;
};
