#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

class LCDRegisters : public IReadWrite {
private:
  Byte _lcdc, _stat, _scy, _scx, _ly, _lyc, _dma, _bgp, _obp0, _obp1, _wy, _wx;

public:
  LCDRegisters() { reset(); }

  void reset(){
	_lcdc = 0x91;
	_stat = 0;
	_scy = 0;
	_scx = 0;
	_ly = 0;
	_lyc = 0xFC;
	_dma = 0;
	_bgp = 0xFC;
	_obp0 = 0xFF;
	_obp1 = 0xFF;
	_wy = 0;
	_wx = 0;
  }

  Byte read(Word addr) const override {
    switch (addr) {
    case 0xFF40:
      return _lcdc;
    case 0xFF41:
      return _stat;
    case 0xFF42:
      return _scy;
    case 0xFF43:
      return _scx;
    case 0xFF44:
      return _ly;
    case 0xFF45:
      return _lyc;
    case 0xFF46:
      return _dma;
    case 0xFF47:
      return _bgp;
    case 0xFF48:
      return _obp0;
    case 0xFF49:
      return _obp1;
    case 0xFF4A:
      return _wy;
    case 0xFF4B:
      return _wx;
    default:
      return (0);
    }
  }
  void write(Word addr, Byte v) override {
    switch (addr) {
    case 0xFF40:
      _lcdc = v;
      break;
    case 0xFF41:
      _stat = v;
      break;
    case 0xFF42:
      _scy = v;
      break;
    case 0xFF43:
      _scx = v;
      break;
    case 0xFF44:
      _ly = v;
      break;
    case 0xFF45:
      _lyc = v;
      break;
    case 0xFF46:
      _dma = v;
      break;
    case 0xFF47:
      _bgp = v;
      break;
    case 0xFF48:
      _obp0 = v;
      break;
    case 0xFF49:
      _obp1 = v;
      break;
    case 0xFF4A:
      _wy = v;
      break;
    case 0xFF4B:
      _wx = v;
      break;
    default:
      break;
    }
  }
};
