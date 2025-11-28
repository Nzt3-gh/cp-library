#include "../template/template.hpp"

/*
非負整数集合を管理する

void insert(v)
vを集合に追加する

void erase(v)
vを集合から削除する

bool contains(v)
vが集合に含まれているか確認する

ll xor_min(x)
集合に含まれる値sであってs xor xが最小となるものを得る

ll xor_kth_min(x,k)
集合に含まれる値sであってs xor xがk番目に小さいものを得る
*/

namespace Lib {
struct binary_trie {
  struct Node {
    int chi[2];
    int par, cnt;
  };
  static const int TRIE_LEN = 31;
  vector<Node> tr;
  binary_trie() : tr(1) { tr[0] = Node{{-1, -1}, -1, 0}; }
  void insert(ll v) {
    if (contains(v))
      return;
    int idx = 0;
    for (int i = TRIE_LEN - 1; i >= 0; i--) {
      tr[idx].cnt++;
      if (tr[idx].chi[v >> i & 1] == -1) {
        tr[idx].chi[v >> i & 1] = ssize(tr);
        tr.push_back(Node{{-1, -1}, idx, 0});
      }
      idx = tr[idx].chi[v >> i & 1];
    }
    tr[idx].cnt++;
  }
  bool contains(ll v) {
    int idx = 0;
    for (int i = TRIE_LEN; i--;) {
      if (tr[idx].chi[v >> i & 1] == -1)
        return false;
      idx = tr[idx].chi[v >> i & 1];
    }
    return tr[idx].cnt > 0;
  }
  bool erase(ll v) {
    if (!contains(v))
      return false;
    int idx = 0;
    for (int i = TRIE_LEN; i--;) {
      tr[idx].cnt--;
      idx = tr[idx].chi[v >> i & 1];
    }
    tr[idx].cnt--;
    return true;
  }
  ll xor_min(ll x) {
    assert(tr[0].cnt > 0);
    ll ret = 0;
    int idx = 0;
    for (int i = TRIE_LEN; i--;) {
      int idx2 = tr[idx].chi[x >> i & 1];
      if (idx2 != -1 && tr[idx2].cnt) {
        idx = idx2;
      } else {
        idx = tr[idx].chi[!(x >> i & 1)];
        ret |= 1ll << i;
      }
    }
    return ret;
  }
  ll xor_kth_min(ll x, int k) {
    assert(tr[0].cnt >= k);
    ll ret = 0;
    int idx = 0;
    for (int i = TRIE_LEN; i--;) {
      int idx2 = tr[idx].chi[x >> i & 1];
      if (idx2 != -1 && tr[idx2].cnt >= k) {
        idx = idx2;
      } else {
        k -= tr[idx2].cnt;
        idx = tr[idx].chi[!(x >> i & 1)];
        ret |= 1ll << i;
      }
    }
    return ret;
  }
  int size() { return tr[0].cnt; }
};
} // namespace Lib