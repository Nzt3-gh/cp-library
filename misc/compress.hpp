#include "../template/template.hpp"
/*
座標圧縮

Compress (vector<T> V) :  O(|V|)
vector Vの座標圧縮を構築

idx(v): O(log(|V|))
値vの座標圧縮後のindexを取得

val(i): O(1)
i番目の値を取得
*/

namespace Lib {
template <class T> struct Compress {
  vector<T> v;
  long long sz;
  Compress(vector<T> v_) : v(v_) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    sz = ssize(v);
  }
  int idx(T x) {
    int ret = lower_bound(v.begin(), v.end(), x) - v.begin();
    assert(ret < sz);
    assert(v[ret] == x);
    return ret;
  }
  T val(int i) {
    assert(i >= 0 && i < sz);
    return v[i];
  }
  int size() { return sz; }
};
} // namespace Lib