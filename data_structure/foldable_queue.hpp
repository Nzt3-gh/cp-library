#include "../template/template.hpp"

/*
半群を入れたqueueについて、全要素の積を計算するデータ構造
foldable_stack も用意する
*/
namespace Lib {
  template<class S,auto op>
  struct foldable_stack{
    static_assert(is_convertible_v<decltype(op),function<S(S,S)>>);
    vector<S> stack_V,stack_P;
    foldable_stack():stack_V(0),stack_P(0){}
    void push(S v){
      if(!stack_P.empty()){
        stack_P.push_back(op(stack_P.back(),v));
      }else{
        stack_P.push_back(v);
      }
      stack_V.push_back(v);
    }
    void pop(){
      assert(!stack_V.empty());
      assert(!stack_P.empty());
      stack_P.pop_back();
      stack_V.pop_back();
    }
    S top(){
      assert(!stack_V.empty());
      return stack_V.back();
    }
    S prod(){
      assert(!stack_P.empty());
      return stack_P.back();
    }
  };

  template<class S,auto op>
  struct foldable_queue{
    static_assert(is_convertible_v<decltype(op),function<S(S,S)>>);
    vector<S> f_st_V,f_st_P,b_st_V,b_st_P;
    foldable_queue():f_st_V(0),f_st_P(0),b_st_V(0),b_st_P(0){}
    void push(S v){
      if(!b_st_P.empty()){
        b_st_P.push_back(op(b_st_P.back(),v));
      }else{
        b_st_P.push_back(v);
      }
      b_st_V.push_back(v);
    }
    void move_bf(){
      assert(f_st_V.empty());
      while(!b_st_V.epmty()){
        S v=b_st_V.back();
        b_st_V.pop_back();
        b_st_P.pop_back();
        if(f_st_P.epmty()){
          f_st_P.push_back(v);
        }else{
          f_st_P.push_back(op(v,f_st_P.back()));
        }
        f_st_V.push_back(v);
      }
    }
    void pop(){
      assert(f_st_P.size()+b_st_P.size()>=1);
      if(f_st_P.empty()){
        move_bf();
      }
      f_st_P.pop_back();
      f_st_V.pop_back();
    }
    S front(){
      assert(f_st_P.size()+b_st_P.size()>=1);
      if(f_st_P.empty()){
        move_bf();
      }
      return f_st_P.back();
    }
    S prod(){
      assert(f_st_P.size()+b_st_P.size()>=1);
      S ret=front();
      if(!b_st_P.empty()){
        ret=op(ret,b_st_P.back());
      }
      return ret;
    }

  };
  
}  // namespace Lib
