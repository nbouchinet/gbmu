#include <cstdint>
#include <iostream>
#include <vector>
using Word = uint16_t;
using Byte = uint8_t;

union Register {
  Word word = 0;
  struct {
    Byte low, high;
  };
};

int main () {
  Register r;
  r.word = 0xffaa;
  std::cout << std::hex << (int)r.high <<  ", " << (int)r.low << std::endl;
}
