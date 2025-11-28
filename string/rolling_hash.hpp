#include "../template/template.hpp"

/*
配列Sのハッシュ値を求める
N=|S|とする

構築(S,base): O(N)
vector<整数> / String からhash列を構築する
baseを与える

get(l,r): O(1)
区間[l,r)のハッシュ値を求める

verify
https://yukicoder.me/submissions/950314
https://atcoder.jp/contests/tessoku-book/submissions/50219460
https://atcoder.jp/contests/joi2008ho/submissions/50221125

*/
namespace Lib {
struct Rolling_hash {
  static constexpr ll rMOD = (1ll << 61) - 1;
  ull base, inv;
  vector<ull> hash_val, pw;
  Rolling_hash(string St, unsigned b) {
    vector<ull> S(St.begin(), St.end());
    base = b;
    ull c = 1, t = base;
    ull h = 0;
    pw.push_back(1);
    hash_val.push_back(0);
    for (int i = 0; i < ssize(S); i++) {
      h = (mul(h, base) + S[i]) % rMOD;
      hash_val.push_back(h);
      pw.push_back(mul(pw.back(), base));
    }
  }
  Rolling_hash(vector<ull> S, unsigned b) {
    base = b;
    ull c = 1, t = base;
    ull h = 0;
    pw.push_back(1);
    hash_val.push_back(0);
    for (int i = 0; i < ssize(S); i++) {
      h = (mul(h, base) + S[i]) % rMOD;
      hash_val.push_back(h);
      pw.push_back(mul(pw.back(), base));
    }
  }
  constexpr ull mul(ull a, ull b) {
    ull a1 = a / (1ull << 31), a2 = a % (1ull << 31), b1 = b / (1ull << 31),
        b2 = b % (1ull << 31);
    ull ret = 0;
    ret = (ret + a1 * b1 * 2) % rMOD;
    ull mid = a1 * b2 + b1 * a2;
    ret =
        (ret + mid / (1ull << 30) + (mid % (1ull << 30)) * (1ull << 31)) % rMOD;
    ret = (ret + a2 * b2) % rMOD;
    return ret;
  }
  ull get(int l, int r) {
    assert(l < r);
    return (hash_val[r] - mul(hash_val[l], pw[r - l]) + rMOD) % rMOD;
  }
};
} // namespace Lib