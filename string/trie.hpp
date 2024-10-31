#include"../template/template.hpp"

/*
文字列集合を管理する
未テスト

insert(string s)
文字列sを集合に追加する

erase(string s)
文字列sを集合から削除する

find(string s)
集合に含まれるもののうちsとの共通接頭辞で最長のノードを得る

prefix(string s)
集合に含まれる文字列のsとの最長共通接頭辞の長さ
*/

namespace Lib {
struct trie {
  using ci = pair<char, int>;
  struct Node {
    int par, depth;
    vector<ci> chi;
  };
  vector<Node> tr;
  trie() : tr(1) { tr[0] = {-1, 0, vector<ci>(0)}; }

  void insert(const string& s) {
    int n = s.size(), idx = 0;
    rep(i, n) {
      bool e = 0;
      for (auto [c, j] : tr[idx].chi) {
        if (c == s[i]) {
          idx = j;
          e = 1;
        }
      }
      if (!e) {
        tr[idx].chi.push_back({s[i], (int)tr.size()});
        tr.push_back(Node{idx, i, {}});
        idx = (int)tr.size() - 1;
      }
    }
  }
  Node find(const string& s) {
    int idx = 0, n = s.size();
    rep(i, n) {
      bool e = 0;
      for (auto [c, j] : tr[idx].chi) {
        if (c == s[i]) {
          idx = j;
          e = 1;
          break;
        }
      }
      if (!e) break;
    }
    return tr[idx];
  }
  int prefix(const string& s) { return find(s).depth; }
  bool erase(const string& s) {
    int idx = prefix(s), n = s.size();
    // 存在しない
    if (tr[idx].depth < (int)s.size()) return false;
    rep(ri, n) {
      int i = n - 1 - ri;
      if (!tr[idx].chi.empty()) break;
      idx = tr[idx].par;
      auto& v = tr[idx].chi;
      rep(j, v.size()) {
        if (v[j].first == s[i]) {
          swap(v[j], v.back());
          v.pop_back();
          break;
        }
      }
    }
    // 削除成功
    return true;
  }
};
}  // namespace Lib
