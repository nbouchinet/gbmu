#ifndef BIOS_H
#define BIOS_H

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"
#include "src/GbType.hpp"

#include <exception>
#include <vector>
#include <boost/serialization/access.hpp>

class Bios : public IReadWrite {

public:
  class BadLogo : public std::exception {
  public:
    const char *what() const noexcept { return "Bad Nintendo Logo"; }
  };

private:
  static const std::vector<Byte> s_dmg_bios;
  static const std::vector<Byte> s_cgb_bios;

  friend boost::serialization::access;
  template <class Archive> void serialize(Archive &, const unsigned int) {}

  const std::vector<Byte>& get_bios() const;

  GbType _type = GbType::DMG;

public:
  Byte read(Word addr) const { return get_bios()[addr]; }
  void write(Word, Byte) { }

  auto get_begin() const { get_bios().cbegin(); }
  void set_type(GbType type) { _type = type; }
};
#endif /* BIOS_H */
