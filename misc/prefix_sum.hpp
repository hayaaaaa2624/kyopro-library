#pragma once

#include "../base.hpp"

/**
 * @brief 一次元累積和。query(l, r) は半開区間 [l, r) の和を返す。
 * @note 構築 O(N)、取得 O(1)
 */
template <class T>
class PrefixSum {
public:
    PrefixSum() = default;

    explicit PrefixSum(const vector<T>& values)
        : sum_(values.size() + 1, T{}) {
        for (size_t i = 0; i < values.size(); ++i) {
            sum_[i + 1] = sum_[i] + values[i];
        }
    }

    T query(int left, int right) const {
        assert(0 <= left && left <= right && right < static_cast<int>(sum_.size()));
        return sum_[right] - sum_[left];
    }

    T prefix(int right) const {
        assert(0 <= right && right < static_cast<int>(sum_.size()));
        return sum_[right];
    }

private:
    vector<T> sum_;
};

/**
 * @brief 二次元累積和。query(y1, x1, y2, x2) は [y1,y2)×[x1,x2) の和。
 * @note 構築 O(HW)、取得 O(1)
 */
template <class T>
class PrefixSum2D {
public:
    PrefixSum2D() = default;

    explicit PrefixSum2D(const vector<vector<T>>& grid) {
        const int height = static_cast<int>(grid.size());
        const int width = height == 0 ? 0 : static_cast<int>(grid[0].size());
        sum_.assign(height + 1, vector<T>(width + 1, T{}));

        for (int y = 0; y < height; ++y) {
            assert(static_cast<int>(grid[y].size()) == width);
            for (int x = 0; x < width; ++x) {
                sum_[y + 1][x + 1] = grid[y][x] + sum_[y][x + 1]
                                      + sum_[y + 1][x] - sum_[y][x];
            }
        }
    }

    T query(int y1, int x1, int y2, int x2) const {
        assert(0 <= y1 && y1 <= y2 && y2 < static_cast<int>(sum_.size()));
        assert(!sum_.empty());
        assert(0 <= x1 && x1 <= x2 && x2 < static_cast<int>(sum_[0].size()));
        return sum_[y2][x2] - sum_[y1][x2] - sum_[y2][x1] + sum_[y1][x1];
    }

private:
    vector<vector<T>> sum_;
};
