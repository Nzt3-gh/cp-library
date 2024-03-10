#include"../template/template.hpp"

namespace Lib{
  ll modpow(ll a,ll n){
    long long ret=1,t=a;
    while(n>0){
      if(n&1)ret=ret*t%MOD;
      t=t*t%MOD;
      n/=2;
    }
    return ret;
  }
}