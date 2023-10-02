#include"../template/template.hpp"

/*
Disjoint Set Union + Rollback
merge by size により leader, merge, same, sizeを O(log(N))で行う
undoにより直前のmergeを O(1)で 取り消す
*/

namespace Lib{
  struct DSU{
    vector<int>par,sz;
    stack<array<int,3>>his;
    DSU(int n):
      par(n),sz(n){
      fill(par.begin(),par.end(),-1);
      fill(sz.begin(),sz.end(),1);
    }
    int leader(int a){
      if(par[a]==-1)return a;
      return leader(par[a]);
    }
    void merge(int a,int b){
      a=leader(a),b=leader(b);
      if(a==b){
        his.push({-1,-1,-1});
        return;
      }
      if(sz[a]>sz[b])swap(a,b);
      his.push({a,b,sz[a]});
      par[a]=b;
      sz[b]+=sz[a];
    }
    bool same(int a,int b){
      a=leader(a),b=leader(b);
      return a==b;
    }
    void undo(){
      auto [c,p,s]=his.top();
      if(c==-1)return;
      his.pop();
      par[c]=-1;
      sz[c]=s;
      sz[p]-=s;
    }
    int size(int v){
      v=leader(v);
      return sz[v];
    }
  };
}