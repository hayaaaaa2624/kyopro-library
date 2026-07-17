#pragma once

#include "../base.hpp"

/**
 * @brief unsigned long long の自然オーバーフローを使う Rolling Hash。
 * @note 衝突の可能性はゼロではない。get(left, right) は [left, right)。
 */
struct RollingHash {
    static constexpr ull base = 100000007ULL;
    vector<ull> hash;
    vector<ull> power;

    explicit RollingHash(const string& text) : hash(text.size() + 1), power(text.size() + 1, 1) {
        for (int i = 0; i < static_cast<int>(text.size()); ++i) {
            hash[i + 1] = hash[i] * base + static_cast<unsigned char>(text[i]);
            power[i + 1] = power[i] * base;
        }
    }

    ull get(int left, int right) const {
        return hash[right] - hash[left] * power[right - left];
    }
};
