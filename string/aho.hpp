#include "../template/template.hpp"

/*
Aho-Corasick(英子文字用)

文字列Xを管理し、そのsuffixに検索文字列が含まれるか判定する

void add (string)
検索文字列 S を追加する

void build ()
検索文字列の追加を終了し、suffix linkを構築する

void clear()
内部で管理している文字列を全消去する

void push(char)
内部の文字列の末尾に文字cを追加する

int check()
suffixに検索文字列が含まれているか判定

Aho-Corasick (hash可能数値型用)
void add(vector<S>)
void build()
void clear()
void push(S)
int check()
*/
namespace Lib {
struct Aho_lc {
  int X;
  bool init;
  static constexpr int sigma = 26;
  vector<array<int, sigma>> to;
  vector<int> cnt, link;
  Aho_lc() : cnt(1), to(1), init(0) { rep(i, sigma) to[0][i] = -1; }
  void add(const string &s) {
    int v = 0;
    for (char i : s) {
      i -= 'a';
      if (to[v][i] == -1) {
        to[v][i] = ssize(to);
        to.push_back(array<int, sigma>());
        cnt.push_back(0);
        rep(j, sigma) to.back()[j] = -1;
      }
      v = to[v][i];
    }
    cnt[v]++;
  }
  void build() {
    assert(!init);
    init = 1;
    link.assign(ssize(to), -1);
    queue<int> bfs;
    bfs.push(0);
    while (!bfs.empty()) {
      int v = bfs.front();
      bfs.pop();
      rep(i, sigma) {
        int u = to[v][i];
        if (u == -1)
          continue;
        link[u] = _link_search(link[v], i);
        cnt[u] += cnt[link[u]];
        bfs.push(u);
      }
    }
    clear();
  }
  int _link_search(int v, int c) {
    while (v != -1) {
      if (to[v][c] != -1)
        return to[v][c];
      v = link[v];
    }
    return 0;
  }
  void push(char c) {
    c -= 'a';
    while (X != -1) {
      if (to[X][c] == -1)
        X = link[X];
      else {
        X = to[X][c];
        break;
      }
    }
    if (X < 0)
      X = 0;
  }
  void clear() { X = 0; }
  int check() { return cnt[X]; }
};

template <class S> struct Aho {
  int X;
  bool init;
  using ump = unordered_map<S, int>;
  vector<ump> to;
  vector<int> cnt, link;
  Aho() : cnt(1), to(1), init(0) {}
  void add(const vector<S> &s) {
    int v = 0;
    for (S i : s) {
      if (!to[v].contains(i)) {
        to[v][i] = ssize(to);
        to.push_back(ump());
        cnt.push_back(0);
      }
      v = to[v][i];
    }
    cnt[v]++;
  }
  void build() {
    assert(!init);
    init = 1;
    link.assign(ssize(to), -1);
    queue<int> bfs;
    bfs.push(0);
    while (!bfs.empty()) {
      int v = bfs.front();
      bfs.pop();
      for (auto [k, u] : to[v]) {
        link[u] = _link_search(link[v], k);
        cnt[u] += cnt[link[u]];
        bfs.push(u);
      }
    }
    clear();
  }
  int _link_search(int v, S c) {
    while (v != -1) {
      if (to[v].contains(c))
        return to[v][c];
      v = link[v];
    }
    return 0;
  }
  void push(S c) {
    while (X != -1) {
      if (!to[X].contains(c))
        X = link[X];
      else {
        X = to[X][c];
        break;
      }
    }
    if (X < 0)
      X = 0;
  }
  void clear() { X = 0; }
  int check() { return cnt[X]; }
};
} // namespace Lib