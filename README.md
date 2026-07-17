# Kyopro Library

C++17 以降で使える、競技プログラミング向けの個人ライブラリです。各ヘッダは単独で include でき、`library/all.hpp` から一括で読み込むこともできます。

## 使い方

### 必要な機能だけ読み込む

```cpp
#include "library/data_structure/unionfind.hpp"

int main() {
    UnionFind uf(5);
    uf.unite(0, 1);
    cout << uf.same(0, 1) << '\n';
}
```

### 全ライブラリを読み込む

```cpp
#include "library/all.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 解答を書く
}
```

## ディレクトリ構成

```text
library/
├── base.hpp
├── all.hpp
├── data_structure/
├── graph/
├── math/
├── misc/
└── string/
```

## 収録アルゴリズム

| 分類 | ファイル | 内容 | 主な計算量 |
|---|---|---|---|
| データ構造 | `bit.hpp` | Binary Indexed Tree | 更新・区間和 `O(log N)` |
| データ構造 | `segmenttree.hpp` | セグメント木 | 更新・区間取得 `O(log N)` |
| データ構造 | `unionfind.hpp` | Union-Find | 償却 `O(alpha(N))` |
| グラフ | `bfs.hpp` | 無重み最短距離 | `O(V + E)` |
| グラフ | `dfs.hpp` | 深さ優先探索 | `O(V + E)` |
| グラフ | `dijkstra.hpp` | 非負辺最短路 | `O((V + E) log V)` |
| グラフ | `bellman_ford.hpp` | 負辺対応最短路 | `O(VE)` |
| グラフ | `topological_sort.hpp` | トポロジカルソート | `O(V + E)` |
| グラフ | `scc.hpp` | 強連結成分分解 | `O(V + E)` |
| グラフ | `lca.hpp` | Lowest Common Ancestor | 構築 `O(N log N)`、取得 `O(log N)` |
| グラフ | `maximumflow.hpp` | Dinic 法 | 一般に `O(V^2E)` |
| 数学 | `factorial.hpp` | 素数 mod 上の階乗・逆階乗 | 構築 `O(N)`、取得 `O(1)` |
| 数学 | `combination.hpp` | 素数 mod 上の組合せ nCr | 構築 `O(N)`、取得 `O(1)` |
| 数学 | `permutation.hpp` | 素数 mod 上の順列 nPr | 構築 `O(N)`、取得 `O(1)` |
| 数学 | `homogeneous_combination.hpp` | 素数 mod 上の重複組合せ nHr | 構築 `O(N)`、取得 `O(1)` |
| 数学 | `eratosthenes.hpp` | 素数列挙 | `O(N log log N)` |
| 数学 | `gcd.hpp` / `lcm.hpp` | 最大公約数・最小公倍数 | `O(log min(a,b))` |
| 数学 | `modpow.hpp` | mod 累乗 | `O(log n)` |
| 数学 | `moddiv.hpp` | 素数 mod での除算 | `O(log m)` |
| 文字列 | `kmp.hpp` | KMP 法 | 構築・検索 `O(N + M)` |
| 文字列 | `rollinghash.hpp` | Rolling Hash | 構築 `O(N)`、取得 `O(1)` |
| 文字列 | `z_algorithm.hpp` | Z algorithm | `O(N)` |
| その他 | `compress.hpp` | 座標圧縮 | `O(N log N)` |
| その他 | `lis.hpp` | 最長増加部分列の長さ | `O(N log N)` |

## 階乗・組合せ・順列の使用例

必要な機能のヘッダだけを読み込みます。

```cpp
#include "library/math/combination.hpp"

int main() {
    Combination<> comb(200000);  // 998244353 を使用
    cout << comb.combination(5, 2) << '\n';  // 10
}
```

```cpp
#include "library/math/permutation.hpp"

Permutation<> perm(200000);
cout << perm.permutation(5, 2) << '\n';  // 20
```

```cpp
#include "library/math/homogeneous_combination.hpp"

HomogeneousCombination<> homogeneous(200000);
cout << homogeneous.homogeneous(3, 2) << '\n';  // 6
```

```cpp
#include "library/math/factorial.hpp"

Factorial<> fact(200000);
cout << fact.factorial(5) << '\n';          // 120
cout << fact.inverse_factorial(5) << '\n';  // (5!)^{-1}
```

`1000000007` など別の素数 mod を使う場合はテンプレート引数で指定します。

```cpp
Combination<MOD1E9P7> comb(200000);
```

前計算範囲は、`combination(n, r)` と `permutation(n, r)` では `n` 以上、`homogeneous(n, r)` では `n + r - 1` 以上にしてください。

## 提出用コードへの展開

`expand.py` は、ソース内のローカル `#include "..."` を再帰的に展開します。

```bash
python expand.py main.cpp -o expanded.cpp
```

出力先を省略すると標準出力へ表示します。

```bash
python expand.py main.cpp
```

## 注意事項

- `dijkstra` は負辺を扱えません。
- `bellman_ford` は現在、負閉路の検出結果を返しません。
- `moddiv(a, b, m)` は `m` が素数で、`b` が `m` の倍数でない場合を前提とします。
- `Factorial<Mod>`、`Combination<Mod>`、`Permutation<Mod>`、`HomogeneousCombination<Mod>` は `Mod` が素数で、前計算範囲が `Mod` 未満であることを前提とします。
- `RollingHash` はハッシュ衝突の可能性があります。
- `dfs`、`LCA`、`SCC`、`Dinic` は再帰を使うため、非常に深い入力ではスタックに注意してください。

## コンパイル例

```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o main
```
