#include "../template/template.hpp"

/*
区間モノイド積を計算するデータ構造
非可換でもOK

数列Aについて

set(p,v): log(n)
A[p]=v

prod(l,r): log(n)
A[l] * A[l+1] * … * A[r-1] を計算する

max_right<decltype(F)>(L,F): log(n)
Fは単調とすると
F(A[L] * A[L+1] * … * A[R-1]) = true となる最大のRを得る

min_left<decltype(F)>(R,F): log(n)
Fは単調とすると
F(A[L] * A[L+1] * … * A[R-1]) = true となる最小のLを得る

verify
  https://atcoder.jp/contests/abc217/tasks/abc217_d
  https://judge.yosupo.jp/submission/173390
*/
namespace Lib {
template <class S, auto op, auto e>
struct segtree {
  int size, _n;
  vector<S> seg;
  segtree(int n) {
    _n = n;
    size = 1;
    while (size < n) size <<= 1;
    seg = vector<S>(size * 2, e());
  }
  void set(int p, S val) {
    p += size;
    seg[p] = val;
    while (p /= 2) {
      seg[p] = op(seg[p * 2], seg[p * 2 + 1]);
    }
  }
  S prod(int l, int r) {
    S retL = e(), retR = e();
    for (l += size, r += size; l < r; l /= 2, r /= 2) {
      if (l % 2) retL = op(retL, seg[l++]);
      if (r % 2) retR = op(seg[--r], retR);
    }
    return op(retL, retR);
  }
  S get(int p) { return seg[p + size]; }
  template <class F>
  int max_right(int L, F f) {
    L += size;
    S sm = e();
    do {
      while (L % 2 == 0) L /= 2;
      if (!f(op(sm, seg[L]))) {
        while (L < size) {
          L *= 2;
          if (f(op(sm, seg[L]))) {
            sm = op(sm, seg[L]);
            L++;
          }
        }
        return L - size;
      }
      sm = op(sm, seg[L]);
      L++;
    } while ((L & -L) != L);
    return _n;
  }

  template <class F>
  int min_left(int R, F f) {
    R += size;
    S sm = e();
    do {
      R--;
      while (R > 1 && R % 2 == 1) R /= 2;
      if (!f(op(seg[R], sm))) {
        while (R < size) {
          R = R * 2 + 1;
          if (f(op(seg[R], sm))) {
            sm = op(seg[R], sm);
            R--;
          }
        }
        return R + 1 - size;
      }
      sm = op(seg[R], sm);
    } while ((R & -R) != R);
    return 0;
  }
};
}  // namespace Lib