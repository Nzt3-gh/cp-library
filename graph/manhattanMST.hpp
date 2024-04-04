#include"../data_structure/segtree.hpp"
#include"mst.hpp"

/*
点列を与えるとマンハッタン距離で最小全域木を返す

manhattan_mst(vector<array<ll,2>> P):
  点列 P を与えると、 {最小全域木のコスト,辺列} のペアを返す

verify: https://judge.yosupo.jp/submission/200489
*/

namespace Lib{
  pair<ll,vector<array<int,2>>> manhattan_mst(vector<array<ll,2>> P){
    int N=P.size();
    vector<array<ll,3>> E;
    for(int x_inv=0;x_inv<2;x_inv++){
      for(int y_inv=0;y_inv<2;y_inv++){
        for(int xy_inv=0;xy_inv<2;xy_inv++){
          vector y(N,0ll);
          for(int i=0;i<N;i++){
            y[i]=P[i][1];
          }
          sort(y.begin(),y.end());
          y.erase(unique(y.begin(),y.end()),y.end());
          vector y_idx(N,0);
          for(int i=0;i<N;i++){
            y_idx[i]=lower_bound(y.begin(),y.end(),P[i][1])-y.begin();
          }
          auto seg_op=[](pair<ll,int> a,pair<ll,int> b){
            if(a.first<=b.first){
              return a;
            }
            return b;
          };
          auto seg_e=[](){
            return make_pair((ll)5e18,-1);
          };
          Lib::segtree<pair<ll,int>,seg_op,seg_e> seg(y.size());
          vector idx(N,0);
          iota(idx.begin(),idx.end(),0);
          sort(idx.begin(),idx.end(),[&](int l,int r){
            return array<ll,2>({P[l][1]-P[l][0],-y_idx[l]}) < 
            array<ll,2>({P[r][1]-P[r][0],-y_idx[r]});
          });
          for(int i:idx){
            auto p=seg.prod(y_idx[i],y.size());
            ll x=P[i][0]+P[i][1];
            if(p.second!=-1){
              E.push_back({i,p.second,p.first-x});
            }
            if(seg.get(y_idx[i]).first>x)seg.set(y_idx[i],make_pair(x,i));
          }
          for(auto &i:P){
            swap(i[0],i[1]);
          }
        }
        for(auto &i:P){
          i[1]=-i[1];
        }
      }
      for(auto &i:P){
        i[0]=-i[0];
      }
    }
    auto [cost,Es]=MST_edge(E,(int)P.size());
    vector<array<int,2>> ret;
    for(int i:Es){
      ret.push_back({(int)E[i][0],(int)E[i][1]});
    }
    return make_pair(cost,ret);
  }
} // namespace Lib
