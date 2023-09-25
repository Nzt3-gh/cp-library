#include"../template/template.hpp"

namespace Lib{
  ll modpow(long long a,int n){
    long long ret=1,t=a;
    while(n>0){
      if(n&1)ret=ret*t%mod;
      t=t*t%mod;
      n/=2;
    }
    return ret;
  }
}