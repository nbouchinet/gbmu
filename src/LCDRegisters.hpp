#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

class LCDRegisters : public IReadWrite {
private:
  static constexpr Word _lcd_range_begin = 0xFF40;
  static constexpr Word _lcd_range_end = 0xFF4B;
  Word _lcd_register[12];

public:
  LCDRegisters() {
	_lcd_register[0xFF40 - _lcd_range_begin] = 0x91;
	_lcd_register[0xFF42 - _lcd_range_begin] = 0x00;
	_lcd_register[0xFF43 - _lcd_range_begin] = 0x00;
	_lcd_register[0xFF45 - _lcd_range_begin] = 0x00;
	_lcd_register[0xFF47 - _lcd_range_begin] = 0xFC;
	_lcd_register[0xFF48 - _lcd_range_begin] = 0xFF;
	_lcd_register[0xFF49 - _lcd_range_begin] = 0xFF;
	_lcd_register[0xFF4A - _lcd_range_begin] = 0x00;
	_lcd_register[0xFF4B - _lcd_range_begin] = 0x00;
  }

  Byte read(Word addr) const override {
      return _lcd_register[addr - _lcd_range_begin];
  }
  void write(Word addr, Byte v) override {
      _lcd_register[addr - _lcd_range_begin] = v;
  }
};
