#include "../template/template.hpp"

/*
単純グラフの橋を検出する

lowlink(G): O(N+M)
ordとlowを計算する

get_bridge(G,ord,low): O(N+M)
ordとlowから橋を得る

LCには 非単純グラフの問題がありますが、このライブラリでは解けません
絶対に切断されない辺を縮約するなりしてください

*/
namespace Lib {
pair<vector<int>, vector<int>> lowlink(const vector<vector<int>> &G) {
  int N = ssize(G);
  vector vst(N, false);
  vector wE(N, 0), d(N, 0);
  for (int i = 0; i < N; i++) {
    d[i] = ssize(G[i]);
  }
  vector ord(N, 0), low(N, N + 1), p(N, -1);
  int cntord = 0;
  for (int i = 0; i < N; i++) {
    if (vst[i])
      continue;
    ord[i] = cntord++;
    vst[i] = 1;
    vector dfs(0, 0);
    dfs.push_back(i);
    while (!dfs.empty()) {
      int v = dfs.back();
      dfs.pop_back();
      for (int &j = wE[v]; j < d[v]; j++) {
        if (!vst[G[v][j]]) {
          ord[G[v][j]] = cntord++;
          p[G[v][j]] = v;
          vst[G[v][j]] = 1;
          dfs.push_back(v);
          dfs.push_back(G[v][j]);
          break;
        } else if (G[v][j] != p[v]) {
          low[v] = min(low[v], ord[G[v][j]]);
        }
      }
      if (p[v] != -1) {
        low[p[v]] = min(low[p[v]], low[v]);
      }
    }
  }
  return make_pair(ord, low);
}

vector<array<int, 2>> get_bridge(const vector<vector<int>> &G,
                                 const vector<int> &ord,
                                 const vector<int> &low) {
  vector<array<int, 2>> bridge;
  for (int i = 0; i < ssize(G); i++) {
    for (auto j : G[i]) {
      if (ord[i] < low[j]) {
        bridge.push_back({i, j});
      }
    }
  }
  return bridge;
}
} // namespace Lib
