#include <cstdint>
#include <iostream>
#include <vector>
using Word = uint16_t;
using Byte = uint8_t;
template <typename T>
void exec(std::function<void(T&)> f, T& t) {
  f(t);
}

int main () {
  int i= 0;
  exec([] (int &a) {++a; }, i);
}
