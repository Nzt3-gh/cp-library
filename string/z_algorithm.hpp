#include"../template/template.hpp"

template<class T>
vector<int> z_algorithm(const vector<T>& A){
  int n=A.size();
  vector<int> z(n);
  int i=1,j=0;
  while(i<n){
    while(i+j<n&&A[j]==A[i+j])j+=1;
    z[i]=j;
    if(j==0){
      i+=1;
      continue;
    }
    int k=1;
    while(i+k<n&&k+z[k]<j)z[i+k]=z[k],k+=1;
    i+=k,j-=k;
  }
  z[0]=n;
  return z;
}