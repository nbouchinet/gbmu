#include "src/Bios.hpp"
#include "src/Gameboy.hpp"
#include "src/MemoryBus.hpp"

Bios::Bios(ComponentsContainer &components) : _components(components) {}

bool Bios::is_cgb_bios() const {
  Byte _cgb_flag = _components.mem_bus->read<Byte>(0x143);
  if (_cgb_flag == 0xC0) {
    return true;
  } else if (_cgb_flag == 0x80) {
    return true;
  } else {
    return false;
  }
}

Byte Bios::read(Word addr) const {
  if (is_cgb_bios()) {
    return _cgb_bios[addr];
  }
  return _dmg_bios[addr];
}

auto Bios::get_begin() {
  if (is_cgb_bios()) {
    return _cgb_bios.begin();
  }
  return _dmg_bios.begin();
}
