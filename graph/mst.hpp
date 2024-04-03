#include"../template/template.hpp"
#include"../data_structure/dsu.hpp"

/*
最小全域木

MST_edge(vector<edge> E,int N): 辺集合Eと頂点数Nを与えると pair{最小全域森のコスト,最小全域森に含まれる辺のindex列} を返す

verify: https://judge.yosupo.jp/submission/200260


*/

namespace Lib{
  pair<ll,vector<int>> MST_edge(vector<array<ll,3>> &E,int N){
    Lib::DSU uf(N);
    int M=E.size();
    vector<int> edge_idx(M);
    for(int i=0;i<M;i++)edge_idx[i]=i;
    sort(edge_idx.begin(),edge_idx.end(),[&](int l,int r){
      return E[l][2]<E[r][2];
    });
    vector<int> ret;
    ll cost=0;
    for(auto i:edge_idx){
      if(!uf.same(E[i][0],E[i][1])){
        ret.push_back(i);
        uf.merge(E[i][0],E[i][1]);
        cost+=E[i][2];
      }
    }
    return make_pair(cost,ret);
  }
} // namespace Lib
