#include "../template/template.hpp"

/*
Disjoint Set Union + Rollback

leader: O(log(N))
連結成分の代表を得る

merge: O(log(N))
2つの頂点a,bの属する連結成分を合併する

same; O(log(N))
2つの頂点a,bが同一の連結成分に属するか判定する

size: O(log(N))
連結成分の大きさを得る

undo: O(1)
直前のmergeを取り消す
mergeを行なっていない場合は未定義

*/

namespace Lib {
struct DSU_rollback {
  vector<int> par, sz;
  stack<array<int, 3>> his;
  DSU_rollback(int n) : par(n), sz(n) {
    fill(par.begin(), par.end(), -1);
    fill(sz.begin(), sz.end(), 1);
  }
  int leader(int a) {
    if (par[a] == -1) return a;
    return leader(par[a]);
  }
  void merge(int a, int b) {
    a = leader(a), b = leader(b);
    if (a == b) {
      his.push({-1, -1, -1});
      return;
    }
    if (sz[a] > sz[b]) swap(a, b);
    his.push({a, b, sz[a]});
    par[a] = b;
    sz[b] += sz[a];
  }
  bool same(int a, int b) {
    a = leader(a), b = leader(b);
    return a == b;
  }
  void undo() {
    auto [c, p, s] = his.top();
    if (c == -1) return;
    his.pop();
    par[c] = -1;
    sz[c] = s;
    sz[p] -= s;
  }
  int size(int v) {
    v = leader(v);
    return sz[v];
  }
};
}  // namespace Lib