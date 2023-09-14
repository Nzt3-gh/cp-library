#include"../template/template.hpp"

namespace Lib{
  template<class T>
  vector<int> get_palindrome(const vector<T>& A){
    vector<int> ret(A.size());
    int i=0,j=0;
    while(i<A.size()){
      while(i-j>=0&&i+j<A.size()&&A[i-j]==A[i+j])j+=1;
      ret[i]=j;
      int k=1;
      while(i-k>=0&&k+ret[i-k]<j)ret[i+k]=ret[i-k],k+=1;
      i+=k,j-=k;
    }
    return ret;
  }
}

