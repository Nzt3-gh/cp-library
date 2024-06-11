#include "../template/template.hpp"

/*
foldable_queue <S,op>
半群Sを入れたqueueについて、全要素の積opを計算するデータ構造
push(S): 償却O(1)
末尾への追加
pop(): 償却O(1)
先頭の削除
prod(): 償却O(1)
全要素の積
front(): 償却O(1)
先頭の要素
verify https://judge.yosupo.jp/submission/170387

simple_foldable_queue<S,op,e>
単位元eを持つモノイドSを入れたqueueについて、全要素の積opを計算するデータ構造
foldable_queueから機能を絞った分メモリを半減 定数倍高速
push(S): 償却O(1)
末尾への追加
pop(): 償却O(1)
先頭の削除
prod(): 償却O(1)
全要素の積


半群を入れたstackについて、全要素の積を計算するデータ構造
foldable_stack
push: 末尾への追加 O(1)
pop: 末尾の削除 O(1)
prod: 全要素の積 O(1)
top: 末尾の要素 O(1)
未verify
*/
namespace Lib {
template <class S, auto op>
struct foldable_stack {
  static_assert(is_convertible_v<decltype(op), function<S(S, S)>>);
  vector<S> stack_V, stack_P;
  foldable_stack() : stack_V(0), stack_P(0) {}
  void push(S v) {
    if (!stack_P.empty()) {
      stack_P.push_back(op(stack_P.back(), v));
    } else {
      stack_P.push_back(v);
    }
    stack_V.push_back(v);
  }
  void pop() {
    assert(!stack_V.empty());
    assert(!stack_P.empty());
    stack_P.pop_back();
    stack_V.pop_back();
  }
  S top() {
    assert(!stack_V.empty());
    return stack_V.back();
  }
  S prod() {
    assert(!stack_P.empty());
    return stack_P.back();
  }
  size_t size() { return stack_V.size(); }
};

template <class S, auto op>
struct foldable_queue {
  static_assert(is_convertible_v<decltype(op), function<S(S, S)>>);
  vector<S> f_st_V, f_st_P, b_st_V, b_st_P;
  foldable_queue() : f_st_V(0), f_st_P(0), b_st_V(0), b_st_P(0) {}
  void push(S v) {
    if (!b_st_P.empty()) {
      b_st_P.push_back(op(b_st_P.back(), v));
    } else {
      b_st_P.push_back(v);
    }
    b_st_V.push_back(v);
  }
  void move_bf() {
    assert(f_st_V.empty());
    while (!b_st_V.empty()) {
      S v = b_st_V.back();
      b_st_V.pop_back();
      b_st_P.pop_back();
      if (f_st_P.empty()) {
        f_st_P.push_back(v);
      } else {
        f_st_P.push_back(op(v, f_st_P.back()));
      }
      f_st_V.push_back(v);
    }
  }
  void pop() {
    assert(f_st_P.size() + b_st_P.size() >= 1);
    if (f_st_P.empty()) {
      move_bf();
    }
    f_st_P.pop_back();
    f_st_V.pop_back();
  }
  S front() {
    assert(f_st_P.size() + b_st_P.size() >= 1);
    if (f_st_V.empty()) {
      move_bf();
    }
    return f_st_V.back();
  }
  S prod() {
    assert(f_st_P.size() + b_st_P.size() >= 1);
    S ret = front();
    if (!b_st_P.empty()) {
      ret = op(ret, b_st_P.back());
    }
    return ret;
  }
  size_t size() { return f_st_P.size() + b_st_P.size(); }
};

template <class S, auto op, auto e>
struct simple_foldable_queue {
  static_assert(is_convertible_v<decltype(op), function<S(S, S)>>);
  vector<S> f_P, b_V;
  S b_P;
  simple_foldable_queue() : f_P(0), b_V(0) { b_P = e(); }
  void push(S v) {
    b_V.push_back(v);
    b_P = op(b_P, v);
  }
  void move_bf() {
    assert(f_P.empty());
    while (!b_V.empty()) {
      f_P.push_back(b_V.back());
      b_V.pop_back();
    }
    for (int i = 1; i < (int)f_P.size(); i++) {
      f_P[i] = op(f_P[i], f_P[i - 1]);
    }
    b_P = e();
  }
  void pop() {
    assert(f_P.size() + b_V.size() >= 1);
    if (f_P.empty()) {
      move_bf();
    }
    f_P.pop_back();
  }
  S prod() {
    assert(f_P.size() + b_V.size() >= 1);
    if (f_P.empty()) {
      return b_P;
    }
    return op(f_P.back(), b_P);
  }
  size_t size() { return f_P.size() + b_V.size(); }
};
}  // namespace Lib
