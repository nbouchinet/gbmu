#include "Gameboy.hpp"
#include "MemoryBus.hpp"
#include "PPU.hpp"
#include "cpu/InterruptController.hpp"

#include <bitset>
#include <unistd.h>

//------------------------------------------------------------------------------
bool PPU::is_hdma_active() {
  return (test_bit(_hdma5, 7) == true ? false : true);
}

//------------------------------------------------------------------------------
void PPU::hdma_h_blank_step() {
  // if destination address overflows, stop the transfer
  if (_h_blank_hdma_dst_addr + 16 < _h_blank_hdma_dst_addr) {
    set_bit(_hdma5, 7);
    return;
  }

  _components.core->instr_halt();
  for (int i = 0; i < 16; i++) {
    _components.mem_bus->write(
        _h_blank_hdma_dst_addr + 0x8000,
        _components.mem_bus->read<Byte>(_h_blank_hdma_src_addr));
    _h_blank_hdma_src_addr++;
    _h_blank_hdma_dst_addr++;
  }
  _components.core->notify_interrupt();

  _hdma1 = _h_blank_hdma_src_addr >> 8;
  _hdma2 = _h_blank_hdma_src_addr & 0xFF;
  _hdma3 = _h_blank_hdma_dst_addr >> 8;
  _hdma4 = _h_blank_hdma_dst_addr & 0xFF;

  _hdma5--;
}

//------------------------------------------------------------------------------
void PPU::general_purpose_hdma(uint8_t hdma5_arg) {
  uint16_t addr_source = 0;
  uint16_t addr_dest = 0;
  uint16_t lines_to_transfer = 0;

  addr_source = ((_hdma1 << 8) | _hdma2) & 0xFFF0;
  addr_dest = ((_hdma3 << 8) | _hdma4) & 0x1FF0;
  lines_to_transfer = ((hdma5_arg & 0x7F) + 1) * 16;

  _components.core->instr_halt();
  for (int i = 0; i < lines_to_transfer; i++) {
    _components.mem_bus->write(
        0x8000 + addr_dest + i,
        _components.mem_bus->read<Byte>(addr_source + i));
  }
  _components.core->notify_interrupt();

  addr_source += lines_to_transfer;
  addr_dest += lines_to_transfer;

  _hdma1 = addr_source >> 8;
  _hdma2 = addr_source & 0xFF;
  _hdma3 = addr_dest >> 8;
  _hdma4 = addr_dest & 0xFF;
  _hdma5 = 0xFF;
}

//------------------------------------------------------------------------------
void PPU::initiate_h_blank_hdma_transfer(uint8_t hdma5_arg) {
  unset_bit(hdma5_arg, 7);
  _hdma5 = hdma5_arg;
  _h_blank_hdma_src_addr = ((_hdma1 << 8) + _hdma2) & 0xFFF0;
  _h_blank_hdma_dst_addr = ((_hdma3 << 8) | _hdma4) & 0x1FF0;
}

//------------------------------------------------------------------------------
void PPU::initiate_hdma_transfer(uint8_t hdma5_arg) {
  if (test_bit(hdma5_arg, 7) == true) {
    initiate_h_blank_hdma_transfer(hdma5_arg);
  } else {
    general_purpose_hdma(hdma5_arg);
  }
}

//------------------------------------------------------------------------------
void PPU::handle_hdma_transfer(uint8_t hdma5_arg) {
  if (is_hdma_active() == false) {
    initiate_hdma_transfer(hdma5_arg);
  } else if (is_hdma_active()) {
    if (test_bit(hdma5_arg, 7) == false)
      set_bit(_hdma5, 7);
    //		else
    //			initiate_hdma_transfer(hdma5_arg);
  }
}

//------------------------------------------------------------------------------
void PPU::dma_transfer(uint16_t address) {
  uint16_t dma_addr;

  //	_components.core->instr_halt();
  dma_addr = address << 8;
  for (int i = 0; i < 0xA0; i++) {
    _lcd_oam_ram[i] = _components.mem_bus->read<Byte>(
        dma_addr + i); // dma's are always written into OAM ram
  }
  //	_components.core->notify_interrupt();
}
