#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t;
using Graph = vector<vector<int>>;

template <typename T>
using vc = vector<T>;

#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define rrep(i, a, b) for (int i = (a); i > (b); --i)
#define ALL(a) (a).begin(), (a).end()

inline constexpr ll MOD = 998244353;
inline constexpr ll MOD1E9P7 = 1000000007;
inline constexpr int dx[4] = {1, -1, 0, 0};
inline constexpr int dy[4] = {0, 0, 1, -1};

/** a を b 以上に更新する。更新したとき true を返す。 */
template <class A, class B>
bool chmax(A& a, const B& b) {
    if (a >= b) return false;
    a = b;
    return true;
}

/** a を b 以下に更新する。更新したとき true を返す。 */
template <class A, class B>
bool chmin(A& a, const B& b) {
    if (a <= b) return false;
    a = b;
    return true;
}
