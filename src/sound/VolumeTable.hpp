#ifndef VOLUMETABLE_HPP
#define VOLUMETABLE_HPP

#include "src/Fwd.hpp"

#include <array>

namespace sound {

class VolumeTable {
 private:
  static constexpr std::size_t ByteSize = 16;
  std::array<Byte, ByteSize> _volume_table = {};

 public:
  Byte get_nibble(Byte i) const {
    if (i % 2)
    return _volume_table[i / 2] & 0x0f;
    else 
    return (_volume_table[i / 2] & 0xf0) >> 4;
  }
  Byte& operator[](Byte i) { return _volume_table[i]; }
  Byte operator[](Byte i) const { return _volume_table[i]; }
  constexpr std::size_t size() const { return ByteSize * 2; }
};

}  // namespace sound

#endif // VOLUMETABLE_HPP
