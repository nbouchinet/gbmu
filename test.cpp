#include <cstdint>
#include <iostream>
#include <vector>
using Word = uint16_t;
using Byte = uint8_t;
int main () {
  std::vector<Byte> b;
  Word _clock = 0u;
  for (auto it = b.begin(); it != b.end(); ++it) { 
    switch (*it) {
#include "instructions.inc"
    }
  }

}
