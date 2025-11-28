#include "../template/template.hpp"

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
struct Trie {
  struct Node {
    int par, depth, cnt;
    map<char, int> to;
  };
  static constexpr char endsymb = '!';
  vector<Node> tr;
  Trie() : tr(1) { tr[0] = {-1, 0, 0, {}}; }
  void insert(string s) {
    s += endsymb;
    int v = 0, d = 0;
    for (auto i : s) {
      tr[v].cnt++;
      d++;
      if (!tr[v].to.contains(i)) {
        tr[v].to[i] = ssize(tr);
        tr.push_back(Node{v, d, 0, {}});
      }
      v = tr[v].to[i];
    }
    tr[v].cnt++;
  }
  Node find(string s) {
    s += endsymb;
    int v = 0;
    for (auto i : s) {
      if (!tr[v].to.contains(i))
        return tr[v];
      v = tr[v].to[i];
    }
    return tr[v];
  }
  int prefix(string s) {
    int ret = find(s).depth;
    if (ret > ssize(s))
      ret--;
    return ret;
  }
  bool contains(string s) { return find(s).depth == ssize(s) + 1; }
  bool erase(string s) {
    if (!contains(s))
      return false;
    s += endsymb;
    int v = 0;
    for (auto i : s) {
      tr[v].cnt--;
      v = tr[v].to[i];
    }
    tr[v].cnt--;
    return true;
  }
};
} // namespace Lib