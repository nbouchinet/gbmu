#include "Gameboy.hpp"

#include <fstream>
#include <iostream>
#include "MemoryBus.hpp"
#include "InterruptController.hpp"
#include "cpu/Core.hpp"
#include "Timer.hpp"

Gameboy::Gameboy(std::string const rom_path) {
	cartridge = new Cartridge(rom_path);
	interrupt_controller = new InterruptController();
	mem_bus = new MemoryBus(cartridge, interrupt_controller);
	core = new Core(mem_bus, interrupt_controller);
	interrupt_controller->SetCore(core);
	timer = new Timer(interrupt_controller);
}

int Gameboy::run() {
	auto it = cartridge->get_begin() + core->pc();
	auto end = cartridge->get_end();

	while (it != end) {
		std::cout << "pc: " << std::hex << core->pc() << std::endl;
		core->execute(it);
		interrupt_controller->ParseInterrupt();
		timer->Update(core->clock());
	}
	return (0);
}

void Gameboy::init() {
    mem_bus->write(0xFF05, 0x00); // Timer Counter
    mem_bus->write(0xFF06, 0x00); // Timer Modulo
    mem_bus->write(0xFF07, 0x00); // Timer Controller
    mem_bus->write(0xFF10, 0x80); // Sound1
    mem_bus->write(0xFF11, 0xBF); // Sound1
    mem_bus->write(0xFF12, 0xF3); // Sound1
    mem_bus->write(0xFF14, 0xBF); // Sound1
    mem_bus->write(0xFF16, 0x3F); // Sound2
    mem_bus->write(0xFF17, 0x00); // Sound2
    mem_bus->write(0xFF19, 0xBF); // Sound2
    mem_bus->write(0xFF1A, 0x7F); // Sound3
    mem_bus->write(0xFF1B, 0xFF); // Sound3
    mem_bus->write(0xFF1C, 0x9F); // Sound3
    mem_bus->write(0xFF1E, 0xBF); // Sound3
    mem_bus->write(0xFF20, 0xFF); // Sound4
    mem_bus->write(0xFF21, 0x00); // Sound4
    mem_bus->write(0xFF22, 0x00); // Sound4
    mem_bus->write(0xFF23, 0xBF); // Sound4
    mem_bus->write(0xFF24, 0x77); // Sound4
    mem_bus->write(0xFF25, 0xF3); // Sound4
    mem_bus->write(0xFF26, 0xF1); // Sound4
    mem_bus->write(0xFF40, 0x91);
    mem_bus->write(0xFF42, 0x00);
    mem_bus->write(0xFF43, 0x00);
    mem_bus->write(0xFF45, 0x00);
    mem_bus->write(0xFF47, 0xFC);
    mem_bus->write(0xFF48, 0xFF);
    mem_bus->write(0xFF49, 0xFF);
    mem_bus->write(0xFF4A, 0x00);
    mem_bus->write(0xFF4B, 0x00);
    mem_bus->write(0xFFFF, 0x00);
}
