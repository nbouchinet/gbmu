#include "Cartridge.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Cartridge::Cartridge(std::string rom_path) : rom(0) {
	load_rom(rom_path);
	mbc = get_mbc(rom[0x147]);
}

int Cartridge::load_rom(std::string path) {
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	rom = std::vector<uint8_t>(size);
	if (file.read((char *)(rom.data()), size)) {
		return (1);
	}
	return (0);
}

IMemoryBankController *Cartridge::get_mbc(uint8_t cartridge_type) {
	switch (cartridge_type) {
		case 0x0:
		case 0x01:
		case 0x02:
		case 0x03:
			std::cout << "Detected MBC1" << std::endl;
			return new MemoryBankController1(&rom, &ram);
//			case 0x05:
//			case 0x06:
//				std::cout << "Detected MBC2" << std::endl;
//				return new MemoryBankController2(rom);
//			case 0x0F:
//			case 0x10:
//			case 0x11:
//			case 0x12:
//			case 0x13:
//				std::cout << "Detected MBC3" << std::endl;
//				return new MemoryBankController3(rom);
//			case 0x19:
//			case 0x1A:
//			case 0x1B:
//			case 0x1C:
//			case 0x1D:
//			case 0x1E:
//				std::cout << "Detected MBC5" << std::endl;
//				return new MemoryBankController5(rom, ram);
		default:
			std::cout << static_cast<int>(rom[0x147]) << std::endl;
			return (0);
	}
}
