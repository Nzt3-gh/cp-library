#include "../template/template.hpp"

/*
Disjoint Set Union + Potential

leader: O(α(N))
連結成分の代表を得る

merge: O(α(N))
2つの頂点a,bの属する連結成分を合併し、pot[a]-pot[b]=pとする
元々a,bが同じ連結成分に属する場合は何もしない

same; O(α(N))
2つの頂点a,bが同一の連結成分に属するか判定する

size: O(α(N))
連結成分の大きさを得る

get_pot: O(α(N))
leaderを0としたときのpot[v]を得る

verify https://atcoder.jp/contests/abc328/submissions/47773850

*/
namespace Lib {
struct DSU_potential {
  vector<int> par, sz;
  vector<ll> pot;
  DSU_potential(int n) : par(n), sz(n), pot(n) {
    fill(par.begin(), par.end(), -1);
    fill(sz.begin(), sz.end(), 1);
  }
  int leader(int a) {
    if (par[a] == -1) return a;
    int p = par[a];
    par[a] = leader(par[a]);
    pot[a] += pot[p];
    return par[a];
  }
  void merge(int a, int b, ll p) {
    ll pa = get_pot(a), pb = get_pot(b);
    a = leader(a), b = leader(b);
    if (a == b) return;
    if (sz[a] > sz[b]) {
      swap(a, b);
      swap(pa, pb);
      p *= -1;
    }
    p = p - pa + pb;
    par[a] = b;
    pot[a] = p;
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
  ll get_pot(int v) {
    if (par[v] == -1) return 0ll;
    leader(v);
    return pot[v];
  }
};
}  // namespace Lib