#pragma once

#include "../base.hpp"

/**
 * @brief 関数グラフ上の k 回遷移を高速化するダブリング
 *
 * next[v] は頂点 v から1回進んだ頂点。
 * max_steps 以下の遷移に対応する。
 */
class Doubling {
public:
    Doubling(const vector<int>& next, unsigned long long max_steps) {
        int levels = 1;
        while (levels < 64 && (max_steps >> levels) != 0) ++levels;
        table_.assign(levels, vector<int>(next.size()));
        table_[0] = next;

        for (int level = 1; level < levels; ++level) {
            for (size_t v = 0; v < next.size(); ++v) {
                table_[level][v] = table_[level - 1][table_[level - 1][v]];
            }
        }
    }

    /** 頂点 start から steps 回進んだ頂点を返す。O(log steps) */
    int jump(int start, unsigned long long steps) const {
        int current = start;
        int level = 0;
        while (steps > 0) {
            assert(level < static_cast<int>(table_.size()));
            if (steps & 1ULL) current = table_[level][current];
            steps >>= 1;
            ++level;
        }
        return current;
    }

private:
    vector<vector<int>> table_;
};
