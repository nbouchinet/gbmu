#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include <sys/mman.h>
#include <sys/stat.h>
#include <array>

class MemoryBus;
class Core;
class Cartridge;
class InterruptController;
class Timer;

using Byte = uint8_t;
using Word = uint16_t;

class Gameboy {
	MemoryBus *mem_bus;
	Core *core;
	Cartridge *cartridge;
	InterruptController *interrupt_controller;
	Timer *timer;

public:
	Gameboy(std::string const rom_path);

	int run();
	void init();
};

#endif
