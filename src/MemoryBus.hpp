#ifndef MEMORYBUS_H
#define MEMORYBUS_H

#include <cstdint>
#include <iostream>
#include "Cartridge.hpp"
#include "InterruptController.hpp"

using Byte = uint8_t;
using Word = uint16_t;

class MemoryBus {

private:
	Cartridge *cartridge;
	InterruptController *ic;

public:
	MemoryBus(Cartridge *c, InterruptController *ic) : cartridge(c), ic(ic) {}

	template <typename T>
	T read(Word addr) {
		T ret = 0;
		auto i = sizeof(T);

		if (addr < 0x8000) {
			while (i > 0) {
				i--;
				ret |= cartridge->read(addr + i) >> (i * 8);
			}
		} else if (addr >= 0xFF04 && addr <= 0xFF07) {
		} else if (addr == 0xFF0F || addr == 0xFFFF) {
			ic->Read(addr);
		}
		return ret;
	}

	template <typename T>
	void write(Word addr, T v) {
		auto i = sizeof(T);
		if (addr < 0x8000) {
			while (i > 0) {
				i--;
				cartridge->write(addr + i, v >> (i * 8));
			}
		} else if (addr == 0xFF0F || addr == 0xFFFF) {
			ic->Write(addr, v);
		}
	}
};

#endif /* MEMORYMAP_H */
