#include "../template/template.hpp"

/*
強連結成分分解
add_edge (v,u): 償却O(1)
有向辺 (v->u) を追加する

scc: 頂点数V 辺数E について O(E+V)
強連結成分を求める
トポロジカルソート順に 強連結成分のvector を得る

verify https://judge.yosupo.jp/submission/173442
*/

namespace Lib {
struct scc_graph {
  vector<vector<int>> g;
  int sz;
  scc_graph(int n) : g(n), sz(n) {}
  void add_edge(int v, int u) {
    assert(v < sz && v >= 0);
    assert(u < sz && u >= 0);
    g[v].push_back(u);
  }
  vector<vector<int>> scc() {
    vector visited(sz, false);
    vector rev_g(sz, vector(0, 0));
    for (int i = 0; i < sz; i++) {
      for (auto j : g[i]) {
        rev_g[j].push_back(i);
      }
    }
    vector dfs(0, 0), e_idx(sz, 0), l(0, 0);
    for (int i = 0; i < sz; i++) {
      if (visited[i]) continue;
      visited[i] = 1;
      dfs.push_back(i);
      while (!dfs.empty()) {
        int v = dfs.back();
        dfs.pop_back();
        for (int &j = e_idx[v]; j < g[v].size(); j++) {
          if (!visited[g[v][j]]) {
            dfs.push_back(v);
            dfs.push_back(g[v][j]);
            visited[g[v][j]] = 1;
            break;
          }
        }
        if (e_idx[v] == g[v].size()) {
          l.push_back(v);
        }
      }
    }
    fill(visited.begin(), visited.end(), false);
    fill(e_idx.begin(), e_idx.end(), 0);
    reverse(l.begin(), l.end());
    vector ret(0, vector(0, 0));
    for (int i : l) {
      if (visited[i]) continue;
      visited[i] = 1;
      dfs.push_back(i);
      ret.push_back(vector(0, 0));
      while (!dfs.empty()) {
        int v = dfs.back();
        dfs.pop_back();
        for (int &j = e_idx[v]; j < rev_g[v].size(); j++) {
          if (!visited[rev_g[v][j]]) {
            dfs.push_back(v);
            dfs.push_back(rev_g[v][j]);
            visited[rev_g[v][j]] = 1;
            break;
          }
        }
        if (e_idx[v] == rev_g[v].size()) {
          ret.back().push_back(v);
        }
      }
    }
    return ret;
  }
};
}  // namespace Lib
