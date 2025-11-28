#include "../template/template.hpp"
/*
遅延セグメント木

lazy_segtree<
S: モノイドの型
op: モノイド演算
e: Sの単位元
F: 作用の型
mapping: 作用fのモノイドsへの適用 (f,s)
composition: 作用fの作用gへの適用
id: Fの単位作用
>

prod(l,r): log(n)
区間[l,r)のモノイド積

get(p): log(n)
位置pの要素

apply(l,r,f): log(n)
区間[l,r)への作用fの適用
*/

namespace Lib {
template <class S, auto op, auto e, class F, auto mapping, auto composition,
          auto id>
struct lazy_segtree {
  vector<F> lazy;
  vector<S> val;
  int sz, segsize, height;
  lazy_segtree() : lazy_segtree(0) {}
  lazy_segtree(int n) : lazy_segtree(vector<S>(n, e())) {}
  lazy_segtree(const vector<S> &A) : sz(ssize(A)) {
    segsize = 1;
    height = 0;
    while (sz > segsize)
      segsize <<= 1, height += 1;
    val = vector<S>(2 * segsize, e());
    lazy = vector<F>(2 * segsize, id());
    for (int i = 0; i < sz; i++) {
      val[i + segsize] = A[i];
    }
    for (int i = segsize - 1; i > 0; i--) {
      val[i] = op(val[i * 2], val[i * 2 + 1]);
    }
  }
  void set(int p, S v) {
    p += segsize;
    for (int i = height; i >= 1; i--)
      update(p >> i);
    val[p] = v;
    for (int i = 1; i <= height; i++) {
      val[p >> i] = op(val[p >> (i + 1)], val[(p >> (i + 1)) + 1]);
    }
  }
  S get(int p) { return prod(p, p + 1); }
  void apply(int L, int R, F f, int k = 1, int btm = 0, int top = -1) {
    if (top == -1)
      top = segsize;
    update(k);
    if (R <= btm || L >= top)
      return;
    if (L <= btm && top <= R) {
      lazy[k] = f;
      update(k);
      return;
    }
    int mid = (btm + top) / 2;
    apply(L, R, f, k * 2, btm, mid);
    apply(L, R, f, k * 2 + 1, mid, top);
    val[k] = op(val[k * 2], val[k * 2 + 1]);
  }
  S prod(int L, int R, int k = 1, int btm = 0, int top = -1) {
    if (top == -1)
      top = segsize;
    update(k);
    if (R <= btm || L >= top)
      return e();
    if (L <= btm && top <= R)
      return val[k];
    int mid = (btm + top) / 2;
    S ret = op(prod(L, R, k * 2, btm, mid), prod(L, R, k * 2 + 1, mid, top));
    val[k] = op(val[k * 2], val[k * 2 + 1]);
    return ret;
  }
  void update(int k) {
    val[k] = mapping(lazy[k], val[k]);
    if (k < segsize) {
      lazy[k * 2] = composition(lazy[k], lazy[k * 2]);
      lazy[k * 2 + 1] = composition(lazy[k], lazy[k * 2 + 1]);
    }
    lazy[k] = id();
  }
  template <class G> void min_left(G f) {}
  template <class G> void max_right(G f) {}
};
} // namespace Lib
