#include"../template/template.hpp"

/*
Binary Indexed Tree
半群 の 区間積 が乗るが、ここでは sum のみを想定する
1-indexed
add(p,v) 位置pにvを加算する
sum(l,r) 区間[l,r)の和を得る
*/

namespace Lib{
  struct BIT{
    vector<ll> a;
    int sz;
    BIT (int n):
      sz(n),a(sz+1) {}
    void add(int p,int v){
      for(;p<=sz;p+=p&-p)a[p]+=v;
    }
    ll sum(int l,int r){
      ll ret=0;
      for(--r;r>0;r-=r&-r)ret+=a[r];
      for(--l;l>0;l-=l&-l)ret-=a[l];
      return ret;
    }
  };
}