#ifndef VOLUMETABLE_HPP
#define VOLUMETABLE_HPP

#include "src/Fwd.hpp"

#include <array>
#include <boost/serialization/access.hpp>

namespace sound {

class VolumeTable {
 public:
  static constexpr std::size_t ByteSize = 16;
  using Table = std::array<Byte, ByteSize>;

 private:
  Table _volume_table = {};

 public:
  VolumeTable(Table&& t) : _volume_table(std::move(t)) {}
  VolumeTable() = default;

  Byte get_nibble(Byte i) const {
    if (i % 2)
      return _volume_table[i / 2] & 0x0f;
    else
      return (_volume_table[i / 2] & 0xf0) >> 4;
  }

  void clear() { _volume_table.fill(0); }

  Byte& operator[](Byte i) { return _volume_table[i]; }
  Byte operator[](Byte i) const { return _volume_table[i]; }

  constexpr std::size_t size() const { return ByteSize * 2; }

  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int) {
    ar & _volume_table;
  }
};

}  // namespace sound

#endif  // VOLUMETABLE_HPP
