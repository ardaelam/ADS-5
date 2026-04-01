// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  static const int kSize = size;
  T data[kSize];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  void push(T val) {
    if (topIndex < kSize - 1) {
      data[++topIndex] = val;
    }
  }

  T pop() {
    if (topIndex >= 0) {
      return data[topIndex--];
    }
    return T();
  }

  T top() const {
    if (topIndex >= 0) {
      return data[topIndex];
    }
    return T();
  }

  bool empty() const {
    return topIndex == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
