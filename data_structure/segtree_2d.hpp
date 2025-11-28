#include "../template/template.hpp"

/*
矩形モノイド積を計算するデータ構造
できれば可換の方が安心

segtree_2d(h,w): O(h,w)
eで初期化されたh * w の二次元配列を生成する

set(x,y,S v): O(log H log W)
(x,y)を値vに変更する

prod(h1,w1,h2,w2): O(log h log W)
(h1,w1)を左上、(h2,w2)を右下とする矩形領域 [h1,h2) * [w1,w2) の積を計算する
*/
namespace Lib {
template <class S, auto op, auto e> struct segtree_2d {
  vector<S> seg;
  int _h, _w, sh, sw;
  segtree_2d(int h, int w) {
    sh = 1, sw = 1;
    _h = h, _w = w;
    while (sh < h)
      sh <<= 1;
    while (sw < w)
      sw <<= 1;
    seg = vector<S>(4 * sh * sw, e());
  }
  int idx(int h, int w) {
    assert(h >= 0 && h < sh * 2);
    assert(w >= 0 && w < sw * 2);
    return h * 2 * sw + w;
  }
  void set(int x, int y, S v) {
    assert(x >= 0 && x < _h);
    assert(y >= 0 && y < _w);
    x += sh, y += sw;
    seg[idx(x, y)] = v;
    for (int i = y / 2; i > 0; i /= 2) {
      seg[idx(x, i)] = op(seg[idx(x, i * 2)], seg[idx(x, i * 2 + 1)]);
    }
    while (x /= 2) {
      seg[idx(x, y)] = op(seg[idx(x * 2, y)], seg[idx(x * 2 + 1, y)]);
      for (int i = y / 2; i > 0; i /= 2) {
        seg[idx(x, i)] = op(seg[idx(x, i * 2)], seg[idx(x, i * 2 + 1)]);
      }
    }
  }
  S _inner_prod(int k, int l, int r) {
    S retL = e(), retR = e();
    for (l += sw, r += sw; l < r; l /= 2, r /= 2) {
      if (l % 2)
        retL = op(retL, seg[idx(k, l++)]);
      if (r % 2)
        retR = op(seg[idx(k, --r)], retR);
    }
    return op(retL, retR);
  }
  S prod(int h1, int w1, int h2, int w2) {
    assert(h1 >= 0 && h1 < _h);
    assert(h2 >= h1 && h2 <= _h);
    assert(w1 >= 0 && w1 < _w);
    assert(w2 >= w1 && w2 <= _w);
    S retU = e(), retD = e();
    for (h1 += sh, h2 += sh; h1 < h2; h1 /= 2, h2 /= 2) {
      if (h1 % 2)
        retU = op(retU, _inner_prod(h1++, w1, w2));
      if (h2 % 2)
        retD = op(_inner_prod(--h2, w1, w2), retD);
    }
    return op(retU, retD);
  }
};
} // namespace Lib