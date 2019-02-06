#ifndef CARTRIDGE_HPP
# define CARTRIDGE_HPP

# include <cstdint>
# include <vector>
# include <array>
# include "IMemoryBankController.hpp"

using Byte = uint8_t;
using Word = uint16_t;

class Cartridge {
private:
	IMemoryBankController *mbc;
	std::array<uint8_t,0x20000> ram;
	std::vector<uint8_t> rom;

public:
	Cartridge(std::string rom_path);
	
	auto get_begin() { return rom.begin(); }
	auto get_end() { return rom.end(); }

	Byte read(Word addr) {
		if (mbc)
			return mbc->read(addr);
		return (0);
	}

	void write(Word addr, Byte v) {
		if (mbc) {
			mbc->write(addr, v);
		}
	}

	int load_rom(std::string path);
	IMemoryBankController *get_mbc(uint8_t cartridge_type);

};

#endif
