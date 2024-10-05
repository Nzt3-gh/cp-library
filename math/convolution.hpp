#include "../template/template.hpp"
#include "./modpow.hpp"

/*
数列の畳込み
C[i] = sum A[k]*B[i-k]

convolution(A,B): O( (|A|+|B|) log (|A|+|B|) )
A,Bを畳み込んだ数列 C を返す mod998

convolution_double (A,B):
A,B を畳み込んだ数列 C を返す
複素数でFFTを行う
*/
namespace Lib {
void butterfly(vector<ll>& a) {
  ll g = 3;
  ll sum_e[30];
  int n = a.size(), h = 1;
  while ((1 << h) < n) h++;
  assert(h < 23);
  {
    ll es[30], ies[30];
    int cnt2 = 23;
    ll e = Lib::modpow(g, (MOD - 1) >> cnt2), ie = Lib::modpow(e, MOD - 2);
    for (int i = cnt2; i >= 2; i--) {
      es[i - 2] = e;
      ies[i - 2] = ie;
      e = e * e % MOD;
      ie = ie * ie % MOD;
    }
    ll now = 1;
    for (int i = 0; i < cnt2 - 2; i++) {
      sum_e[i] = es[i] * now % MOD;
      now = now * ies[i] % MOD;
    }
  }
  for (int ph = 1; ph <= h; ph++) {
    int w = 1 << (ph - 1), p = 1 << (h - ph);
    ll now = 1;
    for (int s = 0; s < w; s++) {
      int offset = s << (h - ph + 1);
      for (int i = 0; i < p; i++) {
        ll l = a[i + offset], r = a[i + offset + p] * now % MOD;
        a[i + offset] = (l + r) % MOD;
        a[i + offset + p] = ((l - r) % MOD + MOD) % MOD;
      }
      int t = 0;
      while (((~(unsigned int)(s)) & (1 << t)) == 0) t++;
      now = now * sum_e[t] % MOD;
    }
  }
}
void butterfly_inv(vector<ll>& a) {
  ll g = 3;
  ll sum_ie[30];
  int n = a.size(), h = 1;
  while ((1 << h) < n) h++;
  assert(h < 23);
  {
    ll es[30], ies[30];
    int cnt2 = 23;
    ll e = Lib::modpow(g, (MOD - 1) >> cnt2), ie = Lib::modpow(e, MOD - 2);
    for (int i = cnt2; i >= 2; i--) {
      es[i - 2] = e;
      ies[i - 2] = ie;
      e = e * e % MOD;
      ie = ie * ie % MOD;
    }
    ll now = 1;
    for (int i = 0; i < cnt2 - 2; i++) {
      sum_ie[i] = ies[i] * now % MOD;
      now = now * es[i] % MOD;
    }
  }
  for (int ph = h; ph >= 1; ph--) {
    int w = 1 << (ph - 1), p = 1 << (h - ph);
    ll inow = 1;
    for (int s = 0; s < w; s++) {
      int offset = s << (h - ph + 1);
      for (int i = 0; i < p; i++) {
        ll l = a[i + offset], r = a[i + offset + p];
        a[i + offset] = (l + r) % MOD;
        a[i + offset + p] = (((l - r) % MOD + MOD) % MOD * inow) % MOD;
      }
      int t = 0;
      while (((~(unsigned int)(s)) & (1 << t)) == 0) t++;
      inow = inow * sum_ie[t] % MOD;
    }
  }
}
vector<ll> convolution(vector<ll> a, vector<ll> b) {
  int n = a.size(), m = b.size();
  int z = 1;
  while (z <= n + m - 1) z <<= 1;
  a.resize(z);
  butterfly(a);
  b.resize(z);
  butterfly(b);
  rep(i, z) { a[i] = a[i] * b[i] % MOD; }
  butterfly_inv(a);
  a.resize(n + m - 1);
  ll iz = Lib::modpow(z, MOD - 2);
  rep(i, n + m - 1) a[i] = a[i] * iz % MOD;
  return a;
}
}  // namespace Lib