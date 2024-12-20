#include "../template/template.hpp"

/*
二次元平面上の点集合について、凸包に使われる点を求める
入力は全ての点の座標が異なる必要がある

ConvexHull(pair<ll,ll> XY)
*/
namespace Lib {
using pll = pair<ll,ll>;
vector<int> argsort(const vector<pll> &A) {
  vector<int> ids(A.size());
  iota(all(ids), 0);
  sort(all(ids),
       [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });
  return ids;
}
vector<int> convex_hull(const vector<pll> &XY) {
  ll N = XY.size();
  if (N == 0) return {};
  if (N == 1) return {0};
  if (N == 2) return {0, 1};
  vector I = argsort(XY);
  auto check = [&](ll i, ll j, ll k) -> bool {
    auto xi = XY[i].first, yi = XY[i].second;
    auto xj = XY[j].first, yj = XY[j].second;
    auto xk = XY[k].first, yk = XY[k].second;
    auto dx1 = xj - xi, dy1 = yj - yi;
    auto dx2 = xk - xj, dy2 = yk - yj;
    ll det = dx1 * dy2 - dy1 * dx2;
    // return det >= 0; 辺上の点を含む場合
    return det > 0;
  };
  auto calc = [&]() {
    vector<int> P;
    for (auto &&k : I) {
      if (P.size() && XY[P.back()] == XY[k]) continue;
      while (P.size() > 1) {
        auto i = P[P.size() - 2];
        auto j = P[P.size() - 1];
        if (check(i, j, k)) break;
        P.pop_back();
      }
      P.push_back(k);
    }
    return P;
  };

  // 上側
  vector<int> P;
  {
    vector<int> Q1 = calc();
    P.insert(P.end(), all(Q1));
  }

  // 下側
  {
    if (!P.empty()) P.pop_back();
    reverse(all(I));
    vector<int> Q2 = calc();
    P.insert(P.end(), all(Q2));
  }

  if (P.size() >= 2 && XY[P[0]] == XY[P.back()]) P.pop_back();
  return P;
}
}  // namespace Lib
