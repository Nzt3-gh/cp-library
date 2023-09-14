/*
年(Y)月(M)日(D) から曜日を求める
0: Sat, 1: Sun, 2: Mon, 3: Tus, 4:Wed, 5: Thu, 6: Fri
*/
namespace Lib{
  int get_day(int Y,int M,int D){
    if(M<=2)Y-=1,M+=12;
    return ((D+(13*(M+1)/5)+Y%100+(Y%100)/4+Y/400-Y/100*2)%7+7)%7;
  }
}
