namespace Lib{
  long long llceil(long long a,long long b){
    if(a%b==0){return a/b;}
  
    if(a>=0){return (a/b)+1;}
    else{return -((-a)/b);}
  }

  long long llfloor(long long a,long long b){
    if(a%b==0){return a/b;}
  
    if(a>=0){return (a/b);}
    else{return -((-a)/b)-1;}
  }
}
