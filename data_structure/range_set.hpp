#include "../template/template.hpp"

/*
区間 [l,r) を要素に持つset
区間 [l,r) の追加、削除,点pの存在判定を行う

add({l,r}): ならしlog(n)
区間[l,r)をsetに追加する 繋がる区間はまとめられる

erase({l,r}): ならしlog(n)
区間[l,r)をsetから削除する

cover({l,r}); log(n)
区間 [l,r) を包含する区間がsetに存在するか判定する 存在する場合はその区間を返す
*/

namespace Lib {
struct range_set {
  using all2 = array<long long, 2>;
  static constexpr ll minf = numeric_limits<ll>::min();
  static constexpr ll pinf = numeric_limits<ll>::max();
  set<all2> intervals;
  int add(all2 a) {
    auto [l, r] = a;
    int ret = 1;
    {
      auto it = intervals.upper_bound(all2({l, pinf}));
      if (it != intervals.begin()) {
        it--;
        if ((*it)[1] >= r)
          return 0;
        if ((*it)[1] >= l)
          l = (*it)[0];
      }
    }
    auto it = intervals.lower_bound(all2({l, minf}));
    while (1) {
      if (it != intervals.end() && (*it)[0] <= r) {
        r = max(r, (*it)[1]);
        auto it2 = it;
        it++;
        intervals.erase(it2);
        ret -= 1;
      } else {
        break;
      }
    }
    intervals.insert({l, r});
    return ret;
  }
  int erase(all2 a) {
    auto [l, r] = a;
    int ret = 0;
    {
      auto it = intervals.lower_bound(all2({l, minf}));
      if (it != intervals.begin()) {
        it--;
        if ((*it)[1] > l) {
          auto [l2, r2] = *it;
          intervals.erase(it);
          intervals.insert({l2, l});
          if (r2 > r) {
            intervals.insert({r, r2});
            ret += 1;
          }
        }
      }
    }
    auto it = intervals.lower_bound(all2({l, minf}));
    while (1) {
      if (it != intervals.end() && (*it)[1] <= r) {
        auto it2 = it;
        it++;
        intervals.erase(it2);
        ret -= 1;
      } else {
        break;
      }
    }
    if (it != intervals.end() && (*it)[0] < r) {
      auto [l2, r2] = *it;
      intervals.erase(it);
      intervals.insert({r, r2});
    }
    return ret;
  }
  pair<bool, all2> cover(all2 b) {
    auto [l, r] = b;
    auto it = intervals.upper_bound(all2({l, pinf}));
    if (it != intervals.begin()) {
      it--;
      if ((*it)[0] <= l && r <= (*it)[1]) {
        all2 ret = *it;
        return make_pair(true, ret);
      }
    }
    return make_pair(false, all2({0, 0}));
  }
};
} // namespace Lib