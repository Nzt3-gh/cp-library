#include"../template/template.hpp"

/*
suffix_array: O(n log^2 n + a n log n)
[0,n]のSuffix Array を求める 先頭要素は必ずnになる(空文字列なので)
2項の比較演算がO(a)であるときに n log^2 n + an log nである


lcp_array: O(a n log n)
LCP Array を求める
2項の比較演算がO(a)であるときに an log nである

verify https://atcoder.jp/contests/practice2/submissions/47840592

*/
namespace Lib {
template <class T>
vector<int> suffix_array(const vector<T>& s) {
  int n = s.size();
  vector<int> idx(n), sa(n + 1), rnk(n + 1, -1), tmp(n + 1);
  iota(idx.begin(), idx.end(), 0);
  sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });
  for (int i = 0, t = 0; i < n; i++, t++) {
    if (i > 0 && s[idx[i - 1]] == s[idx[i]]) --t;
    rnk[idx[i]] = t;
  }
  iota(sa.begin(), sa.end(), 0);
  for (int k = 1; k <= n; k *= 2) {
    auto comp = [&](int l, int r) {
      if (rnk[l] != rnk[r]) return rnk[l] < rnk[r];
      int l2 = l + k <= n ? rnk[l + k] : -1, r2 = r + k <= n ? rnk[r + k] : -1;
      return l2 < r2;
    };
    sort(sa.begin(), sa.end(), comp);
    tmp[sa[0]] = 0;
    for (int i = 1; i <= n; i++) {
      tmp[sa[i]] = tmp[sa[i - 1]] + comp(sa[i - 1], sa[i]);
    }
    swap(rnk, tmp);
  }
  return sa;
}

template <class T>
vector<int> lcp_array(const vector<T>& s, const vector<int>& sa) {
  int n = s.size();
  vector<int> a(n), idx(n);
  iota(idx.begin(), idx.end(), 0);
  sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });
  for (int i = 0, t = 0; i < n; i++, t++) {
    if (i > 0 && s[idx[i - 1]] == s[idx[i]]) --t;
    a[idx[i]] = t;
  }
  vector<int> rnk(n + 1);
  for (int i = 0; i <= n; i++) {
    rnk[sa[i]] = i;
  }
  int h = 0;
  vector<int> lcp(n);
  for (int i = 0; i < n; i++) {
    int j = sa[rnk[i] - 1];
    if (h > 0) h--;
    for (; i + h < n && j + h < n; h++) {
      if (a[j + h] != a[i + h]) break;
    }
    lcp[rnk[i] - 1] = h;
  }
  return lcp;
}
}  // namespace Lib