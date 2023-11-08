#include "../template/template.hpp"

namespace Lib {
ll extGCD(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  ll d = extGCD(b, a % b, y, x);
  y = y - a / b * x;
  return d;
}
ll modinv(ll a, ll m) {
  ll x = 0, y = 0, d = extGCD(a, m, x, y);
  if (d != 1) {
    return -1;
  }
  return x;
}
}  // namespace Lib