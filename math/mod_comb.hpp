#include"../template/template.hpp"

/*
mod素数で 階乗と逆元を計算する
verify https://atcoder.jp/contests/abc297/submissions/46169077
*/

namespace Lib{
  struct mod_fac{
    vector <ll> fac,inv,invf;
    mod_fac (int n):
      fac(n),inv(n),invf(n){
      fac[0]=fac[1]=1;
      inv[0]=inv[1]=1;
      invf[0]=invf[1]=1;
      for(int i=2;i<n;i++){
        fac[i]=fac[i-1]*i%mod;
        inv[i]=inv[mod%i]*(mod-mod/i)%mod;
        invf[i]=invf[i-1]*inv[i]%mod;
      }
    }
    ll comb(int n,int r){
      return fac[n]*invf[r]%mod*invf[n-r]%mod;
    }
    ll perm(int n,int r){
      return fac[n]*invf[n-r]%mod;
    }
  };
}