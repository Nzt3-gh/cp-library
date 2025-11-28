#include "extGCD.hpp"

/*
crt: O(n log max(m))
n個の x=r (mod m) という形の情報を全て満たす x=ret_r (mod ret_m) を返す
verify https://yukicoder.me/submissions/926973

crt_mod:O(n^2)
n個の x=r (mod m) という形の情報を全て満たす x=ret_r (mod ret_m)
について、ret_r%modとret_m%mod を返す
verify https://yukicoder.me/submissions/927026
*/

namespace Lib {
pair<ll, ll> crt(vector<ll> r, vector<ll> m) {
  assert(r.size() == m.size());
  ll ret_r = r[0], ret_m = m[0];
  int n = ssize(r);
  for (int i = 1; i < n; i++) {
    ll x = 0, y = 0, d = extGCD(ret_m, m[i], x, y);
    if ((ret_r - r[i]) % d != 0) {
      return make_pair(-1ll, -1ll);
    }
    ll tmp = x * (r[i] - ret_r) / d % (m[i] / d);
    ret_r += tmp * ret_m;
    ret_m *= m[i] / d;
    ret_r %= ret_m;
    if (ret_r < 0)
      ret_r += ret_m;
  }
  if (ret_r < 0)
    ret_r += ret_m;
  return make_pair(ret_r, ret_m);
}

pair<ll, ll> crt_mod(vector<ll> r, vector<ll> m, ll MOD) {
  int n = r.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      ll g = gcd(m[i], m[j]);
      if ((r[i] - r[j]) % g != 0) {
        return make_pair(-1ll, -1ll);
      }
      m[i] /= g, m[j] /= g;
      ll gi = gcd(m[i], g), gj = g / gi;
      do {
        g = gcd(gi, gj);
        gi *= g, gj /= g;
      } while (g != 1);
      m[i] *= gi, m[j] *= gj;
      r[i] %= m[i], r[j] %= m[j];
    }
  }
  m.push_back(MOD);
  vector cef(n + 1, 1ll), con(n + 1, 0ll);
  for (int i = 0; i < n; i++) {
    ll t = (r[i] - con[i]) * modinv(cef[i], m[i]) % m[i];
    if (t < 0)
      t += m[i];
    for (int j = i + 1; j <= n; j++) {
      con[j] += cef[j] * t;
      con[j] %= m[j];
      cef[j] = cef[j] * m[i] % m[j];
    }
  }
  return make_pair(con[n], cef[n]);
}
} // namespace Lib
