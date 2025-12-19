#include "../template/template.hpp"

namespace Lib {
template <class S, auto op, auto e> struct dynamic_segtree {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");
  static const ll K = 62;
  static const ll segsize = 1ll << K;
  dynamic_segtree() : root(), N(0) {};
  S get(ll p) { return _get(p); }
  S prod(ll l, ll r) { return _prod(root, l, r); }
  void set(ll p, S val) { return _set(root, p, val); }
  size_t size() { return N; }

private:
  struct node;
  using node_ptr = node *;
  struct node {
    S val;
    node_ptr left, right;
    node() : val(e()), left(nullptr), right(nullptr) {}
  };
  node_ptr root;
  ll N;

  S _prod(node_ptr &nd, ll l, ll r, ll btm = 0, ll top = segsize) {
    if (!nd)
      return e();
    if (r <= btm || top <= l)
      return e();
    if (l <= btm && top <= r)
      return nd->val;
    ll mid = (btm + top) / 2;
    return op(nd->left ? _prod(nd->left, l, r, btm, mid) : e(),
              nd->right ? _prod(nd->right, l, r, mid, top) : e());
  }

  S _get(ll p) {
    node_ptr nd = root;
    for (ll i = K - 1; i >= 0; i--) {
      if (!nd)
        return e();
      if (p >> i & 1)
        nd = nd->right;
      else
        nd = nd->left;
    }
    if (!nd)
      return e();
    return nd->val;
  }

  void _set(node_ptr &nd, ll p, S val, ll btm = 0, ll top = segsize) {
    if (p + 1 <= btm || top <= p)
      return;
    if (!nd) {
      nd = new node();
      if (btm + 1 == top)
        N++;
    }
    if (p <= btm && top <= p + 1) {
      nd->val = val;
      return;
    }
    ll mid = (btm + top) / 2;
    _set(nd->left, p, val, btm, mid);
    _set(nd->right, p, val, mid, top);

    nd->val = op((nd->left ? nd->left->val : e()),
                 (nd->right ? nd->right->val : e()));
  }
};
} // namespace Lib