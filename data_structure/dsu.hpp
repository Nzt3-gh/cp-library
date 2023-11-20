#include "../template/template.hpp"

/*
Disjoint Set Union
経路圧縮とmerge by sizeにより
それぞれの操作を O(α(N))で行う
*/
namespace Lib {
struct DSU {
  vector<int> par, sz;
  DSU(int n) : par(n), sz(n) {
    fill(par.begin(), par.end(), -1);
    fill(sz.begin(), sz.end(), 1);
  }
  int leader(int a) {
    if (par[a] == -1) return a;
    return par[a] = leader(par[a]);
  }
  void merge(int a, int b) {
    a = leader(a), b = leader(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    par[a] = b;
    sz[b] += sz[a];
  }
  bool same(int a, int b) {
    a = leader(a), b = leader(b);
    return a == b;
  }
  int size(int v) {
    v = leader(v);
    return sz[v];
  }
};
}  // namespace Lib