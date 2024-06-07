#include"../data_structure/dsu_rollback.hpp"

/*
辺の追加/削除を行い、2頂点の連結性クエリと連結成分数クエリに答える

merge(a,b):
2頂点 a,b をつなぐ無向辺を追加する
複数回同じa,bを指定すると多重辺になる

remove(a,b):
2頂点 a,b をつなぐ辺が存在するならばそのうち1つを削除する

connectivity(a,b):
現在2頂点 a,b が連結か判定する

num_of_components():
現在のグラフ全体の連結成分数を数える

execute(): O(Q log Q)
今までに入力したクエリを全て計算し、出力クエリの解答を順番に並べた列を返す
これ以降にクエリの追加を行うことも可能

*/

namespace Lib {
struct offline_dynamic_connectivity {
  using vi3 = array<int, 3>;
  vector<vi3> query;
  DSU_rollback uf;
  int n;
  offline_dynamic_connectivity(int _n) : n(_n), uf(_n) {}
  void merge(int a, int b) {
    if (a > b) swap(a, b);
    query.push_back({0, a, b});
  }
  void remove(int a, int b) {
    if (a > b) swap(a, b);
    query.push_back({1, a, b});
  }
  void connectivity(int a, int b) {
    if (a > b) swap(a, b);
    query.push_back({2, a, b});
  }
  void num_of_components() { query.push_back({3, 0, 0}); }
  vector<int> execute() {
    int segsize = 1, q = query.size();
    while (segsize < q) segsize <<= 1;
    vector es(segsize * 2, vector(0, array<int, 2>()));
    map<array<int, 2>, int> edge_time, edge_cnt;
    auto add_edge = [&segsize](array<int, 2> e, int L, int R,
                               vector<vector<array<int, 2>>>& es) {
      int l = L + segsize, r = R + segsize;
      while (l < r) {
        if (l % 2) es[l++].push_back(e);
        if (r % 2) es[--r].push_back(e);
        l /= 2, r /= 2;
      }
    };
    for (int i = 0; i < q; i++) {
      auto [t, a, b] = query[i];
      array<int, 2> e = {a, b};
      if (t == 0) {
        if (edge_cnt[e] == 0) {
          edge_time[e] = i;
        }
        edge_cnt[e] += 1;
      } else if (t == 1) {
        if (edge_cnt[e] <= 0) continue;
        edge_cnt[e] -= 1;
        if (edge_cnt[e] == 0) {
          add_edge(e, edge_time[e], i, es);
          edge_time[e] = -1;
        }
      }
    }
    for (auto [e, c] : edge_time) {
      if (c == -1) continue;
      add_edge(e, c, q + 1, es);
    }
    stack<int, vector<int>> dfs;
    vector dfs_d(segsize, -1);
    int c_num = n;
    dfs.push(0);
    vector ret(0, 0);
    while (!dfs.empty()) {
      int v = dfs.top();
      dfs.pop();
      if (v >= segsize) {
        for (auto e : es[v]) {
          if (uf.merge(e[0], e[1])) c_num -= 1;
        }
        if (v - segsize < q) {
          int v2 = v - segsize;
          if (query[v2][0] == 2) {
            ret.push_back(uf.same(query[v2][1], query[v2][2]));
          } else if (query[v2][0] == 3) {
            ret.push_back(c_num);
          }
        }
        for (int i = 0; i < (int)es[v].size(); i++) {
          if (uf.undo()) c_num += 1;
        }
        continue;
      }
      if (dfs_d[v] == -1) {
        for (auto e : es[v]) {
          if (uf.merge(e[0], e[1])) c_num -= 1;
        }
      }
      for (int& i = ++dfs_d[v]; i < 2; i++) {
        dfs.push(v);
        dfs.push(v * 2 + i);
        break;
      }
      if (dfs_d[v] == 2) {
        for (int i = 0; i < (int)es[v].size(); i++) {
          if (uf.undo()) {
            c_num += 1;
          }
        }
      }
    }
    return ret;
  }
};
}  // namespace Lib