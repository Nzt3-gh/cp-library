#include"../template/template.hpp"

namespace Lib{
  struct mod_fac{
    vector <ll> fac,inv,invf;
    mod_fac (int n,int mod){
      fac.resize(n);
      inv.resize(n);
      invf.resize(n);
      fac[0]=fac[1]=1;
      inv[0]=inv[1]=1;
      invf[0]=invf[1]=1;
      for(int i=2;i<n;i++){
        fac[i]=fac[i-1]*i%mod;
        inv[i]=inv[mod%i]*(mod-mod/i)%mod;
        invf[i]=invf[i-1]*inv[i]%mod;
      }
    }
  };
}