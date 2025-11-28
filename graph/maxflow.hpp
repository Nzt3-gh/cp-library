#include "../template/template.hpp"

/*
Dinic法により最大流を求める
add_edge(from,to,cap) from->to に 容量capの有向辺を追加する
flow(s,t) s->t 最大流を求める
edges() 全ての辺を (from,to,cap,flow) の形で得る
*/

namespace Lib {
struct mf_graph {
  struct _edge {
    int to, rev;
    ll cap;
  };
  struct edge {
    int from, to;
    ll cap, flow;
  };
  vector<array<int, 2>> pos;
  vector<vector<_edge>> graph;
  unsigned v_size;
  mf_graph(int n) : graph(n), v_size(n) {}
  void add_edge(int from, int to, ll cap) {
    pos.push_back({from, (int)ssize(graph[from])});
    graph[from].push_back(_edge({to, (int)ssize(graph[to]), cap}));
    graph[to].push_back(_edge({from, (int)ssize(graph[from]) - 1, 0}));
  }
  ll flow(int s, int t) {
    ll ret = 0;
    vector lev(v_size, -1);
    auto bfs = [&](int s) {
      fill(lev.begin(), lev.end(), -1);
      queue<int> q;
      lev[s] = 0;
      q.push(s);
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto e : graph[v]) {
          if (e.cap > 0 && lev[e.to] < 0) {
            lev[e.to] = lev[v] + 1;
            q.push(e.to);
          }
        }
      }
    };
    vector iter(v_size, 0);
    auto dfs = [&](auto self, int v, ll f) {
      if (v == t)
        return f;
      for (int &i = iter[v]; i < ssize(graph[v]); i++) {
        _edge &e = graph[v][i];
        if (e.cap > 0 && lev[v] < lev[e.to]) {
          ll d = self(self, e.to, min(f, e.cap));
          if (d > 0) {
            e.cap -= d;
            graph[e.to][e.rev].cap += d;
            return d;
          }
        }
      }
      return 0ll;
    };
    while (1) {
      bfs(s);
      if (lev[t] < 0)
        return ret;
      fill(iter.begin(), iter.end(), 0);
      ll f = 0;
      while ((f = dfs(dfs, s, LLONG_MAX)) > 0) {
        ret += f;
      }
    }
  }
  vector<edge> edges() {
    vector<edge> ret;
    for (auto i : pos) {
      auto e = graph[i[0]][i[1]], re = graph[e.to][e.rev];
      ret.push_back(edge({i[0], e.to, e.cap + re.cap, re.cap}));
    }
    return ret;
  }
};
} // namespace Lib